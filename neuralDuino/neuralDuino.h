#ifndef __neuralDuino_h__
#define __neuralDuino_h__
#include "settings.h"
#include "Arduino.h"
#define sigmoid(x)           (1.0 / (1.0 + (float)exp(-(float)(x))))
#define sigmoidDerivative(x) ((float)((x)*(1.0-(x)))) 
//add the bias support 
/*
	the neuralDuino lib creates one single perceptron object

	to prevent memory fragmentation memory is NOT dynamically allocated
	therefore NUM_SYN specifies the no. of synapses to the perceptron
	TODO:
	- no protection agains unintialized variables and inputs and outputs
	may require memory optimization
	too many float calculations consider optimizing /removing these as well
*/
typedef float (*activFn)(float,byte);
class neuron{
private:
	float synWeight[NUM_SYN];
	float output;
	float input[NUM_SYN];
	byte inCount = 0; //input Nodes are only counted 
	neuron* inNodes[NUM_SYN] ;
	activFn activation;
public:
	neuron();
	float desiredOutput;
	/*
	get the output of the percepron based on the input array
	*/
	float getOutput(float input[]);
	/*setDeesiredOUtput only valid for the last nodes

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
	float getOutput();
	
	void setActivationFn(activFn);
};





#endif