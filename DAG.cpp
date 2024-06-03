#include "DAG.h"

#include <queue>

void DAG::AddLink(OutputPort& output, InputPort& input)
{
	input.IncomingValue = &output.Value;

	// Add link to adjacency list
	m_AdjList[output.OwningNode->GetNodeID()].push_back(input.OwningNode->GetNodeID());
}

void DAG::TopologicalSort()
{
	m_TopSortedNodes.clear();

	std::unordered_map<NodeID, uint32_t> inDegrees;
	std::queue<NodeID> nodesWithNoInput;

	// Set initial input counts to 0
	for (auto [ id, node ] : m_Nodes)
		inDegrees[id] = 0;

	// Calculate number of input for each node
	for (auto [ nodeID, adjNodeIDs] : m_AdjList)
	{
		for (auto adjNodeID : adjNodeIDs)
			inDegrees[adjNodeID]++;
	}

	// Push nodes with no input to queue
	for (auto [ nodeID, inDegree] : inDegrees)
		if (inDegree == 0)
			nodesWithNoInput.push(nodeID);

	while (!nodesWithNoInput.empty())
	{
		NodeID curNode = nodesWithNoInput.front();
		m_TopSortedNodes.push_back(curNode);

		for (auto adjNode : m_AdjList[curNode])
		{
			inDegrees[adjNode]--;
			if (inDegrees[adjNode] == 0)
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