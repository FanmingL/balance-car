#ifndef _CONTROL_TASK_H_
#define _CONTROL_TASK_H_

#define MAX_EXP_ANGLE 5.0f
#define MAN_ROTATE_SPEED 50.0f

void ContolLoop(void);
void Task_2ms(void);
void Task_5ms(void);
void Task_10ms(void);
void Task_20ms(void);
void ChassisControl(float T);

#endif

