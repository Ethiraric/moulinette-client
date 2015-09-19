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

// Ask the user it's login
static char *prompt_login()
{
  size_t size;
  char	*login;
  char	*tmp;

  login = NULL;
  size = 0;
  printf("Login: ");
  if (getline(&login, &size, stdin) < 0)
    {
      perror("getline");
      return (NULL);
    }

  // Remove trailing linefeed, if any
  tmp = strchr(login, '\n');
  if (tmp)
    *tmp = '\0';

  if (strlen(login) > 8)
    {
      fprintf(stderr, "Invalid login\n");
      free(login);
      return (NULL);
    }
  return (login);
}

// Ask the user it's login
static char *prompt_pass()
{
  char	*pass;

  pass = getpass("UNIX password: ");
  if (!pass)
    {
      perror("getpass");
      return (NULL);
    }
  return (pass);
}

// Send authentification strings to the server
static int authenticate(t_moulicl *cl, char *login, char *pass)
{
  size_t len;
  byte	in[16];
  byte	out[16];

  memset(in, 0, 16);
  len = strlen(pass);
  in[0] = len;
  memmove(&in[1], pass, len);
  memset(pass, 0, strlen(pass));
  cipher(in, out, cl->exp_key);
  if (dprintf(cl->socket, "%s\n", login) < 0)
    {
      perror("dprintf");
      return (1);
    }
  if (write(cl->socket, out, 16) < 0)
    {
      memset(out, 0, 16);
      perror("write");
      return (1);
    }
  memset(out, 0, 16);
  return (0);
}

// Main program loop
int	moulicl_run(t_moulicl *cl)
{
  char	*login;
  char	*pass;

  login = prompt_login();
  pass = prompt_pass();
  if (!login || !pass)
    {
      free(login);
      return (1);
    }
  if (authenticate(cl, login, pass) == 0)
    {
    }
  free(login);
  free(pass);
  return (0);
}
