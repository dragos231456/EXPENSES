#pragma once
#include "Validator.h"
#include <vector>
#include <memory>
#include "Undo.h"
#include "Repo.h"
//#include "Repo.cpp"

using namespace std;

class Service
{
private:
	shared_ptr<Repo<Expense>> repo;
	Validator<Expense> validator;
	vector<unique_ptr<Action>> undoStack,redoStack; 
public:
	Service();
	//Service(unique_ptr<Repo<Expense>>& repo);
	void addExpense(string name, float price, string datetime, string description, string photoName);
	void updateExpense(string name, float price, string datetime, string description, string photoName,int index);
	void setFilenameRepo(string filename);
	float getSumOfExpenses();
	vector<Expense> getExpenses();
	int countExpenses();
	void undo();
	void redo();
	string replaceEndline(string description);
};

