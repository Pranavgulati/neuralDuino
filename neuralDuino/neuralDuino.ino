/*
 Name:		neuralDuino.ino
 Created:	10/28/2016 6:08:18 PM
 Author:	Pranav
*/
#include "neuralDuino.h"

neuralDuino node1;

// the setup function runs once when you press reset or power the board
void setup() {
	float input[NUM_SYN] = { 0.5, 0.6, 0.8, 0.9, 0.5 };

}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("do this");
}
