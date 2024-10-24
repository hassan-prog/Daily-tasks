#include <iostream>
#include <vector>

//using namespace std;

struct Item {
	int id;
private:
	std::string name;
	std::string itemDescription;
	bool isUnlimited;
	bool isVisible;

public:
	std::string getName() const {
		return name;
	}

	void setName(const std::string& newName) {
		name = newName;
	}


	bool getIsUnlimited() const {
		return isUnlimited;
	}

	void setIsUnlimited(bool unlimited) {
		isUnlimited = unlimited;
	}

	bool getIsVisible() const {
		return isVisible;
	}

	void setIsVisible(bool visible) {
		isVisible = visible;
	}
};

struct Inventory {
	std::vector<Item> myItems;
	std::string playerName;
	short playerHP;

	void addItems(std::vector<Item> items) {
		for (int i = 0; i < items.size(); i++) {
			myItems.push_back(items[i]);
		}
	}

	void deleteItem(int index) {
		myItems.erase(myItems.begin() + index);
	}

	void printInventory() {
		for (int i = 1; i <= myItems.size(); i++) {
			std::cout << "Item " << i << " " << myItems[i - 1].getName() << '\n';
		}
		std::cout << "Number of items: " << myItems.size() << '\n';
	}

};