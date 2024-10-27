#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int id;
	string name;
	Node* next;
	Node* prev;
};

struct LinkedList {
	Node* first = NULL;
	Node* lastInserted = NULL;
	//int id = 1;
	int size = 0;

	void PushBack(Node* head) {
		if (first == NULL) {
			first = head;
			lastInserted = head;
		}
		else {
			lastInserted->next = head;
			head->prev = lastInserted;
			lastInserted = head;
		}

		head->next = nullptr;
		//head->id = id++;
		size++;
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
		size--;
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
		//newNode->id = id++;
		oldNode = NULL;
	}

	void printList() {
		Node* curr = first;
		while (curr != NULL) {
			cout << "Emp name: " << curr->name << ", Emp ID: " << curr->id << '\n';
			curr = curr->next;
		}
	}

	LinkedList* mergeSort() {
		if (!this || !this->first == NULL || !this->lastInserted == NULL)
			return new LinkedList(*this);

		int mid = size / 2;

		LinkedList* list1 = new LinkedList();
		LinkedList* list2 = new LinkedList();

		Node* current = this->first;

		for (int i = 0; i < size; i++) {
			if (i < mid) {
				list1->PushBack(new Node(*current));
			}
			else {
				list2->PushBack(new Node(*current));
			}
			current = current->next;
		}

		list1->mergeSort();
		list2->mergeSort();

		LinkedList* newList = new LinkedList();

		Node* list1Current = list1->first;
		Node* list2Current = list2->first;

		while (list1Current != NULL && list2Current != NULL) {
			if (list1Current->id <= list2Current->id) {
				newList->PushBack(new Node(*list1Current));
				list1Current = list1Current->next;
			}
			else {
				newList->PushBack(new Node(*list2Current));
				list2Current = list2Current->next;
			}
		}

		while (list1Current != NULL) {
			newList->PushBack(new Node(*list1Current));
			list1Current = list1Current->next;
		}
		while (list2Current != NULL) {
			newList->PushBack(new Node(*list2Current));
			list2Current = list2Current->next;
		}
		delete list1Current;
		delete list2Current;
		return newList;
	}

};

int main()
{
	LinkedList Employees;

	Node firstNode;
	Node secondNode;
	Node thirdNode;
	Node forthNode;
	Node fifthNode;
	Node sixthNode;
	Node seventhNode;

	firstNode.name = "Alaa";
	firstNode.id = 1;
	secondNode.name = "Fadl";
	secondNode.id = 2;
	thirdNode.name = "Ahmed";
	thirdNode.id = 3;
	forthNode.name = "Foad";
	forthNode.id = 6;
	fifthNode.name = "Fady";
	fifthNode.id = 11;
	sixthNode.name = "Ali";
	sixthNode.id = 4;
	seventhNode.name = "Mohamed";
	seventhNode.id = 9;

	Employees.PushBack(&firstNode);
	Employees.PushBack(&secondNode);
	Employees.PushBack(&thirdNode);
	Employees.printList();
	cout << "Push back test\n\n";


	Employees.replaceEmp(&secondNode, &forthNode);
	Employees.printList();
	cout << "replace test\n\n";

	Employees.deleteEmp(&forthNode);
	Employees.printList();
	cout << "delete test\n\n";

	Employees.PushBack(&fifthNode);
	Employees.PushBack(&sixthNode);
	Employees.PushBack(&seventhNode);

	//Employees.deleteEmp(&sixthNode);
	Employees.printList();
	cout << "delete and push back\n\n";

	Employees.mergeSort();
	Employees.printList();
	cout << "Merge sort test\n\n";

	cout << "Emp with id 3: " << Employees.search(3)->name << '\n';


}
