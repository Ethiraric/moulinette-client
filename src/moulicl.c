/*
** moulicl.c for  in /home/sabour_f/aes/src
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Sep 19 13:11:29 2015 Florian SABOURIN
** Last update Sat Sep 19 13:11:29 2015 Florian SABOURIN
*/

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "moulicl.h"

// Initializes a moulicl structure
void	moulicl_init(t_moulicl *moulicl, t_config *cfg)
{
  moulicl->config = cfg;
  moulicl->socket = 0;
  key_expansion(moulicl->key, moulicl->exp_key);
}

// Fetches the host from the configuration
static char *get_host(t_config *cfg)
{
  size_t i;

  for (i = 0 ; i < cfg->nb_entries ; ++i)
    if (!strcmp(cfg->entries[i].key, "host"))
      return (cfg->entries[i].value);
  fprintf(stderr, "No host in config file\n");
  return (NULL);
}

// Fetches the port from the configuration
static unsigned short get_port(t_config *cfg)
{
  size_t i;
  int port;

  for (i = 0 ; i < cfg->nb_entries ; ++i)
    if (!strcmp(cfg->entries[i].key, "port"))
      {
	port = atoi(cfg->entries[i].value);
	if (port > 0 && port < 65536)
	  return ((unsigned short)(port));
	fprintf(stderr, "Invalid port\n");
	return (0);
      }
  fprintf(stderr, "No port in config file\n");
  return (0);
}

// The mouli client will try to connect to remote host
// Host and port are in the configuration
int	moulicl_connect(t_moulicl *moulicl)
{
  unsigned short port;
  char	*host;

  // Get connect informations
  host = get_host(moulicl->config);
  if (!host)
    return (1);
  port = get_port(moulicl->config);
  if (!port)
    return (1);

  // Do connect
  struct hostent *hostinfo;
  struct sockaddr_in sin;

  hostinfo = gethostbyname(host);
  if (!hostinfo)
    {
      herror("gethostbyname");
      return (1);
    }
  moulicl->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (moulicl->socket == -1)
    {
      perror("socket");
      moulicl->socket = 0;
      return (1);
    }
  sin.sin_addr = *((struct in_addr *)hostinfo->h_addr);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (connect(moulicl->socket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      close(moulicl->socket);
      moulicl->socket = 0;
      perror("connect");
      return (1);
    }
  return (0);
}

// Deallocates all resources allocated for the mouli client, and disconnects
void	moulicl_delete(t_moulicl *moulicl)
{
  if (moulicl->socket)
    close(moulicl->socket);
  deleteconfig(moulicl->config);
}

// Main program loop
int	moulicl_run(t_moulicl *moulicl)
{
  (void)(moulicl);
  return (0);
}
