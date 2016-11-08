/*
Name:    neuralDuino.ino
Created: 10/28/2016 6:08:18 PM
Author:  Pranav
*/
#include "neuralDuino.h"
//create the total no. of neurons required in the network including all layers
neuron node1,node2,node3,node4,node5;
/*
	



*/
/*
this is a user defined function for the user to design and join his own special
neurons in his/her own special way

*/
void setupNeuralNetwork(){
	

}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	//these are normalized inputs
	float input[NUM_SYN] = { 0.5, 0.6, 0.8, 0.9, 0.5 };

	for (byte i = 0; i < 10; i++){
		node1.getOutput(input);
		node1.adjustWeights(10, 0.1);
		delay(500);
	}
	node1.printWeights();
}

// the loop function runs over and over again until power down or reset
void loop() {

	delay(2000);
}
