#include "neuralDuino.h"

neuron::neuron(){
	
	for (byte i = 0; i < NUM_SYN; i++){
		input[i] = 0;
		inNodes[i] = NULL;
		synWeight[i] = 0;
		prevDelWeight[i] = 0;
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
	output = activation(sum, LOW);
}

void neuron::setOutput(int value){
	output = value;
	inCount = 0;//only to be used for non input nodes like bias
}

float neuron::getOutput(){
	//this function is called once on the last layer neuron/neurons
	//therefore the output for each of these is stored inside these neurons
	//itself for future adjustment of weights
	//Serial.print("inCount is  ");
	//Serial.println(inCount);
	//Serial.flush();
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
		byte temp = inCount;
		while(temp--){
			sum = sum + (synWeight[temp] * inNodes[temp]->getOutput());
		}
		output = activation(sum, LOW);
	}

	#if DEBUG
		Serial.println(output);
	#endif
	return  output;

}


void neuron::setDesiredOutput(float desiredOutput){
	beta = desiredOutput - output;
	//Serial.print("inCount SDO is  ");
//	Serial.println((int)(beta*100));
	//Serial.flush();
}

/*
this function is called on all those nodes that have an input node
*/
void neuron::backpropagate(){
	//Serial.print("inCount bpo is  ");
	//Serial.println(inCount);
	//Serial.flush();
	float myDelta = beta * activation(output, HIGH);
	if (inCount != 0){
		byte temp = inCount;
		while (temp--){
			//back propagating the delta to previous layer
			inNodes[temp]->beta = inNodes[temp]->beta + (synWeight[temp] * myDelta);
			//by this all the betas reacht the previous layer nodes as summed up
		}
	}
#if DISPLAY_ERROR
	Serial.print(inCount);
	Serial.print(" ");
	Serial.print(beta);
	Serial.print(" ");
	Serial.print(output);
	Serial.println(" ");
	Serial.flush();
#endif
}
/*
this is called on every node after complete backpropagation is done for all nodes
*/
void neuron::adjWeights(){
	float myDelta = beta * activation(output, HIGH);
	if (inCount != 0){
		byte temp = inCount;
		while (temp--){
			//TRY A MINUS HERE IF IT DOESNT CONVERGE
			float  delWeight = (SPEED * inNodes[temp]->output * myDelta);
			synWeight[temp] = synWeight[temp] + delWeight + MOMENTUM * prevDelWeight[temp];
			prevDelWeight[temp] = delWeight;
			Serial.println(prevDelWeight[temp]);
			Serial.flush();
		}
	}
	else{
		for (byte i = 0; i < NUM_SYN; i++){
			//TRY A MINUS HERE IF IT DOESNT CONVERGE
			float  delWeight = (SPEED * input[i] * myDelta);
			synWeight[i] = synWeight[i] + delWeight + MOMENTUM * prevDelWeight[i];
			prevDelWeight[i] = delWeight;
			Serial.println(prevDelWeight[i]);
			Serial.flush();
		}
	}
	beta = 0;
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
	randomSeed(analogRead(A0));
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = (float)(((float)random(0, 100) / (float)100)-1);
	}
#if DEBUG
	//Serial.println((int)&inCount);
	//Serial.flush();
	Serial.println((int)this->activation);
	Serial.println(activation(10, false));
	Serial.flush();
#endif
}