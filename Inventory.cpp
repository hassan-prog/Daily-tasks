#include <iostream>
//#include <vector>
#include "../Daily-tasks/Headers/task1.h"
#include "../Daily-tasks/Headers/task2.h"
#include "../Daily-tasks/Headers/task3.h"

int main() {
	char cont;
	char choice;

	do
	{
		std::cout << "Select one of the below\n";
		std::cout << "1- Get the time table for the number 5\n";
		std::cout << "2- Get the factorial or the power of a number\n";
		std::cout << "3- Create an inventory with some items and print the names of the items\n";
		std::cin >> choice;

		switch (choice)
		{
		case '1': {
			int i = 10;
			timeTable(i);
			break;
		}
		case '2': {
			int option;
			std::cout << "1- Factorial\n" << "2- Power\n";
			std::cin >> option;
			switch (option)
			{
			case 1:
			{
				std::cout << "Enter the number: \n";
				int value;
				std::cin >> value;
				std::cout << "1- With Pointer\n" << "2- Without Pointer\n";
				int ptrOption;
				std::cin >> ptrOption;

				switch (ptrOption)
				{
				case 1: {
					FactorialWithPointer(&value, value);

					std::cout << value << '\n';
					break;
				}case 2: {
					std::cout << Factorial(value) << '\n';
					break;
				}
				default:
					break;
				}
				break;
			}
			case 2:
			{
				std::cout << "Enter the base number: \n";
				int baseValue;
				std::cin >> baseValue;
				std::cout << "Enter the powered by number: \n";
				int secondNum;
				std::cin >> secondNum;
				std::cout << "1- With Pointer\n" << "2- Without Pointer\n";
				int ptrOption;
				std::cin >> ptrOption;

				switch (ptrOption)
				{
				case 1: {
					pwrPtr(&baseValue, &secondNum);
					std::cout << baseValue << '\n';
					break;
				}case 2: {
					std::cout << pwr(baseValue, secondNum) << '\n';
					break;
				}
				default:
					break;
				}
			}
			default:
				break;
			}
			break;
		}

		case '3': {
			Inventory playerInventory;
			std::vector<Item> myItems;
			Item firstItem;
			Item secondItem;
			Item thirdItem;
			myItems.push_back(firstItem);
			myItems.push_back(secondItem);
			myItems.push_back(thirdItem);

			playerInventory.playerName = "Skwizee";
			playerInventory.playerHP = 100;

			myItems[0].setName("Sword");
			myItems[0].setIsUnlimited(true);
			myItems[0].setIsVisible(true);
			myItems[0].id = 1;

			Item secondWeapon;
			myItems[1].setName("Bow");
			myItems[1].setIsUnlimited(false);
			myItems[1].setIsVisible(true);
			myItems[1].id = 2;

			Item thirdWeapon;
			myItems[2].setName("Shield");
			myItems[2].setIsUnlimited(true);
			myItems[2].setIsVisible(false);
			myItems[2].id = 3;

			playerInventory.addItems(myItems);
			playerInventory.printInventory();
			char isDelete;
			std::cout << "Want to delete an item? Y/N\n";
			std::cin >> isDelete;
			switch (isDelete)
			{
			case 'Y':
			case 'y':
			{
				std::cout << "Choose the index\n";
				int deleteIndex;
				std::cin >> deleteIndex;
				playerInventory.deleteItem(deleteIndex);
				playerInventory.printInventory();
				break;
			}
			case 'N':
			case 'n':
			{
				std::cout << "Press any key to continue or \"q\" to quit\n";
				std::cin >> cont;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			std::cout << "invalid input! please enter one of the operations";
			break;
		}
		std::cout << "Press any key to continue or \"q\" to quit\n";
		std::cin >> cont;
	} while (cont != 'q');

}