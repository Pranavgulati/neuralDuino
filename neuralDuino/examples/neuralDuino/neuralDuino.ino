/*
Name:    neuralDuino.ino
Created: 10/28/2016 6:08:18 PM
Author:  Pranav
*/
#include "neuralDuino.h"
//create the total no. of neurons required in the network including all layers
neuron node1,node2,node3,node4,node5,node6;
/*
see the example image for configuration
this is a user defined function for the user to design and join his own special
neurons in his/her own special way
*/
void setupNeuralNetwork(){
	//node1 and node2 are input  nodes
	//node3 node4 are hidden layer nodes
	node3.connectInput(&node1);
	node3.connectInput(&node2);
	node4.connectInput(&node1);
	node4.connectInput(&node2);

	//node5 is output node
	node5.connectInput(&node3);
	node5.connectInput(&node4);

	//node6 is the bias which is for everyone so
	node3.connectInput(&node6);
	node4.connectInput(&node6);
	node5.connectInput(&node6);

	//configure bias node as output =1
	node6.setOutput(1);
	//the network has been configured 
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	setupNeuralNetwork();
	//these are normalized inputs
	float input1[NUM_SYN] = {0.9, 0.8, 0.7 };
 float input2[NUM_SYN] = { 0.23, -0.45, 0.56 };
    //send the input values to the input nodes
    node1.setInput(input1);
    node2.setInput(input2);
    //set the desired output in the result node
    node5.setDesiredOutput(0.9);
 for (int i = 0; i < 300; i++){

		//now ask for the output from the output node
		node5.getOutput();
		//now adjust the weights by backpropogating through the network
		node5.adjustWeights();
	}
	node1.printWeights();
	node2.printWeights();
	node3.printWeights();
	node4.printWeights();
	node5.printWeights();
 Serial.println(node5.getOutput());
}

// the loop function runs over and over again until power down or reset
void loop() {

	delay(2000);
}
