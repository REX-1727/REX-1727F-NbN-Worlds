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

	float xConstants[MOUSEWHEEL_NUMBER];
	float yConstants[MOUSEWHEEL_NUMBER];
	float angleConstants[MOUSEWHEEL_NUMBER];
	Encoder mouseWheels[MOUSEWHEEL_NUMBER];
	float xPosition;
	float yPosition;
	float rotation;
}mouseWheel;


typedef struct trainingSet
{
	float actualReadings[MOUSEWHEEL_NUMBER][TRAINING_SET_SIZE];
}trainingSet;

mouseWheel mouseWheelInit(Encoder inputs[MOUSEWHEEL_NUMBER],
		float xCoef[MOUSEWHEEL_NUMBER],
		float yCoef[MOUSEWHEEL_NUMBER],
		float rotCoef[MOUSEWHEEL_NUMBER]);

void mouseWheelReset(mouseWheel tracker);

size_t trainMouseWheel(mouseWheel mouse, const char *fileName);

