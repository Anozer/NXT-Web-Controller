#ifndef NXTCOMMON_H_INCLUDED
#define NXTCOMMON_H_INCLUDED


// ports
#define PORTA	0x00
#define PORTB	0x01
#define PORTC	0x02
#define PORT1	0x00
#define PORT2	0x01
#define PORT3	0x02
#define PORTC	0x02


// Byte 0 : command type
#define DIRECT_CMD_REP		0x00
#define SYSTEM_CMD_REP		0x01
#define REPLY				0x02
#define DIRECT_CMD_NOREP	0x80
#define SYSTEM_CMD_NOREP	0x81

// Byte 1 : command
#define STARTPROGRAM			0x00
#define STOPPROGRAM				0x01
#define PLAYSOUNDFILE			0x02
#define PLAYTONE				0x03
#define SETOUTPUTSTATE			0x04
#define SETINPUTMODE			0x05
#define GETINPUTSTATE			0x06
#define GETINPUTVALUES			0x07
#define RESETINPUTSCALEDVALUE	0x08
#define MESAGEWRITE				0x09
#define RESETMOTORPOSITION		0x0A
#define GETBATTERYLEVEL			0x0B
#define STOPSOUNDPLAYBACK		0x0C

#define CMD_0x00	"STARTPROGRAM"
#define CMD_0x01	"STOPPROGRAM"
#define CMD_0x02	"PLAYSOUNDFILE"
#define CMD_0x03	"PLAYTONE"
#define CMD_0x04	"SETOUTPUTSTATE"
#define CMD_0x05	"SETINPUTMODE"
#define CMD_0x06	"GETINPUTSTATE"
#define CMD_0x07	"GETINPUTVALUES"
#define CMD_0x08	"RESETINPUTSCALEDVALUE"
#define CMD_0x09	"MESAGEWRITE"
#define CMD_0x0A	"RESETMOTORPOSITION"
#define CMD_0x0B	"GETBATTERYLEVEL"
#define CMD_0x0C	"STOPSOUNDPLAYBACK"


// *** SETOUTPUTSTATE ***

// Valid enumation for "Mode"
#define MOTORON 	0x01	// Turn on the specified motor
#define BRAKE		0x02	// Use run/brake instead of run/float
#define REGULATED	0x04	// Turns on the regulation

// Valid enumation for "Regulation Mode"
#define REGULATION_MODE_IDLE		0x00	// No regulation will be enabled
#define REGULATION_MODE_MOTOR_SPEED	0x01	// Power control will be enabled on specified output
#define REGULATION_MODE_MOTOR_SYNC	0x02	// Synchronization will be enabled (Need enabled on two output)

// Valid enumation for "RunState"
#define MOTOR_RUN_STATE_IDLE		0x00	//Output will be idle
#define MOTOR_RUN_STATE_RAMPUP		0x10	//Output will ramp-up
#define MOTOR_RUN_STATE_RUNNING		0x20	//Output will be running
#define MOTOR_RUN_STATE_RAMPDOWN	0x40	//Output will ramp-down


// *** SETINPUTMODE ***

// Valid enumation for "Sensor Type"
#define NO_SENSOR			0x00	
#define SWITCH				0x01
#define TEMPERATURE			0x02
#define REFLECTION			0x03
#define ANGLE				0x04
#define LIGHT_ACTIVE		0x05
#define LIGHT_INACTIVE		0x06
#define SOUND_DB			0x07
#define SOUND_DBA			0x08
#define CUSTOM				0x09
#define LOWSPEED			0x0A
#define LOWSPEED_9V			0x0B
#define NO_OF_SENSOR_TYPES	0x0C

// Valid enumation for "Sensor Mode"
#define RAWMODE				0x00
#define BOOLEANMODE			0x20
#define TRANSOTIONCNTMODE	0x40
#define PERIODCOUNTERMODE	0x60
#define PCTFULLSCALEMODE	0x80
#define CELSIUSMODE			0xA0
#define FAHRENHEITMODE		0xC0
#define ANGLESTEPSMODE		0xE0
#define SLOPEMASK			0x1F
#define MODEMASK			0xE0


// *** ERRORS ***
#define ERR_0X00	"No error"
#define ERR_0X20	"Pending communication transaction in progress"
#define ERR_0X40	"Specified mailbox queue is empty"
#define ERR_0XBD	"Request failed (i.e. specified file not found)"
#define ERR_0XBE	"Unknown command opcode"
#define ERR_0XBF	"Insane packet"
#define ERR_0XC0	"Data contains out-of-range values"
#define ERR_0XDD	"Communication bus error"
#define ERR_0XDE	"No free memory in communication buffer"
#define ERR_0XDF	"Specified channel/connection is not valid"
#define ERR_0XE0	"Specified channel/connection not configured or busy"
#define ERR_0XEC	"No active program"
#define ERR_0XED	"Illegal size specified"
#define ERR_0XEE	"Illegal mailbox queue ID specified"
#define ERR_0XEF	"Attempted to access invalid field of a structure"
#define ERR_0XF0	"Bad input or output specified"
#define ERR_0XFB	"Insufficient memory available"
#define ERR_0XFF	"Bad arguments"

#endif