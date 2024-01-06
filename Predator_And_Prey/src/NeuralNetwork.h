#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>


class NeuralNetwork
{
	struct Node
	{
		std::vector<float> inputWeights;
		float value, bias;
	};
	//Member Variables
private:
	std::vector<Node> m_inputNodes;
	std::vector<std::vector<Node>> m_hiddenInputNodes;
	std::vector<Node> m_outputNodes;

	//Member Functions
private:
	void setInputValues(std::vector<float>& inputValues);
	void computeOutput();
public:
	NeuralNetwork();
	NeuralNetwork(unsigned int input_size, unsigned int output_size);
	NeuralNetwork(unsigned int input_size, unsigned int output_size, unsigned int hidden_node_size, unsigned int hidden_node_count);
	void initializeRandomWeights();
	void initializeWithBase(NeuralNetwork* base);
	void setColumnValues(std::vector<Node>& leftColumn, std::vector<Node>& rightColumn);
	std::vector<float> getOutputs(std::vector<float>& inputValues);
};

