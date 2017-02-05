#include "neuralDuino.h"

neuron::neuron(){
	beta = 0;
	output = 0;
	inCount = 0;
	input = NULL;
	inNodes = NULL;
	synWeight = NULL;
	prevDelWeight = NULL;
}

void neuron::begin(byte num_syn, byte noConnections = FALSE, byte noInputs = FALSE){
	//deallocating previously allocated memory
	delete input;
	delete inNodes;
	delete synWeight;
	delete prevDelWeight;
	numSynapse = num_syn;
	if (num_syn == 0){
		// since no memory is requested just return
		return;
	}
	//allocating memory only if requested
	if (noInputs == FALSE		){	input = new float[num_syn];	   }
	if (noConnections == FALSE){ inNodes = new neuron*[num_syn]; }
	if (noConnections == FALSE || noInputs == FALSE){
		synWeight = new float[num_syn];
		prevDelWeight = new float[num_syn];
	}
	randomSeed(analogRead(A0));
	for (byte i = 0; i < num_syn; i++){
		synWeight[i] = (float)(((float)random(0, 100) / (float)100) - 0.2);
		prevDelWeight[i] = 0; //important to initialize allocated memory
	}
}

void neuron::setInput(float inputVals[]){
	float sum = 0;
	inCount = 0; //make sure that inCount is marked as zero for inputNodes
	
	for (byte i = 0; i < numSynapse; i++){
		sum = sum + (synWeight[i] * inputVals[i]);
		input[i] = inputVals[i]; //copying by value
	}
	output = activation(sum, LOW);
}

void neuron::setInput(int inputVals[]){
	float sum = 0;
	inCount = 0; //make sure that inCount is marked as zero for inputNodes

	for (byte i = 0; i < numSynapse; i++){
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
	if (inCount != 0){
		byte temp = inCount;
		while(temp!=0){
			temp--;
			sum = sum + (synWeight[temp] * inNodes[temp]->getOutput());
		}
		output = activation(sum, LOW);
	}	

//		Serial.print((int)this);
	//	Serial.print("->");
		//Serial.println(output);
	return  output;

}


byte neuron::setDesiredOutput(float desiredOutput){
	beta = desiredOutput - output;
#if DISPLAY_ERROR
	Serial.println((int)(beta*100));
#endif
	return ((int)(beta * 100) == 0 ? 1 : 0);
}

/*
this function is called on all those nodes that have an input node
*/
void neuron::backpropagate(){
	float myDelta = beta * activation(output, HIGH);
	if (inCount != 0){
		byte temp = inCount;
		while (temp--){
			//back propagating the delta to previous layer
			inNodes[temp]->beta = inNodes[temp]->beta + (synWeight[temp] * myDelta);
			//by this all the betas reacht the previous layer nodes as summed up
		}
	}

}
/*
this is called on every node after complete backpropagation is done for all nodes
*/
void neuron::adjWeights(){
	float myDelta = beta * activation(output, HIGH);
	if (inCount != 0){ //inNodes is filled up 
		byte temp = inCount;
		while (temp!=0){
			temp--;
			float delWeight = (SPEED * inNodes[temp]->output * myDelta);
			synWeight[temp] = synWeight[temp] + delWeight + MOMENTUM * prevDelWeight[temp];
			prevDelWeight[temp] = delWeight;
			//Serial.println(prevDelWeight[temp]);
			//Serial.flush();
		}
	}
	else{//inNodes is empty , therfore this is input node
		for (byte i = 0; i < numSynapse; i++){
			float  delWeight = (SPEED * input[i] * myDelta);
			synWeight[i] = synWeight[i] + delWeight + MOMENTUM * prevDelWeight[i];
			prevDelWeight[i] = delWeight;
			//Serial.println(prevDelWeight[i]);
			//Serial.flush();
		}
	}
#if DEBUG
	Serial.print((int)this);
	Serial.print("=this,beta=");
	Serial.print(beta);
	Serial.print(",out=");
	Serial.println(output);
	Serial.flush();
#endif
	beta = 0;
}

void neuron::printWeights(){
	for (byte i = 0; i < numSynapse; i++){
		Serial.print(synWeight[i]);
		Serial.print(",");
	}
	Serial.println();

}

void neuron::connectInput(neuron* inNode){

	inNodes[inCount] = inNode;
	inCount++;
#if DEBUG
	Serial.print((int)this);
	Serial.print(F(" : connected to :"));
	Serial.println((int)inNode);
#endif
	//Serial.println((int)inNodes[inCount-1]);
}

void neuron::setActivationFn(activFn userFn){
	this->activation = userFn;
	
#if DEBUG
	Serial.print(F("ActFN is "));
	Serial.println((int)userFn);
#endif
}