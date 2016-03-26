/*
 * MouseWheel.h
 *
 *  Created on: Mar 14, 2016
 *      Author: rexadmin
 */

#ifndef MOUSEWHEEL_H_
#define MOUSEWHEEL_H_

#include"API.h"

#endif /* MOUSEWHEEL_H_ */

#define MOUSEWHEEL_NUMBER 		3
#define TRAINING_SET_SIZE 		9
#define TRAINING_SET_MIN_SIZE	9
#define TRAINING_TIME			5000

typedef struct mouseWheel
{

	float *xConstants;
	float *yConstants;
	float *angleConstants;
	Encoder *mouseWheels;
	float xPosition;
	float yPosition;
	float rotation;
	int mousewheelNumber;
}mouseWheel;


typedef struct trainingSet
{
	int mousewheelNumber;
	int trainingSetSize;
	float **actualReadings;
}trainingSet;

mouseWheel mouseWheelInit(int mouseWheels, Encoder *inputs, float *xCoef, float *yCoef, float *rotCoef);

void mouseWheelReset(mouseWheel tracker);

size_t trainMouseWheel(mouseWheel mouse, int trainingSetSize, const char *fileName);

