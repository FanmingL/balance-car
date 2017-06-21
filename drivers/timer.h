#ifndef _TIMER_H_
#define _TIMER_H_
#define Get_Time_Micros() (TIM2->CNT)
void TIM2_Configuration(void);
//uint32_t Get_Time_Micros(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void TIM6_Configuration(void);
void TIM6_Start(void);

#endif
