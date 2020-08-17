#include "Repo.h"

template<typename ClassType>
void Repo<ClassType>::readAllFromFile(vector<ClassType>& elements)
{
	ClassType element;
	ifstream InputStream(this->filename);
	while (InputStream >> element) elements.push_back(element);
	InputStream.close();
}

template<typename ClassType>
void Repo<ClassType>::writeAllToFile(vector<ClassType> elements)
{
	ofstream OutputStream(this->filename);
	for (auto element : elements) OutputStream << element << '\n';
	OutputStream.close();
}

template<typename ClassType>
void Repo<ClassType>::changeFilename(string newFilename)
{
	this->filename = newFilename;
}

template<typename ClassType>
void Repo<ClassType>::addElement(ClassType element)
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	elements.push_back(element);
	this->writeAllToFile(elements);
}

template<typename ClassType>
void Repo<ClassType>::deleteElement(ClassType element)
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	elements.resize(elements.size() - 1);
	this->writeAllToFile(elements);
}


template<typename ClassType>
ClassType Repo<ClassType>::updateElement(ClassType element,int index)
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	swap(elements[index], element);
	this->writeAllToFile(elements);
	return element;
}

template<typename ClassType>
bool Repo<ClassType>::searchElement(ClassType searchedElement)
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	for (auto element : elements) if (element == searchedElement) return true;
	return false;
}

template<typename ClassType>
vector<ClassType> Repo<ClassType>::getElements()
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	return elements;
}

template<typename ClassType>
int Repo<ClassType>::size()
{
	vector<ClassType> elements;
	this->readAllFromFile(elements);
	return elements.size();
}
