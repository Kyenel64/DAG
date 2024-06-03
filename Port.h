#pragma once

union PortData
{
	int IntValue;
	float FloatValue;
};

struct OutputPort
{
	PortData Value;
};

struct InputPort
{
	const OutputPort* LinkedOutputPort;
};

