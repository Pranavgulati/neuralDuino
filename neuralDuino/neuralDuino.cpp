#include "neuralDuino.h"

neuron::neuron(){
	for (byte i = 0; i < NUM_SYN; i++){
		input[i] = 0;
		inNodes[i] = NULL;
		synWeight[i] = INIT_WEIGHT;
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
/*
float neuron::getOutput(float inputVals[]){
	float sum = 0;
	for (byte i = 0; i < NUM_SYN; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}
	output = activation(sum, LOW);
	return output;
}
*/
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

/*
void neuron::adjustWeights(int desiredOutput, float speed){
	//remove this asap
float myError = desiredOutput - output;
#if DISPLAY_ERROR
Serial.println(myError);
#endif
	for (byte i = 0; i < NUM_SYN; i++){
		synWeight[i] = synWeight[i] + (float)(speed * (myError * input[i]));
	}
}
*/
void neuron::setDesiredOutput(float desiredOutput){
	beta = desiredOutput - output;
	//Serial.print("inCount SDO is  ");
	Serial.println((int)(beta*100));
	Serial.flush();
}
/*
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

void neuron::adjustWeights(int k){

	//NEWWWW

#if DISPLAY_ERROR
	Serial.print(beta);
#endif
	float delta = beta * activation(output, HIGH);
	if (inCount != 0){
		for (byte i = 0; inNodes[i] != NULL && i < NUM_SYN; i++){
			//back propagating the delta to previous layer
			inNodes[i]->beta = inNodes[i]->beta + (synWeight[i] * delta);
			//the following is correct for the output layer
			//TRY A MINUS HERE IF IT DOESNT CONVERGE
			synWeight[i] = synWeight[i] + (SPEED * inNodes[i]->output * delta);
			//now the value that needs to be backpropogated is 
			// so inNodes[i]->beta += synWeight[i]*delta; 
			//by this all the betas reacht the previous layer nodes as summed up
		}
	}
	else{
#if DEBUG
		Serial.println(" RSN AW");
#endif
		//incount is 0 therfore reached starting nodes or the bias node
		//bias node doesnt have any inputs therefore delta for it will be zero
		for (byte i = 0; i < NUM_SYN; i++){
			//TRY A MINUS SIGN HERE TOO
			synWeight[i] = synWeight[i] + (float)((float)SPEED * input[i] * delta);
		}
	}

}

*/
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
			synWeight[temp] = synWeight[temp] + (SPEED * inNodes[temp]->output * myDelta);
		}
	}
	else{
		for (byte i = 0; i < NUM_SYN; i++){
			//TRY A MINUS HERE IF IT DOESNT CONVERGE
			synWeight[i] = synWeight[i] + (SPEED * input[i] * myDelta);
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

#if DEBUG
	//Serial.println((int)&inCount);
	//Serial.flush();
	Serial.println((int)this->activation);
	Serial.println(activation(10, false));
	Serial.flush();
#endif
}