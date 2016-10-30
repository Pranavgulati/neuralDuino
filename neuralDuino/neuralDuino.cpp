#include "neuralDuino.h"

int neuralDuino::getOutput(float input[]){
	int sum= 0;
	neuralDuino::__input = input;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * input[i]);
	}
	neuralDuino::output = sum;
	return sum;
}

void neuralDuino::adjustWeights(int desiredOutput,float speed){	
	int error = desiredOutput - neuralDuino::output;
#ifdef DISPLAY_ERROR
	Serial.println(error);
#endif
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = synWeight[i] + (int)(speed * (error * __input[i]));
	}
}