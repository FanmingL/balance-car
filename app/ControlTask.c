#include "main.h"

uint32_t SystemTimeMs=0; 
float position_out=0,speed_out=0,pwm_out_left=0,pwm_out_right=0;
float exp_angle=0.0f,rotate_speed=0.0f;

static void ModeTask(void)				//前进、后退、向左转、向右转、停止模式
{
	if (ControlMode==1){
		rotate_speed=0.0f;
		exp_angle=-MAX_EXP_ANGLE;
	}
	else if (ControlMode==2)
	{
			rotate_speed=0.0f;
			exp_angle=MAX_EXP_ANGLE;
	}
	else if (ControlMode==3){
		rotate_speed=MAN_ROTATE_SPEED;
		exp_angle=0.0f;
	}
	else if (ControlMode==4){
		rotate_speed=-MAN_ROTATE_SPEED;
		exp_angle=0.0f;
	}
	else if(ControlMode==5){
		rotate_speed=0.0f;
		exp_angle=0.0f;
	}
	else {
		rotate_speed=0.0f;
		exp_angle=0.0f;
	}

}

void Task_2ms(void)
{
	float inner_loop_time = GetInnerLoop(Task_2ms_Time)/1000000.0f;
	MPU6050_Read();
	MPU6050_Data_Prepare( inner_loop_time );
 	IMUupdate(0.5f *inner_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, //更新IMU
						mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);
}

void Task_5ms(void)
{	
	float inner_loop_time = GetInnerLoop(Task_5ms_Time)/1000000.0f;
	position_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														exp_angle,				//期望值（设定值）
														Pitch,			//反馈值
														&PitchP_arg, //PID参数结构体
														&PitchP_val,	//PID数据结构体
														1000			//integration limit，积分限幅
														 );			//输出	
	speed_out=  PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														position_out,				//期望值（设定值）
														mpu6050.Gyro.y*TO_ANGLE,			//反馈值
														&PitchS_arg, //PID参数结构体
														&PitchS_val,	//PID数据结构体
														1500			//integration limit，积分限幅
														 );			//输出	
	ModeTask();															//模式切换
	ChassisControl(inner_loop_time);
}

void Task_10ms(void)
{
	ANO_AK8975_Read();										//读取磁力计
}


void Task_20ms(void)
{
	float inner_loop_time = GetInnerLoop(Task_20ms_Time)/1000000.0f;//获取准确的执行周期
			if(!Mag_CALIBRATED)
		GPIO_ToggleBits(GPIOA,GPIO_Pin_5);						//磁力计校准阶段，LED停止闪烁
}

void ChassisControl(float T)							//底盘电机控制
{
		Refresh_Encoder();										//角度、角速度更新
		pwm_out_left=PID_calculate( T,            //周期
														0,				//前馈
														speed_out,				//期望值（设定值）
														left_encoder.speed,			//反馈值
														&Chassis_arg, //PID参数结构体
														&Chassis_left_val,	//PID数据结构体
														32			//integration limit，积分限幅
														 );			//输出	
		pwm_out_right=pwm_out_left-rotate_speed;
	/*pwm_out_right=PID_calculate( T,            //周期
														0,				//前馈
														speed_out,				//期望值（设定值）
														right_encoder.speed,			//反馈值
														&Chassis_arg, //PID参数结构体
														&Chassis_right_val,	//PID数据结构体
														200			//integration limit，积分限幅
														 );			//输出	*/
	pwm_out_left+=rotate_speed;	
	if (pwm_out_left<0){LEFT_DOWN();pwm_out_left=(-pwm_out_left);RIGHT_DOWN();}
	else {LEFT_UP();RIGHT_UP();}
	if (pwm_out_right<0){RIGHT_DOWN();pwm_out_right=(-pwm_out_right);}
	else {RIGHT_UP();}
	if (my_abs(Pitch)<50.0f)
	{SetPWMOut((int)(pwm_out_left),(int)pwm_out_right);}
	else {SetPWMOut(0,0);}
}

void ContolLoop(void)																//ControlLoop中将各种任务分为1ms、2ms、5ms、10ms、20ms任务
{
	SystemTimeMs++;
	if (SystemTimeMs%2==0)Task_2ms();
	if (SystemTimeMs%5==0)Task_5ms();
	if (SystemTimeMs%10==0)Task_10ms();
	if (SystemTimeMs%20==0)Task_20ms();
	DataTransferTask(SystemTimeMs);
}


