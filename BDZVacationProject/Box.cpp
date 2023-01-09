#include "Box.hpp"

void Box::Copy(const Box& other)
{
	BoxID = other.BoxID;

	int souvenirSize = other.sounvenirs.size();
	for (int i = 0; i < souvenirSize; i++)
	{
		sounvenirs.push_back(other.sounvenirs[i]);
	}

	int boxesSize = other.boxes.size();
	for (int i = 0; i < boxesSize; i++)
	{
		///create new box
		Box* newBox = new Box(*other.boxes[i]);
		boxes.push_back(newBox);
	}
}

void Box::Erase()
{
	//std::cout << "calling erase of:" << BoxID << std::endl;
	for (auto i : boxes)
		delete i;

	/*for (auto i : boxes)
		i->Erase();
	*/
	//delete this;
}

Box::Box(std::string& s)
{
	BoxID = s;
}

Box::Box(const Box& other)
{
	Copy(other);
}

Box& Box::operator=(const Box& other)
{
	if (this != &other)
	{
		Erase();
		Copy(other);
	}
	return *this;
}

Box::~Box()
{
	//std::cout << "calling destructor of:" << BoxID << std::endl;
	Erase();
}

void Box::rec()
{
	for (auto i : this->boxes)
		i->rec();

	auto iterator = boxes.begin();
	bool stop = iterator != boxes.end();
	while (stop)
	{
		auto temp = iterator;
		iterator++;
		stop = iterator != boxes.end();
		if ((*temp)->boxes.size() == 0 && (*temp)->sounvenirs.size() == 0)
		{
			boxes.erase(temp);
			if (boxes.size() == 0)break;
			//delete* temp;
		}
	}

	if (BoxID != "MainBox" && boxes.size() == 1 && sounvenirs.size() == 0)
	{
		Box* tempBox = boxes[0];
		BoxID = tempBox->BoxID;
		boxes = tempBox->boxes;
		sounvenirs = tempBox->sounvenirs;
		delete tempBox;
	}
}

Box* Box::findBox(std::string boxName) const
{
	int boxesSize = boxes.size();
	for (int i = 0; i < boxesSize; i++)
	{
		if (boxes[i]->BoxID == boxName)
		{
			return boxes[i];
		}
		else
		{
			Box* temp = boxes[i]->findBox(boxName);
			if (temp != nullptr)
			{
				return temp;
			}
		}
	}
	return nullptr;
}

Box* Box::extractBox(std::string boxName)
{
	int boxesSize = boxes.size();
	for (int i = 0; i < boxesSize; i++)
	{
		if (boxes[i]->BoxID == boxName)
		{
			Box* temp = boxes[i];
			boxes.erase(boxes.begin() + i);
			return temp;
		}
		else
		{
			boxes[i]->extractBox(boxName);
		}
	}
	return nullptr;
}

void Box::print()
{
	std::cout << "/-----------------" << std::endl;
	std::cout << BoxID << std::endl;
	std::cout << "Souvenirs:" << std::endl;
	int souvenirSize = sounvenirs.size();
	for (int i = 0; i < souvenirSize; i++)
	{
		std::cout << sounvenirs[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "Boxes:" << std::endl;
	int boxesSize = boxes.size();
	for (int i = 0; i < boxesSize; i++)
	{
		std::cout << boxes[i]->BoxID << " " << std::endl;
		//boxes[i]->print();
	}
	for (int i = 0; i < boxesSize; i++)
	{
		boxes[i]->print();
	}
	std::cout << std::endl;

}

void Box::addSouvenir(std::string souvenir)
{
	sounvenirs.push_back(souvenir);
}

void Box::addBox(Box insideBox)
{
	Box* temp = new Box(insideBox);
	boxes.push_back(temp);
}

void Box::addBoxByPointer(Box* insideBox)
{
	boxes.push_back(insideBox);
}

void Box::initFromFile(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return;
	}
	std::string buff;
	getline(file, buff);

	while (!file.eof())
	{
		getline(file, buff);

		int i = 0, buffSize = buff.size();
		std::string boxName = "";

		while (buff[i] != ' ')
		{
			boxName += buff[i];
			i++;
		}

		if (findBox(boxName) == nullptr)
		{
			Box newBox = Box(boxName);
			addBox(newBox);
		}


		i++; ///miss the interval
		std::string numSouvenirs = "";
		while (buff[i] >= '0' && buff[i] <= '9')
		{
			numSouvenirs += buff[i];
			i++;
		}

		i++;//miss the interval

		Box* currBox = findBox(boxName);

		int numOfSouvenirs = stoi(numSouvenirs);
		//std::cout << numOfSouvenirs << std::endl;

		for (int k = 0; k < numOfSouvenirs; k++)
		{
			std::string souvenir = "";
			while (buff[i] != ' ')
			{
				souvenir += buff[i];
				i++;
			}
			i++;//miss the interval

			currBox->addSouvenir(souvenir);

		}

		std::string numBoxes = "";
		while (buff[i] >= '0' && buff[i] <= '9')
		{
			numBoxes += buff[i];
			i++;
		}

		i++;//miss the interval

		int numOfBoxes = stoi(numBoxes);

		for (int k = 0; k < numOfBoxes; k++)
		{
			std::string box = "";
			while (i < buffSize && buff[i] != ' ')
			{
				box += buff[i];
				i++;
			}
			i++;//miss the interval

			if (findBox(box) == nullptr)
			{
				Box insideBox(box);
				currBox->addBox(insideBox);
			}
			else
			{
				Box* temp = extractBox(box);
				currBox->addBoxByPointer(temp);
			}
		}

	}
	file.close();
}

void Box::optimizeBoxes()
{
	///start from mainBox pointer
	rec();
}
