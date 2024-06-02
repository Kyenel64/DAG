#pragma once

class Node;

union PortData
{
	int IntValue;
	float FloatValue;
};

class Port
{
public:
	Port() = default;
	Port(Node* node) : m_OwningNode(node) {}
	virtual ~Port() = default;

	Node* GetOwningNode() const { return m_OwningNode; }

private:
	Node* m_OwningNode = nullptr;
};

class InputPort : public Port
{
public:
	InputPort() = default;
	InputPort(Node* node) : Port(node) {}
	virtual ~InputPort() = default;

	void SetIncomingValue(const PortData* value) { m_IncomingValue = value; }
	const PortData* GetIncomingValue() const { return m_IncomingValue; }

private:
	const PortData* m_IncomingValue = nullptr;
};

class OutputPort : public Port
{
public:
	OutputPort() = default;
	OutputPort(Node* node) : Port(node) {}
	virtual ~OutputPort() = default;

	void SetValue(PortData value) { m_Value = value; }
	const PortData& GetValue() const { return m_Value; }

private:
	PortData m_Value;
};

