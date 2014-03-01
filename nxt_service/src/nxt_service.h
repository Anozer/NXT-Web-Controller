#ifndef NXT_H_INCLUDED
#define NXT_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "nxt_common.h"
#include "serialPort.h"

#define DEFAULT_NXT_PATH	"/dev/cu.NXT_SerialPort"
#define	MQ_PATH				"/tmp/mq_php2nxt"

#define MOTOR_LEFT		PORTB
#define	MOTOR_RIGHT		PORTC
#define MOTOR_CENTER	PORTA
#define MOTOR_ALL		0xFF

#define FRONT	0
#define BACK	1
#define LEFT	2
#define RIGHT	3
#define STOP	4

typedef unsigned short int uint16;
typedef unsigned char uint8;

void	thread_nxtWriter	(void);
void	thread_nxtReader	(void);
void	nxt_move			(int dir);
void	cmd_playTone		(uint16 freq, uint16 duration);
void	cmd_setOutputState	(uint8 port, uint8 power, uint8 mode, uint8 regulationMode, uint8 turnRatio, uint8 runState, int tachoLimit);
void	sendCmd				(uint8* cmd, int size);
char	getLSB				(uint16 word);
char	getMSB				(uint16 word);
int		instant_getchar		(void);

#endif
