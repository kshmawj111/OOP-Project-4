#include "interface.h"

void Interface::print()
{
	/*string input;
cout << "Enter your filename : ";
getline(cin, input);
Student s(input); // student class*/

	Student s("20165705 ±è¿øÁØ.csv");
	subject_DB sdb; // subject DB class
	sdb.init_DB(); // initiate DB

	while (true)
	{
		s.get_input(sdb);
	}
}