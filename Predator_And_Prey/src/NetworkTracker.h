#pragma once
#include "NeuralNetwork.h"
#include <chrono>

class NetworkTracker
{
private:
	NeuralNetwork m_bestPreyNetwork;
	NeuralNetwork m_bestPredatorNetwork;
	std::chrono::duration<double> m_preyAliveTime;
	std::chrono::duration<double> m_predatorAliveTime;
	int m_predatorPreyEaten = 0;

public:
	NetworkTracker()
	{
		m_preyAliveTime = std::chrono::duration<double>();
		m_predatorAliveTime = std::chrono::duration<double>();
	}

	void setPreyNetwork(NeuralNetwork preyNetwork)
	{
		m_bestPreyNetwork = preyNetwork;
	}

	NeuralNetwork* getPreyNetwork()
	{
		return &m_bestPreyNetwork;
	}

	void setPredatorNetwork(NeuralNetwork predatorNetwork)
	{
		m_bestPredatorNetwork = predatorNetwork;
	}

	NeuralNetwork* getPredatorNetwork()
	{
		return &m_bestPredatorNetwork;
	}

	void setPreyAliveTime(std::chrono::duration<double> time)
	{
		m_preyAliveTime = time;
	}

	std::chrono::duration<double> getPreyAliveTime()
	{
		return m_preyAliveTime;
	}

	void setPredatorAliveTime(std::chrono::duration<double> time)
	{
		m_predatorAliveTime = time;
	}

	std::chrono::duration<double> getPredatorAliveTime()
	{
		return m_predatorAliveTime;
	}

	void setPredatorPreyEaten(int preyEaten)
	{
		m_predatorPreyEaten = preyEaten;
	}

	int getPredatorPreyEaten()
	{
		return m_predatorPreyEaten;
	}
};

