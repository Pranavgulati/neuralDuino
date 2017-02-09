# neuralDuino
extendable perceptron library to build Artificial neural networks for Arduino

# Pre-Requisites
- Tested using Arduino v1.6.5(windows) on UNO and Mega but should work on any board really and since it is based on C++ it can be ported to any platform easily

# Background
- this library imagines neural networks as connected individual neurons, obvious?, not so much because conventional libraries think of neural networks as layers of nodes.
- Due to the above ideology the library creates a neuron object that has synapses incoming to it and a single output going from it
- Read the header file comments for general usage of the library and examples to use it

# Instructions
- Start with the examples, read the comments and move from there
- for any problems post an issue

# Features
- supports backpropagation , by calling backpropagate on a neuron the library backpropagates the beta to all the neurons that it this neuron is connected to
- Non layered architecture to support any ANN design required djfaknf the user
- choose your own activation function from the main sketch for each neuron individually
- connect the neurons to each other as you like
- each neuron is an object and whatever network you draw on the paper can be realized with this library
- layer management (backpropagation, adjusting weights etc.) given to the user 
- Lots of examples ;-P

the project is also on hackaday - http://bit.ly/neuralDuino_H
