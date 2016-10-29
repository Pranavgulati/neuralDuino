#include "neuralDuino.h"

int neuralDuino::getOutput(int input[]){
	int output = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		output = output + (synWeight[i] * input[i]);
	}
	return output;
}
