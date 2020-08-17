#include "Expense.h"

Expense::Expense(string name, float price, string datetime, string description, string photoName)
{
	this->name = name;
	this->price = price;
	this->datetime = datetime;
	this->description = description;
	this->photoName = photoName;
}

void Expense::updateDescription(string description)
{
	this->description = description;
}

void Expense::updatePhoto(string photoName)
{
	this->photoName = photoName;
}

string Expense::displayShort()
{
	return this->displayPrice() + " " + this->name + " " + this->datetime;
}

string Expense::displayDescription()
{
	return this->resetEndlines(this->description);
}

string Expense::displayPhotoName()
{
	return this->photoName;
}

string Expense::displayName()
{
	return this->name;
}

string Expense::displayPrice()
{
	stringstream strm;
	strm << fixed << setprecision(2) << this->price;
	return strm.str();
}

string Expense::displayDatetime()
{
	return this->datetime;
}

float Expense::getPrice()
{
	return this->price;
}


bool Expense::operator==(Expense& expense2)
{
	return this->datetime == expense2.datetime;
}

bool Expense::isValid()
{
	return this->price > 0;
}

string Expense::resetEndlines(string description)
{
	for (auto& character : description) if (character == 5) character = '\n';
	return description;
}

istream& operator>>(istream& InputStream, Expense& expense)
{
	string line;
	string name, pricestr, date, description, photoname;
	float price;
	getline(InputStream, line);
	stringstream linestream(line);
	getline(linestream, name, ',');
	getline(linestream, pricestr, ','); stringstream pricestream(pricestr); pricestream >> price;
	getline(linestream, date, ',');
	getline(linestream, description, ',');
	getline(linestream, photoname, ',');
	Expense exp(name, price, date, description, photoname);
	expense = exp;

	return InputStream;
}

ostream& operator<<(ostream& OutputStream, Expense expense)
{
	OutputStream << expense.name << ',' << to_string(expense.price) << ',' << expense.datetime << ',' << expense.description << ',' << expense.photoName;
	return OutputStream;
}
