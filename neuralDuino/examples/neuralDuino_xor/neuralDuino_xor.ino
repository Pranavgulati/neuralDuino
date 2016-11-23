/*
Name:    neuralDuino.ino
Created: 10/28/2016 6:08:18 PM
Author:  Pranav
*/
#include "neuralDuino.h"
#define NUM_SET 4
#define NUM_OUT_NODES 1
//create the total no. of neurons required in the network including all layers
neuron node1,node2,node3,node4;
/*
see the example image for configuration
this is a user defined function for the user to design and join his own special
neurons in his/her own special way
*/

float sigmoidFn(float in,byte isDerivative){
  return isDerivative==HIGH?sigmoidDerivative(in):sigmoid(in);
  }
float linear(float in,byte isDerivative){
  return isDerivative==HIGH?1:in;
  }
  
void setupNeuralNetwork(){
  
	//node1 and node2 are input  nodes
	node1.setActivationFn(&sigmoidFn);
  node2.setActivationFn(&sigmoidFn);
  node3.setActivationFn(&linear);
  node4.setActivationFn(&sigmoidFn);
 
  node3.connectInput(&node1);
  node3.connectInput(&node2);

  node3.connectInput(&node4);
  //configure bias node as output =1
	node4.setOutput(1);
	//the network has been configured 
  Serial.println("NN setup done");
}
   //these are normalized inputs
  float input[NUM_SET][NUM_SYN] = {
                                  {0, 0,1},
                                  {0, 1,1},
                                  {1, 0,1},
                                  {1, 1,1},
                                  };

void layerAdjustWeights(){
  //now the user has to call backpropagate on every 
//these can be skipped but just for testing
               node3.adjWeights();
               node2.adjWeights();
               node1.adjWeights();
     
  }
void learn(){
//output can never be negative since 
//it is the output of a sigmoid function
  float output[NUM_SET]  ={0,1,1,0};
  for(int i=0;i<1000;i++){
    for(byte k=0;k<NUM_SET;k++){
        //send the input values to the input nodes
        node1.setInput(input[k]);
        node2.setInput(input[k]);
        //now ask for the output from the output node
        //set the desired output in the result node
        node3.getOutput();
        node3.setDesiredOutput(output[k]);
        for (byte i=0;i<NUM_OUT_NODES;i++){
            //depending on all the output nodes call each of their adjust weights
            //for them to set the betas of the preious layers
               node3.backpropagate();
               Serial.println("--");
          }
               node1.backpropagate();
               node2.backpropagate();
               Serial.println("----");
        //now adjust the weights by backpropogating through the network
    } 
    layerAdjustWeights();
  } 
}

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

  Serial.print("Number of synapses for input = ");
  Serial.println(NUM_SYN);
  //the following 2 function calls are user defined as per convenience
	setupNeuralNetwork();
  learn();
  Serial.println("learn done");
  Serial.flush();

	node1.printWeights();
	node2.printWeights();
	node3.printWeights();

  node1.setInput(input[0]);
  node2.setInput(input[0]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
  Serial.println("----");
 
  node1.setInput(input[1]);
  node2.setInput(input[1]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input[2]);
  node2.setInput(input[2]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input[3]);
  node2.setInput(input[3]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 
}

// the loop function runs over and over again until power down or reset
void loop() {

	delay(2000);
}
