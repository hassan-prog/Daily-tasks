#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int id;
	string name;
	Node* next;
	Node* prev;

	void PrintNode() {
		cout << "Name : " << name << "| ID : " << id << '\n';
	}

};

struct LinkedList {
	Node* first = NULL;
	Node* lastInserted = NULL;
	int id = 1;

	void PushBack(Node* head) {
		if (first == nullptr) {
			first = head;
			lastInserted = head;
		}
		else {
			lastInserted->next = head;
			head->prev = lastInserted;
			lastInserted = head;
		}

		head->next = nullptr;
		head->id = id++;
	}

	Node* search(int id) {
		Node* curr = first;
		if (first == NULL) {
			cout << "The list is empty";
			return NULL;
		}
		while (curr) {
			if (curr->id == id) {
				return curr;
			}
			curr = curr->next;
		}
		return NULL;
	}

	void deleteEmp(Node* Emp) {
		if (Emp == NULL) {
			return;
		}
		Node* curr = search(Emp->id);

		if (curr == NULL) {
			return;
		}

		if (curr->prev != NULL) {
			curr->prev->next = curr->next;
		}

		if (curr->next != NULL) {
			curr->next->prev = curr->prev;
		}

		if (Emp == curr) {
			Emp = curr->next;
		}
	}


	void replaceEmp(Node* oldNode, Node* newNode) {
		if (oldNode->prev != NULL) {
			oldNode->prev->next = newNode;
			newNode->prev = oldNode->prev;
		}
		if (oldNode->next != NULL) {
			oldNode->next->prev = newNode;
			newNode->next = oldNode->next;
		}
		newNode->id = id++;
		oldNode = NULL;
	}

	void printList(Node* head) {
		Node* curr = head;
		while (curr != NULL) {
			cout << "Emp name: " << curr->name << ", Emp ID: " << curr->id << '\n';
			curr = curr->next;
		}
	}

};

int main()
{
	LinkedList Employees;

	Node firstNode;
	Node secondNode;
	Node thirdNode;
	Node forthNode;
	firstNode.name = "Alaa";

	secondNode.name = "Fadl";

	thirdNode.name = "Ahmed";

	forthNode.name = "Merna";

	Employees.PushBack(&firstNode);
	Employees.PushBack(&secondNode);
	Employees.PushBack(&thirdNode);
	Employees.printList(&firstNode);

	Employees.deleteEmp(&secondNode);
	Employees.printList(&firstNode);

	Employees.replaceEmp(&secondNode, &forthNode);
	Employees.printList(&firstNode);

	//cout << Employees.search(3)->name << "this is my node";
}
