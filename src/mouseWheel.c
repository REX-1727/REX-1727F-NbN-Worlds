/*
 * mouseWheel.c
 *
 *  Created on: Mar 14, 2016
 *      Author: rexadmin
 */

#include "mouseWheel.h"
#include "rexAPI.h"
#include "1727F.h"
#include "math.h"
#include "API.h"


mouseWheel mouseWheelInit(Encoder inputs[MOUSEWHEEL_NUMBER],
		float xCoef[MOUSEWHEEL_NUMBER],
		float yCoef[MOUSEWHEEL_NUMBER],
		float rotCoef[MOUSEWHEEL_NUMBER])
{
	mouseWheel aMouseWheel;
	aMouseWheel.mouseWheels = inputs;
	aMouseWheel.xConstants = xCoef;
	aMouseWheel.yConstants = yCoef;
	aMouseWheel.angleConstants = rotCoef;
	aMouseWheel.xPosition = 0;
	aMouseWheel.yPosition = 0;
	aMouseWheel.rotation = 0;

	return aMouseWheel;
}

void mouseWheelReset(mouseWheel tracker)
{
	tracker.rotation = 0;
	tracker.yPosition = 0;
	tracker.rotation = 0;
}

float getXPosition(mouseWheel tracker)
{
	float XPosition;

	for(int i = 0; i<MOUSEWHEEL_NUMBER;i++)
	{
		XPosition += tracker.xConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return XPosition;
}

float getYPosition(mouseWheel tracker)
{
	float YPosition;

	for(int i = 0; i<MOUSEWHEEL_NUMBER;i++)
	{
		YPosition += tracker.yConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return YPosition;
}

float getRotation(mouseWheel tracker)
{
	float rotation;

	for(int i = 0; i<MOUSEWHEEL_NUMBER;i++)
	{
		rotation += tracker.angleConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return rotation;
}

size_t trainMouseWheel(mouseWheel mouse, const char *fileName)
{
	trainingSet aTrainingSet;
	for(int testRun = 0; testRun < TRAINING_SET_SIZE; testRun++)
	{
		unsigned long startTime = millis();
		while(millis() < startTime + TRAINING_TIME)
		{
			defaultDrive();
			delay(20);
		}
		stopAllMotors();
		delay(500);
		for(int encoderAxis = 0; encoderAxis < MOUSEWHEEL_NUMBER; encoderAxis++)
		{
			aTrainingSet.actualReadings[encoderAxis][testRun] = encoderGet(mouse.mouseWheels[encoderAxis]);
		}
	}
	FILE trainingSet_file = fopen(fileName,"w");
	size_t bytesWritten = fwrite(&aTrainingSet, sizeof(trainingSet), 1, trainingSet_file);
	fclose(trainingSet_file);

	return bytesWritten;
}



