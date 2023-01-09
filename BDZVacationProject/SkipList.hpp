#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

template<typename T>
struct SkipNode
{
	T data;
	SkipNode* next;
	SkipNode* skip;

	SkipNode(const T& data)
	{
		this->data = data;
		next = nullptr;
		skip = nullptr;
	}
};

template<typename T>
class SkipList
{
private:
	SkipNode<T>* head;
	SkipNode<T>* tail;

	void Copy(const SkipList<T>& other);
	void Erase();
	SkipNode<T>* findNode(const T& el) const;
	std::string BFS(SkipNode<T>*& currNode, std::string& ennd);
public:
	SkipList();
	SkipList(const SkipList<T>& other);
	SkipList& operator= (const SkipList<T>& other);
	~SkipList();

	void pushBack(const T& el);
	bool addSkipConnection(const T&, const T&);

	void print() const;
	void initList(std::vector<std::string>& route);
	//void addConnections();
	std::string findPath(std::vector<std::string> mustVisit);
};

template<typename T>
void SkipList<T>::Copy(const SkipList<T>& other)
{
	SkipNode<T>* ptr = other.head;
	while (ptr != nullptr)
	{
		pushBack(ptr->data);
		ptr = ptr->next;
	}

	///fixing the skip pointers
	ptr = other.head;
	SkipNode<T>* newptr = head;
	while (ptr != nullptr)
	{
		if (ptr->skip != nullptr)
		{
			newptr->skip = findNode(ptr->skip->data);
		}

		ptr = ptr->next;
		newptr = newptr->next;
	}
}

template<typename T>
void SkipList<T>::Erase()
{
	SkipNode<T>* curr = head;
	while (curr != nullptr)
	{
		SkipNode<T>* ptr = curr;
		curr = curr->next;
		delete ptr;
	}
	head = tail = nullptr;
}

template<typename T>
SkipList<T>::SkipList()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
SkipList<T>::SkipList(const SkipList<T>& other)
{
	head = nullptr;
	tail = nullptr;

	Copy(other);
}

template<typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other)
{
	if (this != &other)
	{
		Erase();
		Copy(other);
	}

	return *this;
}

template<typename T>
SkipList<T>::~SkipList()
{
	Erase();
}

template<typename T>
void SkipList<T>::pushBack(const T& el)
{
	SkipNode<T>* ptr = new SkipNode<T>(el);

	if (tail == nullptr)
	{
		head = tail = ptr;
		return;
	}

	tail->next = ptr;
	tail = ptr;
}

template<typename T>
SkipNode<T>* SkipList<T>::findNode(const T& el) const
{
	SkipNode<T>* ptr = head;

	while (ptr != nullptr)
	{
		if (ptr->data == el)
		{
			return ptr;
		}
		ptr = ptr->next;
	}

	return nullptr;
}

template<typename T>
bool SkipList<T>::addSkipConnection(const T& beg, const T& ennd)
{
	SkipNode<T>* ptr = findNode(beg);
	SkipNode<T>* ptr2 = findNode(ennd);

	//std::cout << "found the Nodes buddy" << std::endl;

	if (ptr == nullptr)
	{
		std::cout << "Non existent Node -> " << beg << " in the List" << std::endl;
		return false;
	}
	if (ptr2 == nullptr)
	{
		std::cout << "Non existent Node -> " << ennd << " in the List" << std::endl;
		return false;
	}

	ptr->skip = ptr2;
	//std::cout << "Put the connection in place" << std::endl;
	return true;
}

template<typename T>
void SkipList<T>::print() const
{
	SkipNode<T>* ptr = head;
	while (ptr != nullptr)
	{
		std::cout << ptr->data << " -> ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

template<typename T>
void SkipList<T>::initList(std::vector<std::string>& route)
{
	int routeSize = route.size();
	for (int i = 0; i < routeSize; i++)
	{
		pushBack(route[i]);
	}
}

/*template<typename T>
void SkipList<T>::addConnections()
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
		addSkipConnection(town1, town2);
		//cin.ignore(1000, '\n');
	}
	cout << "done connections" << endl;
}
*/

template<typename T>
std::string SkipList<T>::BFS(SkipNode<T>*& currNode, std::string& ennd)
{
	std::unordered_map<T, T> used;
	std::queue<SkipNode<T>* >q;
	std::string startingTownName = currNode->data;

	used[currNode->data] = currNode->data;
	q.push(currNode);

	while (!q.empty())
	{
		SkipNode<T>* nb = q.front();
		q.pop();

		if (nb->next != nullptr && used.find(nb->next->data) == used.end())
		{
			used[nb->next->data] = nb->data;
			if (nb->next->data == ennd)
			{
				///we have found the ennd element
				currNode = nb->next; ///moving the global pointer ahead
				break; ///search no longer required
			}

			q.push(nb->next);
		}
		if (nb->skip != nullptr && used.find(nb->skip->data) == used.end())
		{
			used[nb->skip->data] = nb->data;
			if (nb->skip->data == ennd)
			{
				currNode = nb->skip; ///moving the global pointer to the next search block
				break; ///search no longer required
			}

			q.push(nb->skip);
		}
	}

	std::string path = ennd;
	std::string str = ennd;

	//std::cout << "recovering path" << std::endl;
	while (used[str] != startingTownName)
	{
		//cout << str << " " << used[str] << endl;
		path = used[str] + " " + path;
		str = used[str];
	}
	path = " " + path;

	//cout << path << endl;

	return path;

}

template<typename T>
std::string SkipList<T>::findPath(std::vector<std::string> mustVisit)
{
	mustVisit.push_back(tail->data);

	std::string fullPath = head->data;
	SkipNode<std::string>* tempHead = head;

	for (int i = 0; i < mustVisit.size(); i++)
	{
		//std::cout << "/------------------------------------------------------" << std::endl;
		//std::cout << "BFS between " << tempHead->data << " " << mustVisit[i] << std::endl;
		//std::cout << std::endl;
		std::string path = BFS(tempHead, mustVisit[i]); ///old beg
		fullPath += path;
	}

	return fullPath;
}