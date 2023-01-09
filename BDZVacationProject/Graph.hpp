#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

class Graph
{
private:
	std::unordered_map< std::string, std::vector< std::pair<std::string, int> > >graph;
	std::vector<std::string> towns;
	std::unordered_map<std::string, bool> read;
	int availableTime;

	void updatePath(std::vector<std::string>& currPath, std::vector<std::string>& maxPath, int& maxVisitedEdges);
	void rec(std::string currEdge, std::vector<std::string> currPath, std::vector<std::string>& answerPath, int& maxVisitedEdges, int currTime, int maxTime);
public:
	Graph() = default;
	~Graph() = default;

	///getters

	void addTown(std::string town);
	void addEdge(std::string from, std::string to, int weight);
	void initFromFile(std::string fileName);
	std::string findPath();
	void printGraph();
};
