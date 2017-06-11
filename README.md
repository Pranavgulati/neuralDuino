# neuralDuino
extendable perceptron library to build dynamic and reconfigurable Artificial Neural networks with back-propagation for arduino
#### **Note** : This library sways away from the conventional layered architecture that is taught in most youtube videos but it definitely supports it. Now you have the power to make you arduino actually LEARN from the environment.

# Pre-Requisites
- Tested using Arduino v1.6.5(windows) on UNO and Mega but should work on any board really and since it is based on C++ it can be ported to any platform easily

# Background
- this library imagines neural networks as connected individual neurons, obvious?, not so much because conventional libraries think of neural networks as layers of nodes.
- Due to the above ideology the library creates a neuron object that has synapses incoming to it and a single output going from it
- This design method gives the flexibility of making the most designer and complex ANN networks and have the control of designing and connecting the nodes to each other *on the fly* as well (Possibility of cascaded Neural Nets) with a very simple API
- Read the header file comments for general usage of the library and examples to use it

# Instructions
- Start with the examples, read the comments and move from there
- for any problems post an issue

# Features
- supports back-propagation , by calling backpropagate on a neuron the library backpropagates the beta to all the neurons that *this* neuron is onnected to
- Non layered architecture to support any ANN design required by the user
- choose your own activation function from the main sketch for each neuron individually
- connect the neurons to each other as you like
- each neuron is an object and whatever network you draw on the paper can be realized with this library
- Layer management (Construction and connections) given to the user with a default back-propagation and adjWeights implementation that needs to be called by the programmer as and when they wish.
- Lots of examples with different neural net architectures ;-P

Read the story on hackaday - http://bit.ly/neuralDuino_H
