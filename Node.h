#pragma once

#include "Port.h"

static uint32_t hashIndex = 0;

using NodeID = uint32_t;

class Node
{
public:
	Node() : m_NodeID(hashIndex) { hashIndex++; };
	virtual ~Node() = default;

	// Runs the logic of the node and sets the output values if any exists.
	virtual void Evaluate() = 0;

	NodeID GetNodeID() const { return m_NodeID; }

protected:
	std::vector<InputPort> m_InputPorts;
	std::vector<OutputPort> m_OutputPorts;

private:
	NodeID m_NodeID;

public:
	friend class DAG;
};

class EndNode : public Node
{
public:
	EndNode()
	{
		InputPort inputPort;
		m_InputPorts.push_back(inputPort);
	};

	virtual ~EndNode() = default;

	void Evaluate() override
	{
		value = m_InputPorts[0].LinkedOutputPort->Value.IntValue;
	}

	int GetValue() { return value; }

private:
	int value;
};

class IntNode : public Node
{
public:
	IntNode()
	{
		m_OutputPorts.resize(1);

		OutputPort outputPort;
		outputPort.Value.IntValue = 10;
		m_OutputPorts[0] = outputPort;
	}
	virtual ~IntNode() = default;

	void SetValue(int val)
	{
		m_OutputPorts[0].Value.IntValue = val;
	}

	void Evaluate() override {}
};

class MultiplyNode : public Node
{
public:
	MultiplyNode()
	{
		m_InputPorts.resize(2);
		m_OutputPorts.resize(1);

		InputPort inputPort1;
		m_InputPorts[0] = inputPort1;
		InputPort inputPort2;
		m_InputPorts[1] = inputPort2;

		OutputPort outputPort;
		m_OutputPorts[0] = outputPort;
	}

	virtual ~MultiplyNode() = default;

	void Evaluate() override
	{
		PortData data;
		data.IntValue = m_InputPorts[0].LinkedOutputPort->Value.IntValue * m_InputPorts[1].LinkedOutputPort->Value.IntValue;
		m_OutputPorts[0].Value = data;
	}
};