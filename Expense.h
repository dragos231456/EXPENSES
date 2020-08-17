#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Expense
{
private:
	string name="";
	string datetime="";
	float price=0.0;
	string description="-";
	string photoName="-";
public:
	Expense() {}
	Expense(string name, float price, string datetime, string description, string photoName);
	void updateDescription(string description);
	void updatePhoto(string photoName);
	string displayShort();
	string displayDescription();
	string displayPhotoName();
	string displayName();
	string displayPrice();
	string displayDatetime();
	float getPrice();
	friend istream& operator>>(istream& InputStream, Expense& expense);
	friend ostream& operator<<(ostream& OutputStream, Expense expense);
	bool operator==(Expense& expense2);
	bool isValid();
	string resetEndlines(string description);
};

