#include "main.h"
_encoder_st left_encoder=Encoder_InitVal,
						right_encoder=Encoder_InitVal;
/*-----LEFT----TIM3*/
/*----RIGHT----TIM5*/
void Encoder_Configuration(void)
{
		GPIO_InitTypeDef gpio;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC,&gpio);
		gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
		GPIO_Init(GPIOA,&gpio);
	
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM3,ENABLE);	
		TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM5,ENABLE);	
}



void Encoder_Start(void)
{
    TIM5->CNT = 0x00;
		TIM3->CNT = 0x00;
		
}
void Refresh_Encoder(void)
{
	int TIM_TIM5,TIM_TIM3;
	
	TIM_TIM5 = (short)TIM5 -> CNT; TIM5->CNT=0;
	TIM_TIM3 = (short)TIM3 -> CNT; TIM3->CNT=0;
	
	left_encoder.T=((GetInnerLoop(Left_Chassis_Time))/1000000.0f);
	right_encoder.T=((GetInnerLoop(Right_Chassis_Time))/1000000.0f);
	
	left_encoder.encoder_temp = TIM_TIM3*PWMToDegree;
	right_encoder.encoder_temp = TIM_TIM5*PWMToDegree;
	
	left_encoder.speed=ANGLE_TO_RADIAN*TIM_TIM3*PWMToDegree/left_encoder.T;
	right_encoder.speed=ANGLE_TO_RADIAN*TIM_TIM5*PWMToDegree/right_encoder.T;
	
	left_encoder.degree += left_encoder.encoder_temp;
	right_encoder.degree += right_encoder.encoder_temp;
	
	if (left_encoder.degree>360){left_encoder.degree-=360;left_encoder.circle_cnt++;}
	else if(left_encoder.degree<0){left_encoder.degree+=360;left_encoder.circle_cnt--;}
	
	if (right_encoder.degree>360){right_encoder.degree-=360;right_encoder.circle_cnt++;}
	else if(right_encoder.degree<0){right_encoder.degree+=360;right_encoder.circle_cnt--;}
}
