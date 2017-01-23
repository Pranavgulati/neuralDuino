#include "neuralDuino.h"
/*
 * the no of training data sets available 
 * on which the  model is to be trained 
 * this is user defined and therfore in the main sketch
*/
#define NUM_SET 4
/* this is also user dependent present only for layer Management functions */
#define NUM_OUT_NODES 1
//create the total no. of neurons required in the network
//including all layers and one node for bias
neuron node1,node2,node3,node4,node5,node6;
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
  //no input is given to these neurons,instead their output is directly set
  node1.begin(0);
  node2.begin(0);
  //always include the bias in counting the no. of synapses required
  node3.begin(3);
  node4.begin(3);
  node5.begin(3);
  node6.begin(0);
  //node1 and node2 are input  nodes
  node1.setActivationFn(&linear);
  node2.setActivationFn(&linear);
  //node 3 is hidden layer
  node3.setActivationFn(&sigmoidFn);
  //node 4 is output node
  node4.setActivationFn(&sigmoidFn);
  //node5 is bias node
  node5.setActivationFn(&sigmoidFn);
  node6.setActivationFn(&sigmoidFn);

 //making neuron connections
  node5.connectInput(&node3);
  node5.connectInput(&node4);
  node5.connectInput(&node6);
  
  node4.connectInput(&node1);
  node4.connectInput(&node2);
  node4.connectInput(&node6);
  
  node3.connectInput(&node1);
  node3.connectInput(&node2);
  node3.connectInput(&node6);

  //configure bias node as output = 1
  node6.setOutput(1);
  //the network has been configured 
  Serial.println("NN setup done");
 
}
   //these are normalized inputs
  float input1[NUM_SET] = {0,1,0,1};
  float input2[NUM_SET] = {0,0,1,1};

void learn(){
  float output[NUM_SET]  ={0,0,0,1};
  for(unsigned int i=0;i<3000;i++){
    for(byte k=0;k<NUM_SET;k++){
        //send the input values to the input nodes
        //the input array is of finite length configurable by library header parameter NUM_SYN
        node1.setOutput(input1[k]);
        node2.setOutput(input2[k]);
              //now ask for the output from the output nodes one by one 
              //set the desired output in the output nodes only
              //call backpropagate to bkprpg8 to only 1 level behind the calling nodes
               node5.getOutput();
               node5.setDesiredOutput(output[k]);
               node5.backpropagate();
               
        //call adjustWeights for all nodes after backrprp8n is done for every node
        node5.adjWeights();
        node4.adjWeights();
        node3.adjWeights();
    }
  } 
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  setupNeuralNetwork();
  //print the inital weights if reqd
  node3.printWeights();
  node4.printWeights();
  delay(500);
  learn();
  Serial.println("learn done");
  Serial.flush();
  Serial.println(millis());
  node3.printWeights();
  node4.printWeights();

//TESTING the learned model
node1.setOutput(input1[0]);
node2.setOutput(input2[0]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node5.getOutput());
  Serial.println("----");
 
node1.setOutput(input1[1]);
node2.setOutput(input2[1]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

node1.setOutput(input1[2]);
node2.setOutput(input2[2]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

node1.setOutput(input1[3]);
node2.setOutput(input2[3]);
 Serial.println(node1.getOutput());
 Serial.println(node2.getOutput());
 Serial.println(node5.getOutput());
 Serial.println("----");

 
}

// the loop function runs over and over again until power down or reset
void loop() {
  delay(2000);
}
