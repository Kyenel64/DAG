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

	Port* GetInputPort(uint32_t index) { return m_InputPorts[index]; }
	Port* GetOutputPort(uint32_t index) { return m_OutputPorts[index]; }

protected:
	std::vector<Port*> m_InputPorts;
	std::vector<Port*> m_OutputPorts;

private:
	UUID m_NodeID;
};

class EndNode : public Node
{
public:
	EndNode()
	{
		IntInputPort* inputPort = new IntInputPort(this);
		m_InputPorts.push_back(inputPort);
	};

	virtual ~EndNode()
	{
		for (auto port : m_InputPorts)
			delete port;
	}

	void Evaluate() override
	{
		value = *dynamic_cast<IntInputPort*>(m_InputPorts[0])->GetIncomingValue();
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
		IntOutputPort* outputPort = new IntOutputPort(this);
		outputPort->SetValue(val);
		m_OutputPorts[0] = outputPort;
	}
	virtual ~IntNode()
	{
		for (auto& port : m_OutputPorts)
			delete port;
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

		IntInputPort* inputPort1 = new IntInputPort(this);
		m_InputPorts[0] = inputPort1;
		IntInputPort* inputPort2 = new IntInputPort(this);
		m_InputPorts[1] = inputPort2;

		IntOutputPort* outputPort = new IntOutputPort(this);
		m_OutputPorts[0] = outputPort;
	}

	virtual ~MultiplyNode()
	{
		for (auto& port : m_InputPorts)
			delete port;
		for (auto& port : m_OutputPorts)
			delete port;
	}

	void Evaluate() override
	{
		IntOutputPort* outputPort = dynamic_cast<IntOutputPort*>(m_OutputPorts[0]);
		IntInputPort* input1 = dynamic_cast<IntInputPort*>(m_InputPorts[0]);
		IntInputPort* input2 = dynamic_cast<IntInputPort*>(m_InputPorts[1]);

		outputPort->SetValue(*input1->GetIncomingValue() * *input2->GetIncomingValue());
	}
};