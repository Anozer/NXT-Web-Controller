#include "serialPort.h"

// ouvre le port série
int open_port(char* port_loc)
{
	int fd;

	// ouverture non bloquante
	fd = open(port_loc, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) show_error("open_port");
	else fcntl(fd, F_SETFL, 0); // 0 pour opérations non bloquantes
	return (fd);
}

// Init du port série
void init_port(int fd)
{
	struct termios	port_options;
	
	tcgetattr(fd, &port_options);			// get des anciennes options du port
	cfsetspeed(&port_options, B9600);		// vitesse 9600 bauds
	port_options.c_cflag &= ~PARENB;		// pas de paritée
	port_options.c_cflag &= ~CSTOPB;		// 1 bit de stop
	port_options.c_cflag &= ~CSIZE; 		// Mask the character size bits
    port_options.c_cflag |= CS8;			// 8 bits de données
	tcsetattr(fd, TCSANOW, &port_options);	// set des options modifées
}

// Ecriture d'un caractère sur le port
void writeChar_port(int fd, char c)
{
	char data[1];
	data[0] = c;
	writeStr_port(fd, data, 1);
}

// Ecriture d'une chaine sur le port
void writeStr_port(int fd, char* str, int len)
{
	int ret;	
	ret = write(fd, str, len);
	if(ret == -1) show_error("writeStr_port");
}

// Lecture d'un caractère sur le port
char readChar_port(int fd)
{
	char str;
	readStr_port(fd, 1, (char*) &str);
	return str;
}

// Lecture d'une chaine sur le port
void readStr_port(int fd, int nbChar, char* str)
{
	int len;
	len = read(fd, str, nbChar);
	if(len == -1) show_error("readChar_port");
	str[nbChar] = '\0';
}

// Affiche l'erreur et quitte
void show_error(char* err_str)
{
	perror(err_str);
	exit(1);
}
