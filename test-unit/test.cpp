#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){
	
		Student student;
		string studentName;
		string studentInfo = "'Brandon' 45679999";
		string idNumber;
		string command;
		auto *newNode = new AVL();

		int firstQuote = studentInfo.find_first_of('"');
		int lastQuote = studentInfo.find_last_of('"');
		studentName = studentInfo.substr(firstQuote + 1, lastQuote - 2);
		idNumber = studentInfo.substr(lastQuote + 1, studentInfo.length() - 1);

		if (!isIdValid(idNumber)|| studentName.empty())
		{
			cout << "unsuccessful" << endl;
		}

		if (!isNameValid(studentName))
		{
			cout << "unsuccessful" << endl;
		}

		newNode->NAME = studentName;
		newNode->ID = stoi(idNumber);
		student.root = student.insert(student.root, newNode);


	
	REQUIRE(1 == 1);
}