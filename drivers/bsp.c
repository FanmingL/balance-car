#include "main.h"

void All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);     
	LED_Configuration();
	TIM2_Configuration();
	PWM_Configuration();
	Encoder_Configuration();
	TIM6_Configuration();
	GPIO_Configuration();
	MotorEnable();
	Usart1_Init(115200);
	Usart2_Init(115200);
	Para_ResetToFactorySetup();
	PID_Para_Init();
	I2c_Soft_Init();
	Delay_ms(100);
	MPU6050_Init(20); 
	Delay_ms(100);
	ak8975_ok = !(ANO_AK8975_Run());
	Encoder_Start();
	TIM6_Start();
}



