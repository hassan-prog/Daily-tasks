#include <iostream>

using string = std::string;

struct Node {
	string name;
	string address;
	int id;

	Node* prev = NULL;
};

struct TreeNode {
	string name;
	string address;
	int id;

	TreeNode* right = NULL;
	TreeNode* left = NULL;
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

#pragma region Student
struct Student {
	Node* first = NULL;
	Node* last = NULL;
	int index = 0;

	void enqueue(Node* newNode) {
		int nextId = index + 1;
		if (first == NULL && last == NULL) {
			//nextId = last->id;

			last = first = newNode;
			last->id = nextId;
			index += 1;
			return;
		}
		last->prev = newNode;
		last = newNode;
		index++;
		last->id = nextId;
	}

	Node* dequeue() {
		if (first == NULL) {
			std::cout << "The stack is empty\n";
			return NULL;
		}
		Node* temp = first;
		first = temp->prev;

		index--;
		return temp;
	}

	Node* findStudent(int index) {
		Node* current = first;
		while (current != NULL) {
			if (current->id == index) {
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
		for (int i = 0; i < index + 1; i++) {
			if (current != NULL) {
				std::cout << "Name: " << current->name << '\n';
				current = current->prev;
			}
		}
	}
};
#pragma endregion

struct StudentTree {
	TreeNode* root = NULL;
	int index = 0;

	void insert(TreeNode* newNode) {
		int nextId = index + 1;
		if (root == NULL) {
			newNode->id = nextId;
			root = newNode;
			index++;
			return;
		}

		TreeNode* current = root;
		TreeNode* parent = NULL;

		while (current != NULL) {
			parent = current;

			if (newNode->id > current->id) {
				current = current->left;
				if (current == NULL) {
					newNode->id = index + 1;
					parent->left = newNode;
					index++;
				}
			}
			else {
				current = current->right;
				if (current == NULL) {
					newNode->id = index + 1;
					parent->right = newNode;
					index++;
				}
			}

		}
	}

	TreeNode* findStud(TreeNode* root, int id) {
		if (root == NULL) {
			std::cout << "not found\n";
			return NULL;
		}

		if (root->id == id)
			return root;

		if (id < root->id) {
			return findStud(root->left, id);
		}
		else {
			return findStud(root->right, id);
		}
	}
};

int main()
{
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

		auto x = student.findStudent(1);
		std::cout << student.findStudent(1)->name << "\n\n\n";

		//student.printQueue();

		student.addAtIndex(&node4, 1);

		student.printQueue();
	}

	TreeNode* s1 = new TreeNode();
	TreeNode* s2 = new TreeNode();
	TreeNode* s3 = new TreeNode();
	TreeNode* s4 = new TreeNode();

	StudentTree tree;

	s1->name = "Khaled";
	s2->name = "Mostafa";
	s3->name = "Ali";
	s4->name = "Omar";

	tree.insert(s1);
	tree.insert(s2);
	tree.insert(s3);
	tree.insert(s4);

	TreeNode* solution = tree.findStud(tree.root, 3);

	if (solution != NULL)
		std::cout << "\nUsing search. \nStudent Name: " << solution->name << '\n';

}
