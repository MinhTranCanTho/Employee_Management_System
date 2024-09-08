#ifndef EMPLOYEE_DATA_H
#define EMPLOYEE_DATA_H

#include<iostream>
#include<string>

using namespace std;

class Employee_Data
{
public:
	string Name;
	unsigned int Employee_ID;
	unsigned int Age;
	string Address;
	string School;
	unsigned int Year_Of_Experience;
	string Language;
	string Certificate;

	Employee_Data() 
	{
		this->Name = "";
		this->Employee_ID = 0;
		this->Age = 0;
		this->Address = "";
		this->School = "";
		this->Year_Of_Experience = 0;
		this->Language = "";
		this->Certificate = "";
	}
	Employee_Data(string Name, unsigned int Employee_ID, unsigned int Age, string Address, string School, unsigned int Year_Of_Experience, string Language, string Certificate)
	{
		this->Name = Name;
		this->Employee_ID = Employee_ID;
		this->Age = Age;
		this->Address = Address;
		this->School = School;
		this->Year_Of_Experience = Year_Of_Experience;
		this->Language = Language;
		this->Certificate = Certificate;
	}
	~Employee_Data() 
	{
		this->Name = "";
		this->Employee_ID = 0;
		this->Age = 0;
		this->Address = "";
		this->School = "";
		this->Year_Of_Experience = 0;
		this->Language = "";
		this->Certificate = "";
	}
};


#endif // !EMPLOYEE_DATA_H

