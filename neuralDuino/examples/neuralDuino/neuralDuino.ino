/*
Name:    neuralDuino.ino
Created: 10/28/2016 6:08:18 PM
Author:  Pranav
*/
#include "neuralDuino.h"
#define NUM_SET 4
//create the total no. of neurons required in the network including all layers
neuron node1,node2,node3,node4,node5,node6;
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
	//node3 node4 are hidden layer nodes
	node3.connectInput(&node1);
	node3.connectInput(&node2);
	node4.connectInput(&node1);
	node4.connectInput(&node2);
  node3.setActivationFn(sigmoidFn);
  node4.setActivationFn(sigmoidFn);

	//node5 is output node
	node5.connectInput(&node3);
	node5.connectInput(&node4);
  node5.setActivationFn(linear);

	//node6 is the bias which is for everyone so
	//do not give a bias input
	node3.connectInput(&node6);
	node4.connectInput(&node6);
	node5.connectInput(&node6);
 

	//configure bias node as output =1
	node6.setOutput(1);
	//the network has been configured 
}
   //these are normalized inputs
  float input1[NUM_SET][NUM_SYN] = {
                                  {100, 100, 100},
                                  {-100, -100, -100},
                                  {100, 100, 100},
                                  {-100, -100, -100},
                                  };
  float input2[NUM_SET][NUM_SYN] = {
                                  {-100, -100, -100},
                                  {100, 100, 100},
                                  {100, 100, 100},
                                 {-100, -100, -100},
                                  };

void learn(){
//output can never be negative since 
//it is the output of a sigmoid function
  float output[NUM_SET]  ={1,1,0,0};
  for(int i=0;i<1000;i++){
    for(byte k=0;k<NUM_SET;k++){
        //send the input values to the input nodes
        node1.setInput(input1[k]);
        node2.setInput(input2[k]);
        //set the desired output in the result node
        node5.setDesiredOutput(output[k]);
        //now ask for the output from the output node
        node5.getOutput();
        //now adjust the weights by backpropogating through the network
        node5.adjustWeights();
    }
    
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

	node1.printWeights();
	node2.printWeights();
	node3.printWeights();
	node4.printWeights();
	node5.printWeights();

  node1.setInput(input1[0]);
  node2.setInput(input2[0]);
 Serial.println(node3.getOutput());
 Serial.println(node4.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");
 
  node1.setInput(input1[1]);
  node2.setInput(input2[1]);
 Serial.println(node3.getOutput());
 Serial.println(node4.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

 
  node1.setInput(input1[2]);
  node2.setInput(input2[2]);
 Serial.println(node3.getOutput());
 Serial.println(node4.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

   node1.setInput(input1[3]);
  node2.setInput(input2[3]);
 Serial.println(node3.getOutput());
 Serial.println(node4.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

 
}

// the loop function runs over and over again until power down or reset
void loop() {

	delay(2000);
}
