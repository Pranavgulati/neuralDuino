#ifndef __neuralDuino_h__
#define __neuralDuino_h__
#include "settings.h"
#include "Arduino.h"
#define sigmoid(x)           (1.0 / (1.0 + (float)exp(-(double)(x))))
#define sigmoidDerivative(x) ((float)(x)*(1.0-(x))) 
//add the bias support 
/*
	the neuralDuino lib creates one single perceptron object

	to prevent memory fragmentation memory is NOT dynamically allocated
	therefore NUM_SYN specifies the no. of synapses to the perceptron

*/
class neuron{
private:
	float synWeight[NUM_SYN];
	int output;
	float input[NUM_SYN];
	float desiredOutput;
	byte inCount = 0;
	neuron* inNodes[NUM_SYN];
public:
	/*
	get the output of the percepron based on the input array
	*/
	int getOutput(float input[]);
	/*setDeesiredOUtput only valid for the last nodes
	may require memory optimization
	too many float calculations consider optimizing /removing these as well
	*/
	void setDesiredOutput(float desiredOutput);
	/*
	Set the constant input values for the input layer
	*/
	int setInput(float input[]);
	/*
	Set the constant output value mostly for the bias node only
	*/
	int setOutput(int value);


	/*
	adjust weights according to the update rule 
	*/
	void adjustWeights(int desiredOutput,float speed);

	void adjustWeights();
	/*
	print the final weights after learning has happened
	*/
	void printWeights();

	/*
	node configuration handler
	*/
	/*
	Add input nodes to this node
	this function accepts one neuron pointer and adds to the
	list of input pointer from which output is taken as an input for this node
	*/
	void connectInput(neuron* inNode);
	/*
	get output from the input nodes	
	*/
	int getOutput();
};





#endif