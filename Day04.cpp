#include <iostream>

using string = std::string;

struct Node {
	string name;
	string address;
	int index;

	Node* prev = NULL;
};

#pragma region StackImp
struct Stack {
	Node* top = NULL;

	void push(Node* newNode) {
		if (top == NULL) {
			top = newNode;
			return;
		}
		newNode->prev = top;
		top = newNode;
	}
	Node* pop() {
		if (top == NULL) {
			std::cout << "The stack is empty \n";
			return NULL;
		}
		Node* temp;
		temp = top;

		top = top->prev;
		return temp;
	}
};

#pragma endregion

struct Student {
	Node* first = NULL;
	Node* last = NULL;
	int iter;

	void enqueue(Node* newNode) {
		if (first == NULL && last == NULL) {
			iter = 0;
			last = first = newNode;
		}
		last->prev = newNode;
		last = newNode;
		iter++;
		last->index = iter;
	}

	Node* dequeue() {
		if (first == NULL) {
			std::cout << "The stack is empty\n";
			return NULL;
		}
		Node* temp = first;
		first = temp->prev;

		iter--;
		return temp;
	}
	Node* findStudent(int index) {
		Node* current = first;
		while (current != NULL) {
			if (current->index == index) {
				return current;
			}
			current = current->prev;
		}
		return NULL;
	}

	void addAtIndex(Node* newNode, int index) {
		Node* temp = findStudent(index);
		if (temp == NULL) {
			enqueue(newNode);
			return;
		}
		newNode->prev = temp->prev;
		temp->prev = newNode;
	}

	void printQueue() {
		Node* current = first;
		for (int i = 0; i <= iter; i++) {
			if (current != NULL) {
				std::cout << "Name: " << current->name << '\n';
				current = current->prev;
			}
		}
	}
};

int main()
{
	Node node1;
	Node node2;
	Node node3;
	Node node4;

	Student student;

	node1.name = "Ahmed";
	node2.name = "Amr";
	node3.name = "Mohamed";
	node4.name = "Mahmoud";

	student.enqueue(&node1);
	student.enqueue(&node2);
	student.enqueue(&node3);

	std::cout << student.findStudent(1)->name << "\n\n\n";

	student.printQueue();

	student.addAtIndex(&node4, 2);

	student.printQueue();
}
