#include "nxt_service.h"

int			bt_fd;
pthread_t	tid_nxtReader;
pthread_t	tid_nxtWriter;
int			mq_id;

int main(void)
{
	int		ret;
	key_t	mq_key;
	int		mq_file;
	
	printf("Connecting to %s ...\n", DEFAULT_NXT_PATH);
	bt_fd = open_port(DEFAULT_NXT_PATH);
	
	printf("Ready\n");
	
	
	mq_file = open(MQ_PATH, O_CREAT|O_TRUNC, 0600);
	if(mq_file == -1) show_error("open mq_file");
	close(mq_file);
	mq_key = ftok(MQ_PATH, 0);
	if(mq_key == -1) show_error("ftok");
	mq_id = msgget(mq_key , 0600 | IPC_CREAT);
	if(mq_id == -1) show_error("msgget");
	
	
	ret = pthread_create(&tid_nxtReader, NULL, (void*) thread_nxtReader, NULL);	
	if(ret == -1) show_error("pthread_create nxtReader");
	
	ret = pthread_create(&tid_nxtWriter, NULL, (void*) thread_nxtWriter, NULL);	
	if(ret == -1) show_error("pthread_create nxtWriter");
	
	pthread_join(tid_nxtWriter, NULL);
	pthread_cancel(tid_nxtReader);
	
	
	close(bt_fd);
	
	
	ret = msgctl (mq_id, IPC_RMID, 0);
	if(ret == -1) show_error("msgctl");
	remove(MQ_PATH);
	
	return 0;
}


// Thread de lecture parallèle des retours du NXT
void thread_nxtWriter(void)
{
	char data;
	printf(">");
	
	while(1)
	{
		//data = instant_getchar();
		msgrcv(mq_id, &data, 1, 0, MSG_NOERROR);
		
		switch (data) {
			case 'z'	: nxt_move(FRONT);	break;
			case 's'	: nxt_move(BACK);	break;
			case 'q'	: nxt_move(LEFT);	break;
			case 'd'	: nxt_move(RIGHT);	break;
			case ' '	: nxt_move(STOP);	break;
			case 0x1B	: return;			break;
		}
	}
}


// Thread de lecture parallèle des retours du NXT
void thread_nxtReader(void)
{
	uint8	data;
	uint16	packet_size;
	int		i;
	char*	data_type;
	
	// 1 donnée = 2 octet de taille + X de data brute
	while(1)
	{
		// Analyse de la taille du paquet
		packet_size = 0;
		for(i=0;i<2;i++)
		{
			data = readChar_port(bt_fd);
			packet_size += (i == 0) ? data : data << 8;
		}
		// Analyse du paquet
		for(i=0;i<packet_size;i++)
		{
			data = readChar_port(bt_fd);
			if (i == 0) printf("NXT said: \n");
			printf("\t0x%X ",data);
			if (i == 0 && data == 0x02) data_type = "reply";
			else if	(i == 1)
			{
				switch (data) {
					case 0x00: data_type=CMD_0x00; break;
					case 0x01: data_type=CMD_0x01; break;
					case 0x02: data_type=CMD_0x02; break;
					case 0x03: data_type=CMD_0x03; break;
					case 0x04: data_type=CMD_0x04; break;
					case 0x05: data_type=CMD_0x05; break;
					case 0x06: data_type=CMD_0x06; break;
					case 0x07: data_type=CMD_0x07; break;
					case 0x08: data_type=CMD_0x08; break;
					case 0x09: data_type=CMD_0x09; break;
					case 0x0A: data_type=CMD_0x0A; break;
					case 0x0B: data_type=CMD_0x0B; break;
					case 0x0C: data_type=CMD_0x0C; break;
					default:   data_type="?"; break;
				}
			}
			else if	(i == 2)
			{
				switch (data) {
					case 0x00: data_type=ERR_0X00; break;
					case 0x20: data_type=ERR_0X20; break;
					case 0x40: data_type=ERR_0X40; break;
					case 0xBD: data_type=ERR_0XBD; break;
					case 0xBE: data_type=ERR_0XBE; break;
					case 0xBF: data_type=ERR_0XBF; break;
					case 0xC0: data_type=ERR_0XC0; break;
					case 0xDD: data_type=ERR_0XDD; break;
					case 0xDE: data_type=ERR_0XDE; break;
					case 0xDF: data_type=ERR_0XDF; break;
					case 0xE0: data_type=ERR_0XE0; break;
					case 0xEC: data_type=ERR_0XEC; break;
					case 0xED: data_type=ERR_0XED; break;
					case 0xEE: data_type=ERR_0XEE; break;
					case 0xEF: data_type=ERR_0XEF; break;
					case 0xF0: data_type=ERR_0XF0; break;
					case 0xFB: data_type=ERR_0XFB; break;
					case 0xFF: data_type=ERR_0XFF; break;
					default:   data_type="?"; break;
				}
			}
			
			printf("(%s)\n", data_type);
		}
	}
}


// Avance ou recule le NXT à la vitesse indiquée
void nxt_move(int dir)
{
	uint8 left_speed;
	uint8 right_speed;
	
	switch (dir) {
		case FRONT :
			left_speed		= 100;
			right_speed		= 100;
			break;
		case BACK :
			left_speed		= -100;
			right_speed		= -100;
			break;
		case LEFT :
			left_speed		= 100;
			right_speed		= -100;
			break;
		case RIGHT :
			left_speed		= -100;
			right_speed		= 100;
			break;
		case STOP :
		default :
			left_speed		= 0;
			right_speed		= 0;
			break;
	}
	
	cmd_setOutputState(MOTOR_LEFT,  left_speed,  MOTORON|BRAKE, REGULATION_MODE_IDLE, 0, MOTOR_RUN_STATE_RUNNING, 0);
	cmd_setOutputState(MOTOR_RIGHT, right_speed, MOTORON|BRAKE, REGULATION_MODE_IDLE, 0, MOTOR_RUN_STATE_RUNNING, 0);

}

// Commande sonore du NXT
void cmd_playTone(uint16 freq, uint16 duration)
{
	uint8 cmd[6];
	
	if((freq < 200) || (freq > 14000))
	{
		fprintf(stderr,"cmd_playTone: erreur, 200<freq<14000");
		return;
	}
	
	cmd[0] = DIRECT_CMD_REP;
	cmd[1] = PLAYTONE;
	cmd[2] = getLSB(freq);
	cmd[3] = getMSB(freq);
	cmd[4] = getLSB(duration);
	cmd[5] = getMSB(duration);
	
	sendCmd(cmd, 6);
}

// Commande des sorties du NXT
void cmd_setOutputState(uint8 port, uint8 power, uint8 mode, uint8 regulationMode, uint8 turnRatio, uint8 runState, int tachoLimit)
{
	uint8 cmd[12];
	
	cmd[0] = DIRECT_CMD_REP;
	cmd[1] = SETOUTPUTSTATE;
	cmd[2] = port;
	cmd[3] = power;
	cmd[4] = mode;
	cmd[5] = regulationMode;
	cmd[6] = turnRatio;
	cmd[7] = runState;
	cmd[8] = tachoLimit & 0xFF;
	cmd[9] = (tachoLimit & (0xFF << 8)) >> 8;
	cmd[10] = (tachoLimit & (0xFF << 16)) >> 16;
	cmd[11] = (tachoLimit & (0xFF << 24)) >> 24;
	cmd[12] = 0;
	//cmd[12] = (tachoLimit & (0xFF << 32)) >> 32;
	
	sendCmd(cmd, 13);
}

// Envoi d'une commande
void sendCmd(uint8* cmd, int size)
{	
	writeChar_port	(bt_fd, getLSB(size));
	writeChar_port	(bt_fd, getMSB(size));
	writeStr_port	(bt_fd, (char*) cmd, size);
}


char getLSB(uint16 word)
{
	return (word & 0xFF);
}


char getMSB(uint16 word)
{
	return ((word & 0xFF) >> 8);
}

// getchar() sans attente de \n
int instant_getchar(void) 
{
	struct termios oldt, newt;
	int ch;

	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}