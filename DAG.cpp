#include "DAG.h"

#include <queue>

void DAG::AddLink(OutputPort& output, InputPort& input)
{
	input.SetIncomingValue(&output.GetValue());

	// Add link to adjacency list
	m_AdjList[output.GetOwningNode()->GetNodeID()].push_back(input.GetOwningNode()->GetNodeID());
}

void DAG::TopologicalSort()
{
	m_TopSortedNodes.clear();

	std::unordered_map<UUID, uint32_t> inputCounts;
	std::queue<UUID> nodesWithNoInput;

	// Set initial input counts to 0
	for (auto [ id, node ] : m_Nodes)
		inputCounts[id] = 0;

	// Calculate number of input for each node
	for (auto [ nodeID, adjNodeIDs] : m_AdjList)
	{
		for (auto adjNodeID : adjNodeIDs)
			inputCounts[adjNodeID]++;
	}

	// Push nodes with no input to queue
	for (auto [ nodeID, inDegree] : inputCounts)
		if (inDegree == 0)
			nodesWithNoInput.push(nodeID);

	while (!nodesWithNoInput.empty())
	{
		UUID curNode = nodesWithNoInput.front();
		m_TopSortedNodes.push_back(curNode);

		for (auto adjNode : m_AdjList[curNode])
		{
			inputCounts[adjNode]--;
			if (inputCounts[adjNode] == 0)
				nodesWithNoInput.push(adjNode);
		}
		nodesWithNoInput.pop();
	}
}

void DAG::Evaluate()
{
	for (auto& nodeID : m_TopSortedNodes)
		m_Nodes[nodeID]->Evaluate();
}