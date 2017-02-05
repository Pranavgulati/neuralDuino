#ifndef __neuralDuino_h__
#define __neuralDuino_h__

#define DEBUG 0
#define DISPLAY_ERROR 1
#define LEARNING_RATE 0.1
#define MOMENTUM 0.1
#define SPEED LEARNING_RATE
#define FALSE LOW
#define TRUE HIGH

#include "Arduino.h"
#define sigmoid(x)           (1.0 / (1.0 + (float)exp(-(float)(x))))
#define sigmoidDerivative(x) ((float)((x)*(1.0-(x)))) 

/*
	types of neurons can be classified using the 2 begin() parameters noConnections and noInputs

									noConnections	noInputs
	hybrid (most inefficient)		LOW				LOW			(DEFAULT) //leaves the control to the programmer
	intermediate neuron				LOW				HIGH
	bias							HIGH			HIGH
	input neuron					HIGH			LOW

*/


/*
	TODO:
	-too many float calculations consider optimizing /removing these as well
*/
typedef float (*activFn)(float,byte);

class neuron{

public:
	//constructor
	neuron();
	/*
	synWeight holds the weight of each synapase that is INCOMING for that neuron
	the length of synWeight is decided by the begin() function where mem alloc 
	takes place.
	*/
	float *synWeight;
	/*stores the previous change ini weight for each synapse, ONLY required for 
	momentum functionality
	*/
	float *prevDelWeight;
	/*
	for a neuron to which no other neurons are connected an input may be specified
	this implies that neuron will have inputs defined by the user instead of being 
	the output of other neurons
	*/
	float *input;
	/*
	the second way to have inputs is to have output of some other neurons feed into 
	this neuron inNodes stores the address of every neuron which is connected to this
	neuron and asks for the output from each of those to calculate its output
	*/
	neuron **inNodes; //array of pointers of type neuron
	/*
	stores the output of this neuron
	*/
	float output;
	/*
	counts the number of neurons that are connected to this neuron using connectInput()
	be advised this DOES NOT keep count of the inputs specified
	by the programmer by the setInput() function
	*/
	byte inCount ; //input Nodes are only counted 
	/*
	keeps count of the inputs specified by setInput() and begin()
	this counts the number of float array type inputs and not the connectInput() ones
	*/
	byte numSynapse;
	/*
	associates an activation function for this neuron, user sets the address of any activation 
	function using setActivationFn()
	*/
	activFn activation;

	float beta; //just another backpropagation constant

	/*
	to prevent memory fragmentation while retaining flexibility the begin function
	allocates memory one time only, while it is possible to do away with this
	and have completely dynamic allocn and reallocn but it is not advisable because the RAM may get
	fragmented

	ARGs:
	noConnections : implies that this neuron will not have any connections coming into it
                    when noConnections = HIGH, this doesnt allocate memory for the same
	noInputs	  : implies that this neuron will not have any float inputs coming into it from the user
                    when noInputs = HIGH, this doesnt allocate memory for the same
	these are optional arguments for those people who know what they are doing 
	*/
	void begin(byte num_syn, byte noConnections = FALSE, byte noInputs = FALSE);
	/*
	adjust weights according to the update rule
	*/
	void adjWeights();
	/*
	backpropagate the betas to the connected nodes only
	*/
	void backpropagate();
	/*
	setDesiredOUtput only valid for the last nodes
	*/
	byte setDesiredOutput(float desiredOutput);
	/*
	Set the constant input values for the input layer
	*/
	void setInput(float input[]);
	void setInput(int input[]);
	/*
	Set the constant output value mostly for the bias node only
	*/
	void setOutput(int value);
	/*
	print the final weights after learning has happened
	*/
	void printWeights();
	/*
	connect other nodes to this->node as inputs
	this function accepts one neuron pointer and adds to the
	list of input pointer from which output is taken as an input for this node
	*/
	void connectInput(neuron* inNode);
	/*
	get output from the input nodes	
	*/
	float getOutput();
	/*
	set the activation functionfor this->node
	*/
	void setActivationFn(activFn userFn);
};





#endif