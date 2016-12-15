#ifndef __neuralDuino_h__
#define __neuralDuino_h__
#include "settings.h"
#include "Arduino.h"
#define sigmoid(x)           (1.0 / (1.0 + (float)exp(-(float)(x))))
#define sigmoidDerivative(x) ((float)((x)*(1.0-(x)))) 

/*
	to prevent fragmentation memory is allocated at construction for NUM_SYN sized arrays
	it is better since if its made dynamic malloc will happen on the fly that may result 
	in fragmented RAM memory and since this is intended for low power MCU it is not implemented

	TODO:
	- no protection agains unintialized variables and inputs and outputs
	may require memory optimization
	-too many float calculations consider optimizing /removing these as well
	- do away with NUM_SYN since that only specifies the number of inputs to input nodes
	- make settings.h a part of main sketch instead of the library
	
*/
typedef float (*activFn)(float,byte);

class neuron{

public:
	neuron();
	float synWeight[NUM_SYN];
	float prevDelWeight[NUM_SYN];
	float input[NUM_SYN];
	neuron* inNodes[NUM_SYN];

	float output;
	byte inCount = 0; //input Nodes are only counted 
	activFn activation;
	float beta; //just another backpropagation constant

	/*
	adjust weights according to the update rule
	*/
	void adjWeights();
	/*
	backpropagate the betas to the connected nodes only
	*/
	void backpropagate();
	/*
	setDeesiredOUtput only valid for the last nodes
	*/
	void setDesiredOutput(float desiredOutput);
	/*
	Set the constant input values for the input layer
	*/
	void setInput(float input[]);
	/*
	Set the constant output value mostly for the bias node only
	*/
	void setOutput(int value);
	/*
	print the final weights after learning has happened
	*/
	void printWeights();
	/*
	connect other nodes to this->node as inputs
	this function accepts one neuron pointer and adds to the
	list of input pointer from which output is taken as an input for this node
	*/
	void connectInput(neuron* inNode);
	/*
	get output from the input nodes	
	*/
	float getOutput();
	/*
	set the activation functionfor this->node
	*/
	void setActivationFn(activFn);
};





#endif