#pragma once

#include <vector>
#include <unordered_map>

#include "Node.h"
#include "Port.h"

class DAG
{
public:
	DAG() {}

	void AddNode(Node *node) { m_Nodes[node->GetNodeID()] = node; }
	void AddLink(OutputPort& output, InputPort& input);

	// Run whenever there are changes in the graph
	void TopologicalSort();

	// Run whenever data is updated.
	void Evaluate();

private:
	std::unordered_map<NodeID, Node*> m_Nodes;
	std::unordered_map<NodeID, std::vector<NodeID>> m_AdjList;
	std::vector<NodeID> m_TopSortedNodes;
};