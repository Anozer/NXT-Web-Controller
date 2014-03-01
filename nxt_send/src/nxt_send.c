#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define	MQ_PATH	"/tmp/mq_php2nxt"

key_t	mq_key;
int		mq_id;

int main(void)
{
	char *get_data;
	char cmd;
	
	printf("Content-Type: text/html;\n\n");
	
	get_data = getenv("QUERY_STRING");
	if(get_data == NULL)
	{
		printf("<p>Erreur dans le script !</p>");
		return(1);
	}

	sscanf(get_data, "cmd=%s", get_data);
	
	if		(strcmp("FRONT",	get_data) == 0)	cmd = 'z';
	else if	(strcmp("BACK",		get_data) == 0)	cmd = 's';
	else if	(strcmp("LEFT",		get_data) == 0)	cmd = 'q';
	else if	(strcmp("RIGHT",	get_data) == 0)	cmd = 'd';
	else if	(strcmp("STOP",		get_data) == 0)	cmd = ' ';
	else if	(strcmp("EXIT",		get_data) == 0)	cmd = 0x1B;
	else										return 0;
	
	mq_key = ftok(MQ_PATH, 0);
	if(mq_key == -1) perror("ftok");
	mq_id = msgget(mq_key , 0600);
	if(mq_id == -1) perror("msgget");
	
	msgsnd (mq_id, &cmd, 1, 0);
	
	printf("OK");
	
	return 0;
}