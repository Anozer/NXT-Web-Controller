#ifndef SERIALPORT_H_INCLUDED
#define SERIALPORT_H_INCLUDED

/***************
 *	Libs
 ***************/

#include <stdio.h>		/* Standard input/output definitions */
#include <stdlib.h>		/* exit */
#include <string.h>		/* String function definitions */
#include <unistd.h>		/* UNIX standard function definitions */
#include <fcntl.h>		/* File control definitions */
#include <errno.h>		/* Error number definitions */
#include <termios.h>	/* POSIX terminal control definitions */


/***************
 *	Prototypes
 ***************/
 
int		open_port		(char* port_loc);
void	init_port		(int fd);
void	writeChar_port	(int fd, char c);
void	writeStr_port	(int fd, char* str, int len);
char	readChar_port	(int fd);
void	readStr_port	(int fd, int nbChar, char* str);
void	show_error		(char* err_str);


#endif