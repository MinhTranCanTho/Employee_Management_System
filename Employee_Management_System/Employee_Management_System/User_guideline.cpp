#include"User_guideline.h"
#include<string>
#include<iostream>

using namespace std;

int choice = 0;

void User_guideline() 
{
	cout << "Welcome to Employee Management System! " << endl;
	cout << "0. Exit" << endl;
	cout << "1. Add new employee information" << endl;
	cout << "2. Show the information of specific employee" << endl;
	cout << "3. Update the information of specific employee" << endl;
	cout << "4. Delete the information of specific employee" << endl;
	cout << "\n\n" << endl;
	cout << "Your choice is ";
	cin >> choice;
}