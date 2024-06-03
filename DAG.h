#pragma once

#include <vector>
#include <unordered_map>
#include <memory>

#include "Node.h"
#include "Port.h"

class DAG
{
public:
	DAG() {}

	template<typename T, typename... Args>
	std::shared_ptr<T> AddNode(Args&&... args)
	{
		std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
		m_Nodes[node->GetNodeID()] = node;
		return node;
	}

	bool AddLink(const std::shared_ptr<Node>& outputNode, uint32_t outputPortIndex, const std::shared_ptr<Node>& inputNode, uint32_t inputPortIndex);

	// Run whenever there are changes in the graph
	void TopologicalSort();

	// Run whenever data is updated.
	// Each node only references the input node's data to prevent iterating through the whole graph to get a value.
	// If ran in a game loop, this should be called once at the beginning of each frame.
	void Evaluate();

private:
	std::unordered_map<NodeID, std::shared_ptr<Node>> m_Nodes;
	std::unordered_map<NodeID, std::vector<NodeID>> m_AdjList;
	std::vector<NodeID> m_TopSortedNodes;
};