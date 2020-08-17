#include "Service.h"

Service::Service()
{
	this->repo = make_shared<Repo<Expense>>();
}

void Service::addExpense(string name, float price, string datetime, string description, string photoName)
{
	string error = "price not valid!";
	description = this->replaceEndline(description);
	Expense expense(name, price, datetime, description, photoName);
	if (this->validator.isValid(expense) == false) throw error;

	this->repo->addElement(expense);
	this->undoStack.push_back(make_unique<Add>(this->repo,expense));
}

void Service::updateExpense(string name, float price, string datetime, string description, string photoName,int index)
{
	string error1 = "price not valid!";
	string error2 = "index not in range";
	description = this->replaceEndline(description);
	Expense expense(name, price, datetime, description, photoName);
	if (this->validator.isValid(expense) == false) throw error1;

	int repoSize = this->repo->getElements().size();
	if (index < 0 || index >= repoSize) throw error2;

	Expense oldexpense = this->repo->updateElement(expense, index);
	this->undoStack.push_back(make_unique<Update>(this->repo,oldexpense, expense, index));
}

void Service::setFilenameRepo(string filename)
{
	this->repo->changeFilename(filename);
}

float Service::getSumOfExpenses()
{
	float sum=0;
	vector<Expense> elements = this->repo->getElements();
	for (auto element : elements) sum += element.getPrice();
	return sum;
}

vector<Expense> Service::getExpenses()
{
	return this->repo->getElements();
}

int Service::countExpenses()
{
	return this->repo->size();
}

void Service::undo()
{
	string error = "Undo stack is empty!";

	if (this->undoStack.size() == 0) throw error;
	
	unique_ptr<Action> action = move(this->undoStack[this->undoStack.size() - 1]);
	this->undoStack.resize(this->undoStack.size() - 1);
	action->executeUndo();
	this->redoStack.push_back(move(action));
}

void Service::redo()
{
	string error = "Redo stack is empty!";

	if (this->redoStack.size() == 0) throw error;

	unique_ptr<Action> action = move(this->redoStack[this->redoStack.size() - 1]);
	this->redoStack.resize(this->redoStack.size() - 1);
	action->executeRedo();
	this->undoStack.push_back(move(action));
}

string Service::replaceEndline(string description)
{
	for (auto& character : description) if (character == '\n') character = 5;
	return description;
}
