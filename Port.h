#pragma once

class Node;

//struct InputPort
//{
//	Node* OwningNode;
//
//	Node* GetOwningNode() const { return OwningNode; }
//
//	InputPort(Node* node) : OwningNode(node) {}
//	virtual ~InputPort() = default;
//};
//
//struct OutputPort
//{
//	Node* OwningNode;
//
//	Node* GetOwningNode() const { return OwningNode; }
//
//	OutputPort(Node* node) : OwningNode(node) {}
//	virtual ~OutputPort() = default;
//};

enum class PortType { Input = 0, Output = 1 };

class Port
{
public:
	Port(Node* node, PortType type) : m_OwningNode(node), m_Type(type) {}
	virtual ~Port() = default;

	Node* GetOwningNode() const { return m_OwningNode; }
	PortType GetPortType() const { return m_Type; }

private:
	Node* m_OwningNode;
	PortType m_Type;
};

class IntInputPort : public Port
{
public:
	IntInputPort(Node* node) : Port(node, PortType::Input) {}
	virtual ~IntInputPort() = default;

	void SetIncomingValue(const int* value) { m_IncomingValue = value; }
	const int* GetIncomingValue() const { return m_IncomingValue; }

private:
	const int* m_IncomingValue = nullptr;
};

class IntOutputPort : public Port
{
public:
	IntOutputPort(Node* node) : Port(node, PortType::Output) {}
	virtual ~IntOutputPort() = default;

	void SetValue(int value) { m_Value = value; }
	const int& GetValue() { return m_Value; }

private:
	int m_Value;
};

