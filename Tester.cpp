#include "Tester.h"

void Tester::testAll()
{
	testDomain();
	testRepo();
	testValidator();
	testService();
}

void Tester::testDomain()
{
	testDomainCreate();
	testDomainUpdateDescription();
	testDomainUpdatePhotoName();
	testRead();
	testWrite();
}

void Tester::testDomainCreate()
{
	string name = "Ana";
	string date = "azi si nu maine";
	string description = "-";
	string photoName = "-";
	float price = 6.9;
	
	string expected = to_string(price) + " " + name + " " + date;

	Expense expense(name, price, date, description, photoName);

	assert(1 == 1);
	assert(expense.displayShort() == expected);
}

void Tester::testDomainUpdateDescription()
{
	string name = "Ana";
	string date = "azi si nu maine";
	string description = "-",newd="blana";
	string photoName = "-";
	float price = 6.9;

	Expense expense(name, price, date, description, photoName);

	expense.updateDescription(newd);

	assert(expense.displayDescription() == newd);
}

void Tester::testDomainUpdatePhotoName()
{
	string name = "Ana";
	string date = "azi si nu maine";
	string description = "-", newd = "blana";
	string photoName = "-";
	float price = 6.9;

	Expense expense(name, price, date, description, photoName);

	expense.updatePhoto(newd);

	assert(expense.displayPhotoName() == newd);
}


void Tester::testRead()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blana";
	string photoName = "a.jpg";
	float price = 11.5;

	fstream f("test.txt");
	Expense exp;
	f >> exp;

	string expected = to_string(price) + " " + name + " " + date;

	assert(exp.displayShort() == expected);
}

void Tester::testWrite()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blana";
	string photoName = "a.jpg";
	float price = 11.5;

	ofstream g("test2.txt");
	Expense expense(name, price, date, description, photoName);
	g << expense;
	g.close();

	ifstream f("test2.txt");
	Expense expense2;
	f >> expense2;

	assert(expense == expense2);
}

void Tester::testRepo()
{
	testRepoAdd();
	testRepoUpdate();
}

void Tester::testRepoRead()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blana";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, description, photoName);

	Repo<Expense> repo;
	vector<Expense>elems = repo.getElements();

	assert(elems[0] == expense);
}

void Tester::testRepoAdd()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blana";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, description, photoName);

	Repo<Expense> repo;
	repo.addElement(expense);
	vector<Expense>elems = repo.getElements();
	
	assert(elems[0] == expense);
}

void Tester::testRepoUpdate()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blanaBomba";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, newd, photoName);
	Repo<Expense> repo;
	repo.updateElement(expense, 0);
	vector<Expense>elems = repo.getElements();

	assert(elems[0] == expense);
}

void Tester::testValidator()
{
	testValidator___InvalidObject___returnFalse();
	testValidator___ValidObject___returnTrue();
}

void Tester::testValidator___InvalidObject___returnFalse()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blanaBomba";
	string photoName = "a.jpg";
	float price = -11.5;

	Expense expense(name, price, date, newd, photoName);

	Validator<Expense> validator;
	assert(validator.isValid(expense) == false);
}

void Tester::testValidator___ValidObject___returnTrue()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbun", newd = "blanaBomba";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, newd, photoName);

	Validator<Expense> validator;
	assert(validator.isValid(expense) == true);
}

void Tester::testService()
{
	testSerivce___Add___InvalidObject___ThrowError();
	testService___Add___ValidObject__Success();
	testService___Update__InvalidObject___ThrowError();
	testService___Update__InvalidIndex___ThrowError();
	testService___Update__ValidObject___Success();
}

void Tester::testSerivce___Add___InvalidObject___ThrowError()
{
	string name = "Ana";
	string date = "poiieri";
	string description = "bunbunbun";
	string photoName = "a.jpg";
	float price = -11.5;

	string expected= "price not valid!";

	Service service;
	try
	{
		service.addExpense(name, price, date, description, photoName);
		assert(false);
	}
	catch (string & error)
	{
		assert(error == expected);
	}
}

void Tester::testService___Add___ValidObject__Success()
{
	string name = "AnaMaria";
	string date = "poiieri";
	string description = "bunbunbun";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, description, photoName);

	Service service;

	service.addExpense(name, price, date, description, photoName);

	assert(service.getExpenses()[1] == expense);
}

void Tester::testService___Update__InvalidObject___ThrowError()
{
	string name = "AnaMaria";
	string date = "poiieri";
	string description = "bunbunbun";
	string photoName = "a.jpg";
	float price = -11.5;

	string expected = "price not valid!";

	Service service;
	try
	{
		service.updateExpense(name, price, date, description, photoName,1);
		assert(false);
	}
	catch (string & error)
	{
		assert(error == expected);
	}
}

void Tester::testService___Update__InvalidIndex___ThrowError()
{
	string name = "AnaMaria";
	string date = "poiieri";
	string description = "bunbunbun";
	string photoName = "a.jpg";
	float price = 11.5;

	string expected = "index not in range";

	Service service;
	try
	{
		service.updateExpense(name, price, date, description, photoName, 5);
		assert(false);
	}
	catch (string & error)
	{
		assert(error == expected);
	}
}

void Tester::testService___Update__ValidObject___Success()
{
	string name = "AnaMariaDem";
	string date = "poiieri";
	string description = "bunbunbun";
	string photoName = "a.jpg";
	float price = 11.5;

	Expense expense(name, price, date, description, photoName);

	Service service;
	service.updateExpense(name, price, date, description, photoName, 1);

	assert(service.getExpenses()[1] == expense);
}
