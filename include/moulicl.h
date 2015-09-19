/*
** moulicl.h for  in /home/sabour_f/aes/include
**
** Made by Florian SABOURIN
** Login   <sabour_f@epitech.net>
**
** Started on  Sat Sep 19 13:12:00 2015 Florian SABOURIN
** Last update Sat Sep 19 13:12:00 2015 Florian SABOURIN
*/

#ifndef MOULICL_H_
# define MOULICL_H_

# include <stdint.h>
# include "config.h"

// Defined for convenience
typedef unsigned char byte;

// Main moulinette client structure
typedef struct s_moulicl t_moulicl;
struct s_moulicl
{
  int	socket;
  t_config *config;
  byte	exp_key[256]; // Expanded AES key (240 bytes)
  byte	key[32];
};

// Moulicl
void	moulicl_init(t_moulicl *moulicl, t_config *cfg);
int	moulicl_connect(t_moulicl *moulicl);
int	moulicl_run(t_moulicl *cl);
void	moulicl_delete(t_moulicl *moulicl);

// AES utilities
void	key_expansion(uint8_t *key, uint8_t *w);
void	cipher(uint8_t *in, uint8_t *out, uint8_t *w);
void	inv_cipher(uint8_t *in, uint8_t *out, uint8_t *w);

#endif /* !MOULICL_H_ */

/*
** HTTP/1.1 200 OK
** Server: Tiny Web Server
** Content-type: text/html
**
** <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr" >
** <head><title>toto</title></head>
** <body>coucou</body></html>
*/
