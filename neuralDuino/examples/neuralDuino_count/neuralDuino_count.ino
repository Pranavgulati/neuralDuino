#include "neuralDuino.h"
/*
 * the no of training data sets available 
 * on which the  model is to be trained 
 * this is user defined and therfore in the main sketch
*/
#define NUM_SET 4
#define NUM_SYN 3
/* this is also user dependent present only for layer Management functions */
#define NUM_OUT_NODES 1
//create the total no. of neurons required in the network
//including all layers and one node for bias
neuron node1,node2,node3,node4;
/*
this is a user defined function for the user to design and join their own special
neurons in their own special way

PRE-Requisites
1. Main Sketch shall define an activation function of the type
    "float funcName(float input,byte isDerivative)" which returns
    the derivative when isDerivative is HIGH

2. Any function that sets Up the network connections and activation functions for each neuron

*/

float sigmoidFn(float in,byte isDerivative){
  return isDerivative==HIGH?sigmoidDerivative(in):sigmoid(in);
  }
float linear(float in,byte isDerivative){
  return isDerivative==HIGH?1:in;
  }
  
void setupNeuralNetwork(){

  node1.begin(3);
  node2.begin(3);
  node3.begin(3);
  node4.begin(0);
  //node1 and node2 are input  nodes
  node1.setActivationFn(&sigmoidFn);
  node2.setActivationFn(&sigmoidFn);
  //node3 is output node
  node3.setActivationFn(&linear);
  //node4 is bias node
  node4.setActivationFn(&sigmoidFn);

 //making neuron connections
  node3.connectInput(&node1);
  node3.connectInput(&node2);
  node3.connectInput(&node4);

  //configure bias node as output = 1
  node4.setOutput(1);
  //the network has been configured 
  Serial.println("NN setup done");
}
   //these are normalized inputs
  float input1[NUM_SET][NUM_SYN] = {
             //{binary input, dummy input, bias for input nodes}
                                  {0, 0,1},
                                  {1, 0,1},
                                  {0, 0,1},
                                  {1, 0,1},
                                  };
  float input2[NUM_SET][NUM_SYN] = {
                                  {0, 0,1},
                                  {0, 0,1},
                                  {1, 0,1},
                                  {1, 0,1},
                                  };
void learn(){
//output can never be negative since 
//it is the output of a sigmoid function
  float output[NUM_SET]  ={1,2,3,4};
  for(unsigned int i=0;i<500;i++){
    for(byte k=0;k<NUM_SET;k++){
        //send the input values to the input nodes
        //the input array is of finite length configurable by library header parameter NUM_SYN
        node1.setInput(input1[k]);
        node2.setInput(input2[k]);
              //now ask for the output from the output nodes one by one 
              //set the desired output in the output nodes only
              //call backpropagate to bkprpg8 to only 1 level behind the calling nodes
               node3.getOutput();
               node3.setDesiredOutput(output[k]);
               node3.backpropagate();
        //call adjustWeights for all nodes after backrprp8n is done for every node
        node3.adjWeights();
        node2.adjWeights();
        node1.adjWeights();
    }
  } 
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  setupNeuralNetwork();
  //print the inital weights if reqd
  node1.printWeights();
  node2.printWeights();
  node3.printWeights();
  delay(500);
  learn();
  Serial.println("learn done");
  Serial.flush();
  Serial.println(millis());
  node1.printWeights();
  node2.printWeights();
  node3.printWeights();


//TESTING the learned model
  node1.setInput(input1[0]);
  node2.setInput(input2[0]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
  Serial.println("----");
 
  node1.setInput(input1[1]);
  node2.setInput(input2[1]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input1[2]);
  node2.setInput(input2[2]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 node1.setInput(input1[3]);
  node2.setInput(input2[3]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node3.getOutput());
 Serial.println("----");

 
}

// the loop function runs over and over again until power down or reset
void loop() {
  delay(2000);
}
