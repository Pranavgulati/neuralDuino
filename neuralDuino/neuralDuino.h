#ifndef __neuralDuino_h__
#define __neuralDuino_h__
#include "settings.h"
#include "Arduino.h"

/*
	the neuralDuino lib creates one single perceptron object

	to prevent memory fragmentation memory is NOT dynamically allocated
	therefore NUM_SYN specifies the no. of synapses to the perceptron

*/
class neuralDuino{
private:
	float synWeight[NUM_SYN];
	int output;
	float* __input;
public:
	/*
	get the output of the percepron based on the input array
	*/
	int getOutput(float input[]);
	/*
	adjust weights according to the update rule 
	*/
	void adjustWeights(int desiredOutput,float speed);

};





#endif