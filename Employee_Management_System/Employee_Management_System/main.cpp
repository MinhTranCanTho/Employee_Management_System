#include<iostream>
#include<vector>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/statement.h>
#include<mysql_connection.h>
#include<mysql_driver.h>
#include<string>
#include<stdlib.h>
#include<chrono>
#include<thread>
#include"User_guideline.h"
#include"Employee_Data.h"

using namespace std;

/*
	This program will include some features as below
	0. Exit
	1. Add new employee information to Employee_Data DataBase and Check whether this information was existing before or not
	2. Show the information of specific employee
	3. Update the information of specific employee
	4. Delete the information of specific employee

	Note: the console will be waited for 5s before clearing screen or starting a new request

	Data of the employee:
	- Name
	- Employee ID
	- Age
	- Address
	- School
	- Experience
	- Language
	- Certificate
*/
Employee_Data employee;
string Name;
unsigned int Employee_ID;
unsigned int Age;
string Address;
string School;
unsigned int Year_Of_Experience;
string Language;
string Certificate;
int err_flag = 0;

sql::mysql::MySQL_Driver* driver;
sql::Connection* connection;
sql::ResultSet* res;
sql::Statement* stmt;
int main(int argc, char** argv)
{
	/*Show user guideline*/
	User_guideline();
	if (isdigit(choice))
	{
		std::cout << "Your enter value is incorrect!" << endl;
	}
	else 
	{
		/*Wait for 5s before clearing screen*/
		this_thread::sleep_for((chrono::seconds(3)));
		system("cls");

		while (choice != 0)
		{
			if (choice == 1)
			{
				/*1. Add new employee information to Employee_Data DataBase and Check whether this information was existing before or not*/

				/*Step 01: collect all data*/
				/*Start Collecting data of employee*/

				cout << "Please enter employee information!" << endl;
				cout << "Name: ";
				cin.ignore();
				getline(cin, Name);
				cout << "Employee ID: ";
				cin >> Employee_ID;
				cout << "Age: ";
				cin >> Age;
				cout << "Address: ";
				cin.ignore();	/*After above line was executed, there is still the newline character \n (because you pressed enter to input the value) in the input buffer, to fix this you add a line with cin.ignore(); after reading the int.*/
				getline(cin, Address);
				cout << "School: ";
				getline(cin, School);
				cout << "Year Of Experience: ";
				cin >> Year_Of_Experience;
				cout << "Language: ";
				cin.ignore();
				getline(cin, Language);
				cout << "Certificate: ";
				getline(cin, Certificate);


				Employee_Data employee(Name, Employee_ID, Age, Address, School, Year_Of_Experience, Language, Certificate);

				/*End collecting data of user.*/

				/*Step 02: Save data to Employee_Data DataBase*/
				try
				{
					driver = sql::mysql::get_mysql_driver_instance();
					connection = driver->connect("tcp://localhost:3306", "root", "Minh_Tran123456");
					/*Name of data base*/
					connection->setSchema("Employee_Data");
					stmt = connection->createStatement();

					/*Create table in DB*/
					string TableSQL = "CREATE TABLE IF NOT EXISTS Employees("
						"Name varchar(255),"
						"Employee_ID int PRIMARY KEY,"
						"Age varchar(255),"
						"Address varchar(255),"
						"School varchar(255),"
						"YOE int,"
						"Language varchar(255),"
						"Cert varchar(255)"
						")";
					stmt->execute(TableSQL);

					/*
						INSERT INTO Employees (Name, Employee_ID, Age, Address, School, YOE, Language, Cert) VALUES ('TranCongMinh',321,27,'14/245','DHCT',5,'English & Vietnamese','TOEIC')
					*/
					string first_cmd = "INSERT INTO Employees (Name, Employee_ID, Age, Address, School, YOE, Language, Cert) VALUES ";
					string second_cmd = "('" + employee.Name + "'," + to_string(employee.Employee_ID) + ", " + to_string(employee.Age) + ", " + "'" + employee.Address + "'," + "'" + employee.School + "'," + to_string(employee.Year_Of_Experience) + ",'" + employee.Language + "','" + employee.Certificate + "')";
					string InsertDataSQL = first_cmd + second_cmd;

					/*SQL query to retrieve data from the table*/
					string selectDataSQL = "SELECT Name FROM Employees";

					res = stmt->executeQuery(selectDataSQL);
					/*Debug step - Loop through the result set and display data*/
					/*int count = 0;
					while (res->next())
					{
						cout << "Name: " << res->getString("Name") << endl;
						cout << "Employee_ID: " << res->getString("Employee_ID") << endl;
						cout << "Age: " << res->getString("Age") << endl;
						cout << "Address: " << res->getString("Address") << endl;
						cout << "School: " << res->getString("School") << endl;
						cout << "YOE: " << res->getString("YOE") << endl;
						cout << "Language: " << res->getString("Language") << endl;
						cout << "Cert: " << res->getString("Cert") << endl;
					}*/

					while (res->next())
					{
						if (res->getString("Name") == employee.Name)
						{
							err_flag = 1;
							break;
						}
						else
						{
							err_flag = 0;
						}
					}
					if (err_flag == 1)
					{
						cout << "This employee is existed before, please try again!" << endl;
					}
					else
					{
						/*Store data into Employee_Data DataBase*/
						stmt->execute(InsertDataSQL);
					}

					err_flag = 0;
					system("cls");
					cout << "Employee information is saved successfully!" << endl;
					delete stmt;
					delete connection;
					delete res;
				}
				/*Step 03: Check whether this information was existing before or not*/
				catch (sql::SQLException& e)
				{
					if (e.getErrorCode() == 1062)
					{
						cout << "This employee is existed, please try again!" << endl;
					}
					else
					{
						cerr << "SQL error: " << e.getErrorCode() << endl;
					}
				}
			}
			else if (choice == 2)
			{
				/*2. Show the information of specific employee*/
				cout << "Please enter employee ID: " << endl;
				cin >> Employee_ID;
				employee.Employee_ID = Employee_ID;
				try
				{
					/*Create connection*/

					driver = sql::mysql::get_driver_instance();
					connection = driver->connect("tcp://localhost:3306", "root", "Minh_Tran123456");
					/*Name of data base*/
					connection->setSchema("Employee_Data");
					sql::Statement* stmt;
					stmt = connection->createStatement();

					/*SQL query to retrieve data from DB*/
					string selectDataSQL = "SELECT * FROM Employees";
					sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

					while (res->next())
					{
						if (res->getString("Employee_ID") == to_string(employee.Employee_ID))
						{
							err_flag = 0;
							break;
						}
						else
						{
							err_flag = 1;
						}
					}

					if (err_flag == 1) 
					{
						cout << "This employee is not existed in system, please try again!" << endl;
					}
					else 
					{
						system("cls");
						cout << "Name: " << res->getString("Name") << endl;
						cout << "Employee_ID: " << res->getString("Employee_ID") << endl;
						cout << "Age: " << res->getString("Age") << endl;
						cout << "Address: " << res->getString("Address") << endl;
						cout << "School: " << res->getString("School") << endl;
						cout << "YOE: " << res->getString("YOE") << endl;
						cout << "Language: " << res->getString("Language") << endl;
						cout << "Cert: " << res->getString("Cert") << endl;
					}

					err_flag = 0;
					delete stmt;
					delete connection;
					delete res;
				}
				catch (sql::SQLException& e)
				{
					if (e.getErrorCode() == 0) 
					{
						cout << "There is no information stored." << endl;
					}
					else 
					{
						cerr << "SQL error: " << e.getErrorCode() << endl;
					}
				}
			}
			else if (choice == 3)
			{
				/*3. Update the information of specific employee*/
				/*Step 01: collect all data*/
				/*Start Collecting data of employee*/
				system("cls");
				cout << "Please enter employee information!" << endl;
				cout << "Name: ";
				cin.ignore();
				getline(cin, Name);
				cout << "Employee ID: ";
				cin >> Employee_ID;
				cout << "Age: ";
				cin >> Age;
				cout << "Address: ";
				cin.ignore();	/*After above line was executed, there is still the newline character \n (because you pressed enter to input the value) in the input buffer, to fix this you add a line with cin.ignore(); after reading the int.*/
				getline(cin, Address);
				cout << "School: ";
				getline(cin, School);
				cout << "Year Of Experience: ";
				cin >> Year_Of_Experience;
				cout << "Language: ";
				cin.ignore();
				getline(cin, Language);
				cout << "Certificate: ";
				getline(cin, Certificate);


				Employee_Data employee(Name, Employee_ID, Age, Address, School, Year_Of_Experience, Language, Certificate);
				/*End collecting data of user.*/
				try
				{
					/*Step 02: Update new data employee to Employee_Data DataBase*/
					driver = sql::mysql::get_driver_instance();

					connection = driver->connect("tcp://localhost:3306", "root", "Minh_Tran123456");
					/*Name of data base*/
					connection->setSchema("Employee_Data");
					sql::Statement* stmt;
					stmt = connection->createStatement();

					string InsertDataSQL = "UPDATE Employees SET Name = '" + employee.Name + \
						"', Age = '" + to_string(employee.Age) + \
						"', Address = '" + employee.Address + \
						"', School = '" + employee.School + \
						"', YOE = '" + to_string(employee.Year_Of_Experience) + \
						"', Language = '" + employee.Language + \
						"', Cert = '" + employee.Certificate + \
						"' WHERE Employee_ID =" + to_string(employee.Employee_ID);

					/*Store data into Employee_Data DataBase*/
					stmt->execute(InsertDataSQL);
					delete stmt;
					delete connection;
					delete res;
				}
				catch (sql::SQLException& e)
				{
					if (e.getErrorCode() == 1062)
					{
						cout << "This employee is existed, please try again!" << endl;
					}
					else
					{
						cerr << "SQL error: " << e.getErrorCode() << endl;
					}
				}
			}
			else if (choice == 4)
			{
				system("cls");
				cout << "Please enter employee ID: " << endl;
				cin >> Employee_ID;
				employee.Employee_ID = Employee_ID;
				try
				{
					driver = sql::mysql::get_driver_instance();
					connection = driver->connect("tcp://localhost:3306", "root", "Minh_Tran123456");
					connection->setSchema("Employee_Data");
					sql::Statement* stmt;
					stmt = connection->createStatement();
					string InsertDataSQL = "DELETE FROM Employees WHERE Employee_ID = " + to_string(employee.Employee_ID);
					stmt->execute(InsertDataSQL);



					system("cls");
					cout << "Employee information is removed successfully!" << endl;
					delete stmt;
					delete connection;
					delete res;
				}
				catch (sql::SQLException& e)
				{
					if (e.getErrorCode() == 1062)
					{
						cout << "This employee is existed, please try again!" << endl;
					}
					else
					{
						cerr << "SQL error: " << e.what() << endl;
					}
				}
			}
			else
			{
				cout << "Your choice is out of scope, please try again!" << endl;
			}

			/*Wait for 5s before clearing screen*/
			this_thread::sleep_for((chrono::seconds(5)));
			system("cls");
			/*Reinitialize value of all global variables */
			string Name = "";
			unsigned int Employee_ID = 0;
			unsigned int Age = 0;
			string Address = "";
			string School = "";
			unsigned int Year_Of_Experience = 0;
			string Language = "";
			string Certificate = "";
			int err_flag = 0;
			/*Start again*/
			User_guideline();
		}
	}
	


	return 0;
}