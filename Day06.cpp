#include <iostream>
#include <vector>
#include "ComplexNum.h"

//to be inhirited
class Person {
public:
	std::string Breathe() {
		return "Breathing...";
	};
};

#pragma region Association
class Student;
class Doctor : public Person {
public:
	std::string docName;
	void Ask(Student* stud) {
		std::cout << "Asking student a question\n";
	}
};

//the doctor can have multiple students
//linked but they do not own each other
class Student : public Person {
public:
	Doctor* doctor;
};

//the student can have multiple doctors
class Student2 : public Person {
	void takeExam() {
		std::cout << "taking exam\n";
	};
};
class Doctor2 : public Person {
	void Examin(Student2 patient) {}
	Student2* patient;
};

#pragma endregion

#pragma region Aggregation
//library have book objects, but each book can exist outside the library.
class Library;
class Book {
public:
	int numOfPages;
	Library* lib;
};

class Library {
public:
	std::string name;
	std::vector<Book*> Books;
};
#pragma endregion

#pragma region Composition
// cannot exist without eachother
class PersonComp;
class Organ {
public:
	std::string name;
	PersonComp* myHuman;
};

class PersonComp : public Person {
public:
	std::vector<Organ*> myOrgans;
};
#pragma endregion

int main()
{
	char choice;
	do
	{
		std::cout << "Select one of the below or enter q to quit\n";
		std::cout << "1- Overloading operators (+,-,=,!=,==) and casting\n";
		std::cout << "2- Association, Aggregation, Composition, and Inhiritance\n";
		std::cout << "3- Overloading more operators (++, --) BONUS\n";
		std::cin >> choice;

		switch (choice)
		{
		case '1': {
			system("CLS");
			ComplexNum firstNum(3, 2);
			ComplexNum secondNum(2, 0);
			ComplexNum thirdNum(2, 0);

			std::cout << "first number: ";
			firstNum.Display();
			std::cout << "second number: ";
			secondNum.Display();
			std::cout << "third number: ";
			thirdNum.Display();

			ComplexNum additionResult;

			additionResult = firstNum + secondNum;
			std::cout << "Result of adding first and second: ";
			additionResult.Display();
			std::cout << '\n';

			ComplexNum subResult;

			subResult = firstNum - secondNum;
			std::cout << "Result of subtracting first from second: ";
			subResult.Display();
			std::cout << '\n';

			std::cout << "result of comparing first and second with == : ";
			firstNum == secondNum ? std::cout << "true\n" : std::cout << "false\n";
			std::cout << "result of comparing first and second with != : ";
			firstNum != secondNum ? std::cout << "true\n" : std::cout << "false\n";

			std::cout << '\n';
			float complxSqr = firstNum;
			std::cout << "casting first number: " << complxSqr << '\n';
			break;
		}

		case '2': {
			system("CLS");
			Doctor mathDoc;
			std::cout << "Inheritance\n";
			std::cout << "Accessing the Breathe method from the doctor: " << mathDoc.Breathe() << "\n\n";

			std::cout << "Association\n";
			mathDoc.docName = "Ahmed";
			Student stud;
			mathDoc.Ask(&stud);
			stud.doctor = &mathDoc;
			std::cout << "Accessing the doctor's name from the student: " << stud.doctor->docName << "\n\n";

			std::cout << "Aggregation\n";
			Library myLib;
			Book phBook;
			Book mathBook;
			Book englishBook;

			phBook.numOfPages = 507;
			phBook.lib = &myLib;

			mathBook.numOfPages = 400;
			mathBook.lib = &myLib;

			englishBook.numOfPages = 325;
			englishBook.lib = &myLib;

			std::vector<Book*> books;
			books.push_back(&phBook);
			books.push_back(&mathBook);
			books.push_back(&englishBook);

			myLib.Books = books;
			myLib.name = "ITI Library";
			std::cout << "The number of books in my library: " << myLib.Books.size() << "\n\n";
			std::cout << "getting the library name from the books: " << phBook.lib->name << "\n\n";

			std::cout << "Composition\n";
			Organ heart;
			Organ lung;
			PersonComp human;
			heart.name = "my heart\n";
			heart.myHuman = &human;
			lung.name = "my lungs are working\n";
			lung.myHuman = &human;
			std::cout << "Accessing the breathe function from my organ: " << heart.myHuman->Breathe() << "\n\n";

			std::vector<Organ*> humanOrgans;
			humanOrgans.push_back(&heart);
			humanOrgans.push_back(&lung);
			human.myOrgans = humanOrgans;

			std::cout << "The number of organs in the human: " << human.myOrgans.size() << "\n\n";

			break;
		}
		case '3': {
			system("CLS");
			ComplexNum complxNumPost(3, 2);
			ComplexNum complxNumPre(6, 1);

			std::cout << "using post fix on: ";
			complxNumPost.Display();
			complxNumPost++;
			complxNumPost.Display();
			std::cout << "\n";

			std::cout << "using pre fix on: ";
			complxNumPre.Display();
			--complxNumPre;
			complxNumPre.Display();
			std::cout << "\n";
		}
		default:
			break;
		}
	} while (tolower(choice) != 'q');

}