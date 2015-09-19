/*
** main.c for  in /home/sabour_f/aes
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Sep 19 09:39:11 2015 Florian SABOURIN
** Last update Sat Sep 19 09:39:11 2015 Florian SABOURIN
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "config.h"
#include "moulicl.h"

// Fetches the key from the file. The key format is described before main()
static int	fetchkey(char *file, byte *key)
{
  size_t	left; // Number of bytes left to read
  char		buffer[128];
  int		fd; // Input file descriptor
  int		readret; // Return from read() call

  fd = open(file, O_RDONLY);
  if (fd == -1)
    {
      perror("open");
      return (1);
    }

  // The key is 32 bytes (64 digits) long
  left = 64;
  // Read bytes in a loop
  while (left && (readret = read(fd, &buffer[64 - left], left)) > 0)
    left -= readret;
  close(fd);

  // If there was an error when reading the key
  if (left)
    {
      if (readret < 0)
	perror("read");
      else
	fprintf(stderr, "Ill formated key file\n");
      return (1);
    }

  // Check if the key is valid
  buffer[64] = '\0';
  if (strspn(buffer, "0123456789abcdef") != 64)
    {
      fprintf(stderr, "Ill formated key file\n");
      return (1);
    }

  // Translate key from text to binary
  for (left = 0 ; left < 32 ; ++left)
    {
      char dig1, dig2; // The two digits
      dig1 = buffer[left * 2];
      dig2 = buffer[left * 2 + 1];
      // Digit -> value
      dig1 = dig1 >= '0' && dig1 <= '9' ? dig1 - '0' : dig1 - 'a' + 10;
      dig2 = dig2 >= '0' && dig2 <= '9' ? dig2 - '0' : dig2 - 'a' + 10;
      key[left] = ((dig1 & 0x0F) << 4) | (dig2 & 0x0F);
    }
  return (0);
}

// Entry point
// Use the program as : ./mouli <keyfile> <configfile>
// The keyfile must contain an hexadecimal string of 64 digits (letters must be
// lowercase) with an optionnal trailing end of line
int	main(int argc, char **argv)
{
  t_moulicl cl;
  t_config *config;
  int	ret;

  if (argc != 3)
    {
      fprintf(stderr, "Usage: %s keyfile configfile\n", *argv);
      return (1);
    }

  if (fetchkey(argv[1], cl.key) == 0)
    {
      config = loadconfig(argv[2]);
      if (config)
	{
	  moulicl_init(&cl, config);
	  if (moulicl_connect(&cl) == 0)
	    {
	      ret = moulicl_run(&cl);
	      moulicl_delete(&cl);
	      return (ret);
	    }
	  moulicl_delete(&cl);
	}
    }
  else
    perror("open");
  return (1);
}
