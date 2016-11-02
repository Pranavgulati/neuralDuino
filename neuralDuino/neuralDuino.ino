/*
 Name:		neuralDuino.ino
 Created:	10/28/2016 6:08:18 PM
 Author:	Pranav
*/
#include "neuralDuino.h"

neuralDuino node1;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	//these are normalized inputs
	float input[NUM_SYN] = { 0.5, 0.6, 0.8, 0.9, 0.5 };
	node1.getOutput(input);
	for (byte i = 0; i < 10; i++){
		node1.adjustWeights(5, 0.1);
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("do this");
}
