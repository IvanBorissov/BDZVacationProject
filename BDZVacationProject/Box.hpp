#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Box
{
private:
	std::string BoxID;
	std::vector<std::string> sounvenirs;
	std::vector<Box*> boxes;

	void Copy(const Box& other);
	void Erase();

	void rec();
	Box* findBox(std::string boxName) const;
	Box* extractBox(std::string boxName);

public:
	Box() = delete;
	Box(std::string& s);
	Box(const Box& other);
	Box& operator= (const Box& other);
	~Box();

	void print();
	void addSouvenir(std::string souvenir);
	void addBox(Box insideBox);
	void addBoxByPointer(Box* insideBox);
	void initFromFile(std::string fileName);
	void optimizeBoxes();
};

