#include "Undo.h"

Add::Add(shared_ptr<Repo<Expense>> repo, Expense expense)
{
	this->repo = repo;
	this->addedExpense = expense;
}

void Add::executeUndo()
{
	this->repo->deleteElement(this->addedExpense);
}

void Add::executeRedo()
{
	this->repo->addElement(this->addedExpense);
}

Update::Update(shared_ptr<Repo<Expense>> repo, Expense oldExpense, Expense newExpense,int index)
{
	this->repo = repo;
	this->index = index;
	this->oldExpense = oldExpense;
	this->newExpense = newExpense;
}

void Update::executeUndo()
{
	this->repo->updateElement(this->oldExpense,this->index);
}

void Update::executeRedo()
{
	this->repo->updateElement(this->newExpense,this->index);
}
