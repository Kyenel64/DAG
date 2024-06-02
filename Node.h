#pragma once

#include "Port.h"

static uint32_t hashIndex = 0;

using UUID = uint32_t;

class Node
{
public:
	Node() : m_NodeID(hashIndex) { hashIndex++; };
	virtual ~Node() = default;

	virtual void Evaluate() = 0;

	UUID GetNodeID() const { return m_NodeID; }

	InputPort& GetInputPort(uint32_t index) { return m_InputPorts[index]; }
	OutputPort& GetOutputPort(uint32_t index) { return m_OutputPorts[index]; }

protected:
	std::vector<InputPort> m_InputPorts;
	std::vector<OutputPort> m_OutputPorts;

private:
	UUID m_NodeID;
};

class EndNode : public Node
{
public:
	EndNode()
	{
		InputPort inputPort(this);
		m_InputPorts.push_back(inputPort);
	};

	virtual ~EndNode() = default;

	void Evaluate() override
	{
		value = m_InputPorts[0].GetIncomingValue()->IntValue;
	}

	int GetValue() { return value; }

private:
	int value;
};

class IntNode : public Node
{
public:
	IntNode(int val)
	{
		m_OutputPorts.resize(1);

		PortData data;
		data.IntValue = val;
		OutputPort outputPort(this);
		outputPort.SetValue(data);
		m_OutputPorts[0] = outputPort;
	}
	virtual ~IntNode() = default;

	void Evaluate() override {}
};

class MultiplyNode : public Node
{
public:
	MultiplyNode()
	{
		m_InputPorts.resize(2);
		m_OutputPorts.resize(1);

		InputPort inputPort1(this);
		m_InputPorts[0] = inputPort1;
		InputPort inputPort2(this);
		m_InputPorts[1] = inputPort2;

		OutputPort outputPort(this);
		m_OutputPorts[0] = outputPort;
	}

	virtual ~MultiplyNode() = default;

	void Evaluate() override
	{
		PortData data;
		data.IntValue = m_InputPorts[0].GetIncomingValue()->IntValue * m_InputPorts[1].GetIncomingValue()->IntValue;
		m_OutputPorts[0].SetValue(data);
	}
};