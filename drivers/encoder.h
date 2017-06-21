#ifndef _ENCODER_H_
#define _ENCODER_H_

#define PWMToDegree 0.9230769f					//390Ïß
void Encoder_Configuration(void);
typedef struct 
{
	float speed;
	float degree;
	int circle_cnt;
	u32 time_last;
	u32 time_now;
	float T;
	float encoder_temp;
}_encoder_st;
#define Encoder_InitVal {\
													0.0f,\
													0.0f,\
													0,\
													0,\
													0,\
													0.0f,\
													0.0f}
extern _encoder_st left_encoder,right_encoder;
void Encoder_Start(void);
void Refresh_Encoder(void);
#endif
