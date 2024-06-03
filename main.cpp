#include "DAG.h"
#include "Node.h"

#include <iostream>

int main()
{
	IntNode *int5Node = new IntNode(5);
	IntNode *int10Node = new IntNode(10);
	IntNode *int6Node = new IntNode(6);
	MultiplyNode *multiplyNode1 = new MultiplyNode();
	MultiplyNode *multiplyNode2 = new MultiplyNode();
	MultiplyNode *multiplyNode3 = new MultiplyNode();
	EndNode *endNode = new EndNode();

	DAG dag;
	dag.AddNode(endNode);
	dag.AddNode(multiplyNode1);
	dag.AddNode(multiplyNode2);
	dag.AddNode(multiplyNode3);
	dag.AddNode(int5Node);
	dag.AddNode(int10Node);
	dag.AddNode(int6Node);


	// topSorted for testing
	//dag.AddNode(int5Node);
	//dag.AddNode(int10Node);
	//dag.AddNode(int6Node);
	//dag.AddNode(multiplyNode1);
	//dag.AddNode(multiplyNode2);
	//dag.AddNode(multiplyNode3);
	//dag.AddNode(endNode);

	dag.AddLink(int5Node->GetOutputPort(0), multiplyNode1->GetInputPort(0));
	dag.AddLink(int10Node->GetOutputPort(0), multiplyNode1->GetInputPort(1));
	dag.AddLink(int10Node->GetOutputPort(0), multiplyNode2->GetInputPort(0));
	dag.AddLink(int6Node->GetOutputPort(0), multiplyNode2->GetInputPort(1));
	dag.AddLink(multiplyNode1->GetOutputPort(0), multiplyNode3->GetInputPort(0));
	dag.AddLink(multiplyNode2->GetOutputPort(0), multiplyNode3->GetInputPort(1));
	dag.AddLink(multiplyNode3->GetOutputPort(0), endNode->GetInputPort(0));

	dag.TopologicalSort();
	dag.Evaluate();

	int5Node->SetValue(1000);
	dag.Evaluate();

	std::cout << endNode->GetValue() << std::endl;

	return 0;
}