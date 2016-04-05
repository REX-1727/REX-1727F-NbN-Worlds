/*
 * 1727B.c
 *
 *  Created on: Jan 29, 2016
 *      Author: Anton
 */
#include "1727F.h"

void basicDrive()
{

}

void flywheelInit(flywheel aFlywheel,float (*input)(),
		float (*target)(),
		float kP,
		float kI,
		float kD,
		int outputs[4])
{
	aFlywheel.parameters.input = input;
	aFlywheel.parameters.target = target;
	aFlywheel.parameters.timeOut = -1;
	aFlywheel.parameters.kP = kP;
	aFlywheel.parameters.kI = kI;
	aFlywheel.parameters.kD = kD;
}

void velocityReader(void *ignore)
{
	encoderReset(shooterEncoder);
	unsigned long startTime = 0;
	while(true)
	{
		startTime = millis();
		shooter.variables.velocityRaw = -encoderGet(shooterEncoder)*1000/20;
		shooter.variables.velocity = (shooter.variables.velocityRaw*(FLYWHEEL_CIRCUMFERENCE/12)/360.0);
		encoderReset(shooterEncoder);

		printf("%f\n\r",shooter.variables.velocity);
		taskDelayUntil(&startTime, MOTOR_REFRESH_TIME);
	}
}



void powerListener(void *params)
{

	if(true)
	{
		while(true)
		{
			if(main.rightDpad.axisValue == JOY_UP)
			{
				shooter.variables.power++;
				taskDelay(200);
			}
			else if(main.rightDpad.axisValue == JOY_DOWN)
			{
				shooter.variables.power--;
				taskDelay(200);
			}
			else if(main.rightDpad.axisValue == JOY_RIGHT)
			{
				shooter.variables.power += .5;
				taskDelay(200);
			}
			else if(main.rightDpad.axisValue == JOY_LEFT)
			{
				shooter.variables.power -= .5;
				taskDelay(200);
			}
			else if(main.leftDpad.axisValue == JOY_UP)
			{
				shooter.variables.power =26.5;
				taskDelay(200);
			}
			else if(main.leftDpad.axisValue == JOY_RIGHT)
			{
				shooter.variables.power =22;
				taskDelay(200);
			}
			else if(main.leftDpad.axisValue == JOY_LEFT)
			{
				shooter.variables.power =20;
				printf("debug");
				taskDelay(200);
			}
			else if(main.leftDpad.axisValue == JOY_DOWN)
			{
				shooter.variables.power =0;
				taskDelay(200);
			}
			if(shooter.variables.power<0)
			{
				shooter.variables.power =0;
				taskDelay(200);
			}

			shooter.variables.powerRaw = (shooter.variables.power)*(12/FLYWHEEL_CIRCUMFERENCE)*360;

			lcdPrint(uart1,1,"%f",shooter.variables.power);
			//printf("%f /n /r", leftFlywheel.variables.power);
			taskDelay(20);

		}
	}
}

void driveControl(void *params)
{

	while(true)
	{
		motorSet(LB,-main.leftVertical.axisValue);
		motorSet(LF,main.leftVertical.axisValue);
		motorSet(RB,-main.rightVertical.axisValue);
		motorSet(RF,main.rightVertical.axisValue);



		taskDelay(20);
	}
}


//PID HELPERS




float gyroTarget = 0;

float getPower()
{
	return (shooter.variables.powerRaw);
}


float getVel()
{
	return (shooter.variables.velocityRaw);
}

float getGyro()
{
	return (float)(gyroGet(gyro));
}

float getGyroTarget()
{
	return gyroTarget;
}

void setGyroTarget(float target)
{
	gyroTarget = target;
}

//Auton Functions

