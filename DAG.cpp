#include "DAG.h"

#include <queue>

bool DAG::AddLink(const std::shared_ptr<Node>& outputNode, uint32_t outputPortIndex, const std::shared_ptr<Node>& inputNode, uint32_t inputPortIndex)
{
	OutputPort& outputPort = outputNode->m_OutputPorts[outputPortIndex];
	InputPort& inputPort = inputNode->m_InputPorts[inputPortIndex];

	inputPort.LinkedOutputPort = &outputPort;

	// Add link to adjacency list
	m_AdjList[outputNode->GetNodeID()].push_back(inputNode->GetNodeID());

	return true;
}

void DAG::TopologicalSort()
{
	m_TopSortedNodes.clear();

	std::unordered_map<NodeID, uint32_t> inDegrees; // inDegree == number of linked inputs
	std::queue<NodeID> nodesWithNoInput;

	// Set initial inDegrees to 0 for all nodes.
	for (auto& [ id, node ] : m_Nodes)
		inDegrees[id] = 0;

	// Calculate number of indegrees for each node.
	for (auto& [ nodeID, adjNodeIDs] : m_AdjList)
	{
		for (auto adjNodeID : adjNodeIDs)
			inDegrees[adjNodeID]++;
	}

	// Push nodes with an indegree of 0 to queue
	for (auto& [ nodeID, inDegree] : inDegrees)
		if (inDegree == 0)
			nodesWithNoInput.push(nodeID);

	// Retrieve a node with no indegree and push to sorted array.
	// Decrement indegree of adjacent nodes by 1. If the adjacent node has no indegree, add to no indegree queue.
	// Repeat until all nodes have been processed.
	while (!nodesWithNoInput.empty())
	{
		NodeID curNode = nodesWithNoInput.front();
		m_TopSortedNodes.push_back(curNode);

		for (auto& adjNode : m_AdjList[curNode])
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