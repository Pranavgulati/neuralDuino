#include "neuralDuino.h"

int neuron::setInput(float inputVals[]){
	int sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}

	output = sigmoid(sum);
}
int neuron::setOutput(int value){
	output = value;
	inCount = 0;//only to be used for non input nodes like bias
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

int neuron::getOutput(){
	//this function is called once on the last layer neuron/neurons
	//therefore the output for each of these is stored inside these neurons
	//itself for future adjustment of weights
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
		for (byte i = 0; i < NUM_SYN && inNodes[i] != NULL; i++){
			sum = sum + (synWeight[i] * inNodes[i]->getOutput());
		}
	}
	output = sigmoid(sum);
	return  sigmoid(sum);

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


void neuron::setDesiredOutput(float desiredOutput){
	this->desiredOutput = desiredOutput;
}

void neuron::adjustWeights(){
	float myError = desiredOutput - output;
	#ifdef DISPLAY_ERROR
		Serial.println(myError);
	#endif
		if (inCount != 0){
			for (byte i = 0; i < NUM_SYN && inNodes[i]!=NULL; i++){
				inNodes[i]->desiredOutput = inNodes[i]->desiredOutput + (synWeight[i] * sigmoidDerivative(output) * myError);
				//can combine these two statements but this looks much more clear
				float delta = inNodes[i]->output * myError * sigmoidDerivative(output);
				synWeight[i] = synWeight[i] + (SPEED * delta);
				inNodes[i]->adjustWeights();
			}
		}
		else{
			//incount is 0 therfore reached starting nodes or the bias node
			for (byte i = 0; i < NUM_SYN; i++){
				float delta = input[i] * myError * sigmoidDerivative(output);
				synWeight[i] = synWeight[i] + (SPEED * delta);
			}
		}

}

void neuron::printWeights(){

	for (byte i = 0; i < NUM_SYN; i++){
		Serial.print(synWeight[i]);
		Serial.print(",");
	}
	Serial.println();

}


void neuron::connectInput(neuron* inNode){
	inNodes[inCount++] = inNode;
}