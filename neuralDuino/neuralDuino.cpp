#include "neuralDuino.h"

int neuron::setInput(float inputVals[]){
	int sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}

	output = sigmoid(sum);
}

int neuron::getOutput(float inputVals[]){
	int sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}
	output = sigmoid(sum);
	return sum;
}
void neuron::adjustWeights(int desiredOutput, float speed){
	int error = desiredOutput - output;
#ifdef DISPLAY_ERROR
	Serial.println(error);
#endif
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = synWeight[i] + (float)(speed * (error * input[i]));
	}
}

void neuron::adjustWeights(int desiredOutput){
	int error = desiredOutput - output;
#ifdef DISPLAY_ERROR
	Serial.println(error);
#endif
	for (byte i = 0; i < NUM_SYN; i++){
		previouslayererror = previouslayererror + (synWeight[i] * sigmoidDerivative(output) * error);
	changeinweightof previouslayer = previouslayeroutput *error * sigmoidDerivative(output);
	newweights = newweights + (speed * deltaweight);
	}
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = synWeight[i] + (float)(SPEED * (error * input[i]));
	}
}

void neuron::printWeights(){

	for (byte i = 0; i < NUM_SYN; i++){
		Serial.print(synWeight[i]);
		Serial.print(",");
	}
	Serial.println();

}

int neuron::getOutput(){
	int sum = 0;
	if (inCount == 0){
#ifdef DEBUG
		Serial.println("reached the start nodes");
#endif
		//these nodes must be the initial nodes and should have their
		//constant input specified before this iteration
		return output;
	}
	else{
		for (byte i = 0; i < NUM_SYN && inNodes[i]!=NULL; i++){
			sum = sum + (synWeight[i] * inNodes[i]->getOutput());
		}
	}
	return  sigmoid(sum);;

}

void neuron::connectInput(neuron* inNode){
	inNodes[inCount++] = inNode;
}