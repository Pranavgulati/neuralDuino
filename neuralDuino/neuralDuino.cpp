#include "neuralDuino.h"

neuron::neuron(){
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = 1;
		input[i] = 0;
		inNodes[i] = NULL;
	}
	beta = 0;
	output = 0;
	inCount = 0;

}

void neuron::setInput(float inputVals[]){
	float sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}
	//input[NUM_SYN - 1] = 1;//addign bias to the input node
	output = activation(sum, LOW);

}

void neuron::setOutput(int value){
	output = value;
	inCount = 0;//only to be used for non input nodes like bias
}

float neuron::getOutput(float inputVals[]){
	float sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}
	output = activation(sum, LOW);
	return output;
}

float neuron::getOutput(){
	//this function is called once on the last layer neuron/neurons
	//therefore the output for each of these is stored inside these neurons
	//itself for future adjustment of weights
	//Serial.print("inCount is  ");
	//Serial.println(inCount);
	//Serial.flush();
	beta = 0;
	float sum = 0;
	if (inCount == 0){
		#if DEBUG
				Serial.print("RSN out ");
		#endif
		//these nodes must be the initial nodes and should have their
		//constant input specified before this iteration
		return output;
	}
	else{
		for (byte i = 0; inNodes[i] != NULL && i < NUM_SYN; i++){
			sum = sum + (synWeight[i] * inNodes[i]->getOutput());
		}
		output = activation(sum, LOW);
	}

	#if DEBUG
		Serial.println(output);
	#endif
	return  output;

}


void neuron::adjustWeights(int desiredOutput, float speed){
	//remove this asap
float myError = desiredOutput - output;
#if DISPLAY_ERROR
	Serial.println(error);
#endif
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = synWeight[i] + (float)(speed * (myError * input[i]));
	}
}


void neuron::setDesiredOutput(float desiredOutput){
	beta =  desiredOutput-output;
}

void neuron::adjustWeights(){
	#if DISPLAY_ERROR
		Serial.print(beta);
	#endif
		float delta = beta * activation(output, HIGH);
		if (inCount != 0){
			#if DEBUG
				Serial.println(" AW");
			#endif

			for (byte i = 0; inNodes[i] != NULL && i < NUM_SYN; i++){
				//back propagating the delta to previous layer
				inNodes[i]->beta = inNodes[i]->beta + (synWeight[i] * delta);
				//the following is correct for the output layer
				synWeight[i] = synWeight[i] + (SPEED * inNodes[i]->output * delta);
				//now the value that needs to be backpropogated is 
				// so inNodes[i]->beta += synWeight[i]*delta; 
				//by this all the betas reacht the previous layer nodes as summed up
			}
			//this is for now only for a single node output layer will implement for multi 
			//output layers later
			for (byte i = 0; inNodes[i] != NULL && i < NUM_SYN; i++){
				inNodes[i]->adjustWeights();
			}
		}
		else{
			#if DEBUG
						Serial.println(" RSN AW");
			#endif
			//incount is 0 therfore reached starting nodes or the bias node
			//bias node doesnt have any inputs therefore delta for it will be zero
						//###### will not adjust weights for the starting nodes
			for (byte i = 0; i < NUM_SYN; i++){
				synWeight[i] = synWeight[i] + (float)((float)SPEED * input[i] * delta);
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
	//Serial.println((int)inNodes[inCount-1]);
}

void neuron::setActivationFn(activFn userFn){
	this->activation = userFn;

#if DEBUG
	//Serial.println((int)&inCount);
	//Serial.flush();
	Serial.println((int)this->activation);
	Serial.println(activation(10, false));
	Serial.flush();
#endif
}