#include "DAG.h"
#include "Node.h"

#include <iostream>
#include <memory>

int main()
{
	DAG dag;
	std::shared_ptr<EndNode> endNode = dag.AddNode<EndNode>();
	std::shared_ptr<MultiplyNode> multiplyNode1 = dag.AddNode<MultiplyNode>();
	std::shared_ptr<MultiplyNode> multiplyNode2 = dag.AddNode<MultiplyNode>();
	std::shared_ptr<MultiplyNode> multiplyNode3 = dag.AddNode<MultiplyNode>();
	std::shared_ptr<IntNode> intNode1 = dag.AddNode<IntNode>();
	std::shared_ptr<IntNode> intNode2 = dag.AddNode<IntNode>();
	std::shared_ptr<IntNode> intNode3 = dag.AddNode<IntNode>();

	intNode1->SetValue(5);
	intNode2->SetValue(10);
	intNode3->SetValue(6);

	dag.AddLink(intNode1, 0, multiplyNode1, 0);
	dag.AddLink(intNode2, 0, multiplyNode1, 1);
	dag.AddLink(intNode2, 0, multiplyNode2, 0);
	dag.AddLink(intNode3, 0, multiplyNode2, 1);
	dag.AddLink(multiplyNode1, 0, multiplyNode3, 0);
	dag.AddLink(multiplyNode2, 0, multiplyNode3, 1);
	dag.AddLink(multiplyNode3, 0, endNode, 0);

	dag.TopologicalSort();
	dag.Evaluate();

	std::cout << endNode->GetValue() << std::endl;

	return 0;
}