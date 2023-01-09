#include <iostream>
#include "SkipList.hpp"
#include "Graph.hpp"
#include "Box.hpp"

using namespace std;

///------------------------------------------------------------------------------------------------
void inputAllTowns(vector<string>& towns)
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string town;
		cin >> town;
		towns.push_back(town);
	}
}

void inputConnections(SkipList<string>& trainList)
{
	std::string line = "";
	int cnt = 0;

	std::cin.ignore(1000, '\n');
	while (getline(cin, line))
	{
		//cout << line << " " << cnt << endl;
		if (line.size() == 0)break;

		std::string town1 = "", town2 = "";
		int i = 0;
		while (i < line.size() && line[i] != ' ')
		{
			town1 += line[i];
			i++;
		}
		i++;
		while (i < line.size())
		{
			town2 += line[i];
			i++;
		}
		//cout << town1 << " " << town2 << endl;
		trainList.addSkipConnection(town1, town2);
		//cin.ignore(1000, '\n');
	}
	//cout << "done connections" << endl;
}

void inputMustVisitTowns(vector<string>& mustVisit)
{
	string line = "";
	getline(cin, line);

	for (int i = 0; i < line.size(); i++)
	{
		std::string town = "";
		while (i < line.size() && line[i] != ' ')
		{
			town += line[i];
			i++;
		}
		//cout << town << endl;
		mustVisit.push_back(town);
	}
}

void Task1()
{
	SkipList<string>trainList;
	vector<string>towns;
	vector<string>mustVisit;

	inputAllTowns(towns);
	trainList.initList(towns);
	inputConnections(trainList);
	inputMustVisitTowns(mustVisit);
	//trainList.print();
	cout << endl;
	cout << "Optimal path found:" << endl;
	cout << trainList.findPath(mustVisit) << endl;
	cout << endl;
}
///------------------------------------------------------------------------------------------------

void Task2()
{
	Graph Plovdiv;
	string fileName = "Plovdiv.txt";

	Plovdiv.initFromFile(fileName);
	//Plovdiv.printGraph();
	cout << endl;
	cout << "Optimal path for touring the city:" << endl;
	cout << Plovdiv.findPath() << endl;
	cout << endl;
}

///-------------------------------------------------------------------------------------------------

void Task3()
{
	string s = "MainBox";
	Box MainBox(s);

	s = "boxesList.txt";
	//s = "boxesListScramble.txt";
	//s = "AllEmptyBoxes.txt";
	MainBox.initFromFile(s);
	cout << "/--------------------------------" << endl;
	cout << "Boxes from input:" << endl;
	cout << endl;
	MainBox.print();
	cout << endl;
	cout << "//---------------------------------" << endl;
	
	MainBox.optimizeBoxes();

	cout << "/--------------------------------" << endl;
	cout << "Boxes after sorting:" << endl;
	cout << endl;
	MainBox.print();
	cout << endl;
	cout << "//---------------------------------" << endl;
}

///-------------------------------------------------------------------------------------------------

void Interface()
{
	while (1)
	{
		cout << "Select task:" << endl;
		cout << "Type 1 for SkipList task" << endl;
		cout << "Type 2 for TownGraph task" << endl;
		cout << "Type 3 for TownBox task" << endl;
		cout << "Type 4 for exit of the interface" << endl;
		int n;
		cin >> n;

		if (n == 1)
		{
			Task1();
		}
		else
		if (n == 2)
		{
			Task2();
		}
		else
		if (n == 3)
		{
			Task3();
		}
		else
		if (n == 4)
		{
			return;
		}
		else
		{
			cout << "Invalid number! Try again" << endl;
		}
	}
}

int main()
{
	Interface();

	return 0;
}
/*
 Task 1 testcase

9
Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
Sofia Plovdiv
Plovdiv NovaZagora
Dimitrovgrad NovaZagora
StaraZagora Yambol
NovaZagora Burgas

Plovdiv StaraZagora Yambol

*/

/*
Task 1 testcase
10
A 1 2 3 4 5 6 7 8 B
A 5
1 4
2 B
4 8

4 5

*/