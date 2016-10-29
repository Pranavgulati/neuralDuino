#ifndef __neuralDuino_h__
#define __neuralDuino_h__
#include "settings.h"

/*
	the neuralDuino lib creates one single perceptron object

	to prevent memory fragmentation memory is NOT dynamically allocated
	therefore NUM_SYN specifies the no. of synapses to the perceptron

*/
class neuralDuino{
private:
	int synWeight[NUM_SYN];
	int output;
public:
	/*
	get the output of the percepron based on the input array
	*/
	int getOutput(int input[]);


};





#endif