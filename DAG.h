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
	std::unordered_map<UUID, Node*> m_Nodes;
	std::unordered_map<UUID, std::vector<UUID>> m_AdjList;
	std::vector<UUID> m_TopSortedNodes;
};