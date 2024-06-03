#pragma once

class Node;

union PortData
{
	int IntValue;
	float FloatValue;
};

struct InputPort
{
	Node* OwningNode;
	const PortData* IncomingValue = nullptr;
};

struct OutputPort
{
	Node* OwningNode;
	PortData Value;
};

