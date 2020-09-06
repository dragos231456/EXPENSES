#pragma once
#include "Expense.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

///include si cpp in service 
template<typename ClassType>
class Repo
{
private:
	string filename = "exp.csv";
	void readAllFromFile(vector<ClassType>& elements);
	void writeAllToFile(vector<ClassType> elements);
public:
	void changeFilename(string newFilename);
	void addElement(ClassType element);
	void deleteElement(ClassType element);
	ClassType updateElement(ClassType element,int index);
	bool searchElement(ClassType searchedElement);
	vector<ClassType> getElements();
	int size();
};

