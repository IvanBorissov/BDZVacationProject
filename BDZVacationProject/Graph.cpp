#include "Graph.hpp"

void Graph::addTown(std::string town)
{
	towns.push_back(town);
}

void Graph::addEdge(std::string from, std::string to, int weight)
{
	graph[from].push_back(make_pair(to, weight));
}

void Graph::initFromFile(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return;
	}
	std::string buff;
	getline(file, buff); /// nums

	while (!file.eof())
	{
		getline(file, buff);
		int i = 0, lineSize = buff.size();
		std::string from = "";

		if (buff[i] >= '0' && buff[i] <= '9')
		{
			std::string time = "";
			while (i < lineSize)
			{
				time += buff[i];
				i++;
			}
			availableTime = stoi(time);
			break;
		}

		while (buff[i] != ' ')
		{
			from += buff[i];
			i++;
		}

		i++;//miss the interval

		std::string to = "";
		while (buff[i] != ' ')
		{
			to += buff[i];
			i++;
		}

		i++;//miss the interval

		std::string weightS = "";
		while (i < lineSize)
		{
			weightS += buff[i];
			i++;
		}

		int weight = stoi(weightS);

		if (!read[from])
		{
			read[from] = true;
			addTown(from);
		}
		if (!read[to])
		{
			read[to] = true;
			addTown(to);
		}

		addEdge(from, to, weight);
		addEdge(to, from, weight);

	}
	file.close();
}

void Graph::updatePath(std::vector<std::string>& currPath, std::vector<std::string>& maxPath, int& maxVisitedEdges)
{
	int visited = 0, pathSize = currPath.size();
	std::unordered_map<std::string, bool> used;

	for (int i = 0; i < pathSize; i++)
	{
		if (!used[currPath[i]])
		{
			used[currPath[i]] = true;
			visited++;
		}
	}

	if (visited > maxVisitedEdges)
	{
		maxVisitedEdges = visited;
		maxPath.clear();
		for (int i = 0; i < pathSize; i++)
		{
			maxPath.push_back(currPath[i]);
		}
	}
}

void Graph::rec(std::string currEdge, std::vector<std::string> currPath, std::vector<std::string>& answerPath, int& maxVisitedEdges, int currTime, int maxTime)
{
	if (currTime > maxTime)return;

	if (currEdge == "Railstation")
	{
		updatePath(currPath, answerPath, maxVisitedEdges);
	}

	int numOfEdges = graph[currEdge].size();
	for (int i = 0; i < numOfEdges; i++)
	{
		std::string neighbour = graph[currEdge][i].first;
		int weight = graph[currEdge][i].second;

		currPath.push_back(neighbour);
		rec(neighbour, currPath, answerPath, maxVisitedEdges, currTime + weight, maxTime);
		currPath.pop_back();
	}
}

std::string Graph::findPath()
{
	std::vector<std::string> currPath, answerPath;
	std::string currEdge = "Railstation";
	int maxVisitedEdges = 0, currTime = 0;
	int maxTime = availableTime;

	currPath.push_back(currEdge);
	rec(currEdge, currPath, answerPath, maxVisitedEdges, currTime, maxTime);

	std::string path = "";
	int pathSize = answerPath.size();
	for (int i = 0; i < pathSize; i++)
	{
		path = path + answerPath[i] + " ";
	}

	return path;
}

void Graph::printGraph()
{
	int townSize = towns.size();

	std::cout << "********************************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << townSize << " number of locations" << std::endl;
	std::cout << availableTime << " time in minutes" << std::endl;

	for (int i = 0; i < townSize; i++)
	{
		std::string currTown = towns[i];
		int edgeSize = graph[currTown].size();
		std::cout << "------------------------------------" << std::endl;
		std::cout << currTown << std::endl;
		for (int j = 0; j < edgeSize; j++)
		{
			std::cout << graph[currTown][j].first << " " << graph[currTown][j].second << std::endl;
		}
	}
	std::cout << std::endl;
}
