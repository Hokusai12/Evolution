#include "NeuralNetwork.h"
#include <cmath>
#include <chrono>

#include<iostream>


NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(unsigned int input_size, unsigned int output_size)
{
	m_inputNodes = std::vector<Node>();
	m_outputNodes = std::vector<Node>();

	for (int i = 0; i < input_size; i++)
	{
		m_inputNodes.push_back(Node());
	}
	for (int j = 0; j < output_size; j++)
	{
		m_outputNodes.push_back(Node());
	}
}

NeuralNetwork::NeuralNetwork(unsigned int input_size, unsigned int output_size, unsigned int hidden_node_size, unsigned int hidden_node_count)
{
	m_inputNodes = std::vector<Node>();
	m_outputNodes = std::vector<Node>();
	for (int i = 0; i < hidden_node_size; i++)
	{
		std::vector<Node> hiddenNode = std::vector<Node>();
		for (int j = 0; j < hidden_node_count; j++)
		{
			hiddenNode.push_back(Node());
		}
		m_hiddenInputNodes.push_back(hiddenNode);
	}

	for (int i = 0; i < input_size; i++)
	{
		m_inputNodes.push_back(Node());
	}
	for (int j = 0; j < output_size; j++)
	{
		m_outputNodes.push_back(Node());
	}
}

void NeuralNetwork::initializeRandomWeights()
{

	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < m_hiddenInputNodes.size(); i++)
	{
		for (int j = 0; j < m_hiddenInputNodes.at(i).size(); j++)
		{
			m_hiddenInputNodes.at(i).at(j).inputWeights.clear();

			if (i == 0)
			{
				for (int l = 0; l < m_inputNodes.size(); l++)
				{
					m_hiddenInputNodes.at(i).at(j).inputWeights.push_back(((rand() % 2000) - 1000) / 200.f);
				}
				continue;
			}
			for (int k = 0; k < m_hiddenInputNodes.at(i-1).size(); k++)
			{
				m_hiddenInputNodes.at(i).at(j).inputWeights.push_back(((rand() % 2000) - 1000) / 200.f);
			}
		}
	}
	for (int i = 0; i < m_outputNodes.size(); i++)
	{
		m_outputNodes.at(i).inputWeights.clear();

		if (m_hiddenInputNodes.size() > 0)
		{
			for (int j = 0; j < m_hiddenInputNodes.at(m_hiddenInputNodes.size() - 1).size(); j++)
			{
				m_outputNodes[i].inputWeights.push_back(((rand() % 2000) - 1000) / 200.f);
			}
		}
		else
		{
			for (int j = 0; j < m_inputNodes.size(); j++)
			{
				m_outputNodes[i].inputWeights.push_back(((rand() % 2000) - 1000) / 200.f);
			}
		}
	}
}

void NeuralNetwork::initializeWithBase(NeuralNetwork* base)
{
	std::srand(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < m_hiddenInputNodes.size(); i++)
	{
		for (int j = 0; j < m_hiddenInputNodes.at(i).size(); j++)
		{
			m_hiddenInputNodes.at(i).at(j).inputWeights.clear();

			if (i == 0)
			{
				for (int l = 0; l < m_inputNodes.size(); l++)
				{
					m_hiddenInputNodes.at(i).at(j).inputWeights.push_back(base->m_hiddenInputNodes.at(i).at(j).inputWeights.at(l) + (((std::rand() % 2000) - 1000) / 500.f));
				}
				continue;
			}
			for (int k = 0; k < base->m_hiddenInputNodes.at(i-1).size(); k++)
			{
				m_hiddenInputNodes.at(i).at(j).inputWeights.push_back(base->m_hiddenInputNodes.at(i).at(j).inputWeights.at(k) + (((std::rand() % 2000) - 1000) / 500.f));
			}
		}
	}
	for (int i = 0; i < base->m_outputNodes.size(); i++)
	{
		m_outputNodes.at(i).inputWeights.clear();

		if (base->m_hiddenInputNodes.size() > 0)
		{
			for (int j = 0; j < base->m_hiddenInputNodes.at(base->m_hiddenInputNodes.size() - 1).size(); j++)
			{
				m_outputNodes[i].inputWeights.push_back(base->m_outputNodes.at(i).inputWeights.at(j) + (((std::rand() % 2000) - 1000) / 500.f));
			}
		}
		else
		{
			for (int j = 0; j < m_inputNodes.size(); j++)
			{
				m_outputNodes[i].inputWeights.push_back(base->m_outputNodes.at(i).inputWeights.at(j) + (((std::rand() % 2000) - 1000) / 500.f));
			}
		}
	}
}

void NeuralNetwork::setColumnValues(std::vector<Node>& leftColumn, std::vector<Node>& rightColumn)
{
	for (int i = 0; i < rightColumn.size(); i++)
	{
		float valueSum = 0.f;
		for (int j = 0; j < leftColumn.size(); j++)
		{
			float sum = leftColumn.at(j).value * rightColumn.at(i).inputWeights.at(j);

			valueSum += sum;
		}
		rightColumn.at(i).value = 1 / (1 + std::exp(valueSum * -1));
	}
}

void NeuralNetwork::computeOutput()
{
	if (m_hiddenInputNodes.size() == 0)
	{
		setColumnValues(m_inputNodes, m_outputNodes);
	}
	else
	{
		for (int i = 0; i < m_hiddenInputNodes.size(); i++)
		{
			if (i == 0)
			{
				setColumnValues(m_inputNodes, m_hiddenInputNodes.at(i));
			}
			else
			{
				setColumnValues(m_hiddenInputNodes.at(i - 1), m_hiddenInputNodes.at(i));
			}
		}
		setColumnValues(m_hiddenInputNodes.at(m_hiddenInputNodes.size() - 1), m_outputNodes);
	}
}

void NeuralNetwork::setInputValues(std::vector<float>& inputValues)
{
	for (int i = 0; i < inputValues.size(); i++)
	{
		m_inputNodes[i].value = inputValues[i];
	}
}

std::vector<float> NeuralNetwork::getOutputs(std::vector<float>& inputValues)
{
	setInputValues(inputValues);
	computeOutput();
	std::vector<float> outputValues;
	for (int i = 0; i < m_outputNodes.size(); i++)
	{
		outputValues.push_back(m_outputNodes.at(i).value);
	}

	return outputValues;
}
