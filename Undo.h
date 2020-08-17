#pragma once
#include <memory>
#include "Repo.h"
#include "Repo.cpp"

using namespace std;

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	~Action() = default;
};

class Add : public Action
{
private:
	shared_ptr<Repo<Expense>> repo;
	Expense addedExpense;
public:
	Add(shared_ptr<Repo<Expense>> repo,Expense expense);
	void executeUndo() override;
	void executeRedo() override;
};

class Update : public Action
{
private:
	shared_ptr<Repo<Expense>> repo;
	Expense oldExpense,newExpense;
	int index;
public:
	Update(shared_ptr<Repo<Expense>> repo,Expense oldExpense,Expense newExpense,int index);
	void executeUndo() override;
	void executeRedo() override;
};