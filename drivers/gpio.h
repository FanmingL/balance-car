#ifndef _GPIO_H_
#define _GPIO_H_
void GPIO_Configuration(void);
#define LEFT_UP() \
									GPIO_ResetBits(GPIOB,GPIO_Pin_0);\
									GPIO_SetBits(GPIOB,GPIO_Pin_1);
#define LEFT_DOWN() \
									GPIO_SetBits(GPIOB,GPIO_Pin_0);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_1);
#define LEFT_STOP() \
									GPIO_ResetBits(GPIOB,GPIO_Pin_0);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_1);

#define RIGHT_UP() \
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);\
									GPIO_SetBits(GPIOD,GPIO_Pin_2);
#define RIGHT_DOWN() \
									GPIO_SetBits(GPIOC,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_2);
#define RIGHT_STOP() \
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);\
									GPIO_ResetBits(GPIOD,GPIO_Pin_2);

#define ALL_STOP() \
										LEFT_STOP();\
										RIGHT_STOP();
#define MotorEnable() GPIO_SetBits(GPIOE,GPIO_Pin_13);
#define MotorDisable() GPIO_ResetBits(GPIOE,GPIO_Pin_13);
#endif

