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


mouseWheel mouseWheelInit(int mouseWheels, Encoder *inputs, float *xCoef, float *yCoef, float *rotCoef)
{
	mouseWheel aMouseWheel;
	aMouseWheel.xConstants = malloc(sizeof(float)*mouseWheels);
	aMouseWheel.yConstants = malloc(sizeof(float)*mouseWheels);
	aMouseWheel.angleConstants = malloc(sizeof(float)*mouseWheels);
	aMouseWheel.mouseWheels = malloc(sizeof(Encoder)*mouseWheels);
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

	for(int i = 0; i<tracker.mousewheelNumber;i++)
	{
		XPosition += tracker.xConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return XPosition;
}

float getYPosition(mouseWheel tracker)
{
	float YPosition;

	for(int i = 0; i<tracker.mousewheelNumber;i++)
	{
		YPosition += tracker.yConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return YPosition;
}

float getRotation(mouseWheel tracker)
{
	float rotation;

	for(int i = 0; i<tracker.mousewheelNumber;i++)
	{
		rotation += tracker.angleConstants[i]*encoderGet(tracker.mouseWheels[i]);
	}
	return rotation;
}

size_t trainMouseWheel(mouseWheel mouse,int trainingSetSize, const char *fileName)
{
	trainingSet aTrainingSet;
	aTrainingSet.actualReadings = malloc(sizeof(float)*mouse.mousewheelNumber*trainingSetSize);
	for(int testRun = 0; testRun < trainingSetSize; testRun++)
	{
		unsigned long startTime = millis();
		while(millis() < startTime + TRAINING_TIME)
		{
			basicDrive();
			delay(20);
		}
		stopAllMotors();
		delay(500);
		for(int encoderAxis = 0; encoderAxis < mouse.mousewheelNumber; encoderAxis++)
		{
			aTrainingSet.actualReadings[encoderAxis][testRun] = encoderGet(mouse.mouseWheels[encoderAxis]);
		}
	}
	FILE *trainingSet_file = fopen(fileName,"w");
	size_t bytesWritten = fwrite(aTrainingSet.actualReadings, sizeof(aTrainingSet.actualReadings), 1, trainingSet_file);
	fclose(trainingSet_file);

	return bytesWritten;
}



