#ifndef _PWM_H_
#define _PWM_H_

void PWM_Configuration(void);
#define PWM_left TIM1->CCR1
#define PWM_right TIM1->CCR2

#define SetPWMOut(x,y) \
											PWM_left=x;\
											PWM_right=y;

#endif
