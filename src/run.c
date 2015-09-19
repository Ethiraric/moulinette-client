/*
** run.c for  in /home/sabour_f/aes/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Sep 19 16:00:00 2015 Florian SABOURIN
** Last update Sat Sep 19 16:00:00 2015 Florian SABOURIN
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "moulicl.h"

// Ask the user a string
static char *prompt_str(const char *prefix)
{
  size_t size;
  char	*ret;
  char	*tmp;

  ret = NULL;
  size = 0;
  printf("%s", prefix);
  if (getline(&ret, &size, stdin) < 0)
    {
      perror("getline");
      return (NULL);
    }

  // Remove trailing linefeed, if any
  tmp = strchr(ret, '\n');
  if (tmp)
    *tmp = '\0';
  return (ret);
}

// Ask the user it's pass
static char *prompt_pass()
{
  char	*pass;

  pass = getpass("UNIX password: ");
  if (!pass)
    {
      perror("getpass");
      return (NULL);
    }
  if (strlen(pass) > 14)
    {
      free(pass);
      fprintf(stderr, "Pass unsupported\n");
      return (NULL);
    }
  return (pass);
}

// Send authentification strings to the server
// Calls free() on the login and the pass since they no longer need to exist
static int authenticate(t_moulicl *cl, char *login, char *pass)
{
  size_t len;
  byte	in[16];
  byte	out[16];

  // Set unused bytes to 0
  memset(in, 0, 16);
  len = strlen(pass);
  // First byte of the pack is the length of the datas
  in[0] = len;
  // Then the datas follow (no more than 15 bytes
  memmove(&in[1], pass, len);
  // Erase pass from memory
  memset(pass, 0, strlen(pass));
  cipher(in, out, cl->exp_key);
  // Remember to erase the ciphered pass from memory
  if (dprintf(cl->socket, "%s\n", login) < 0)
    {
      memset(out, 0, 16);
      free(login);
      free(pass);
      perror("dprintf");
      return (1);
    }
  if (write(cl->socket, out, 16) < 0)
    {
      memset(out, 0, 16);
      free(login);
      free(pass);
      perror("write");
      return (1);
    }
  memset(out, 0, 16);
  free(login);
  free(pass);
  return (0);
}

// Wait for results and display them
static int wait_results(t_moulicl *cl)
{
  fd_set rfds;
  char	buffer[BUFSIZ];
  int	ret;

  FD_ZERO(&rfds);
  FD_SET(cl->socket, &rfds);
  while (select(cl->socket + 1, &rfds, NULL, NULL, NULL) > 0)
    {
      FD_SET(cl->socket, &rfds);
      ret = read(cl->socket, buffer, BUFSIZ - 1);
      if (!ret)
	return (0);
      if (ret < 0)
	{
	  perror("read");
	  return (1);
	}
      buffer[ret] = '\0';
      printf("%s", buffer);
    }
  perror("select");
  return (1);
}

// Main program loop
int	moulicl_run(t_moulicl *cl)
{
  char	*login;
  char	*pass;
  char	*repo;

  // Prompt login and password, then authenticate
  login = prompt_str("Login: ");
  pass = prompt_pass();
  if (!login || !pass)
    {
      free(login);
      return (1);
    }
  if (strlen(login) > 8)
    {
      fprintf(stderr, "Invalid login\n");
      free(login);
      free(pass);
      return (1);
    }
  if (authenticate(cl, login, pass) == 0)
    {
      // Ask for repository
      repo = prompt_str("Repository: ");
      if (!repo)
	return (1);
      if (dprintf(cl->socket, "%s\n", repo) < 0)
	{
	  perror("dprintf");
	  free(repo);
	  return (1);
	}
      free(repo);
      return (wait_results(cl));
    }
  return (1);
}
