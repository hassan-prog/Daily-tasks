#include <iostream>
#include <cctype>

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
			return;
		}
		last->prev = newNode;
		last = newNode;
		last->id = nextId;
		index++;
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

	Node* findStudent(int id) {
		Node* current = first;
		while (current != NULL) {
			if (current->id == id) {
				return current;
			}
			current = current->prev;
		}
		return NULL;
	}

	Node* findStudByIndex(int j) {
		Node* current = first;
		for (int i = 0; i <= j; i++) {
			current = current->prev;
		}

		/*while (current != NULL) {
			if (current->id == id) {
				return current;
			}
			current = current->prev;
		}*/
		return NULL;
	}

	void addAtIndex(Node* newNode, int j) {
		Node* current = first;
		for (int i = 0; i < j && current->prev != NULL; i++) {
			current = current->prev;
		}
		Node* temp = current;

		if (temp == NULL || (temp->prev == NULL && j != index)) {
			enqueue(newNode);
			return;
		}
		/*newNode->prev = temp->prev;
		temp->prev = newNode;*/
		if (temp == first) {  // If inserting at the beginning
			newNode->prev = first;
			first = newNode;
			index++;
		}
		else {
			Node* prevNode = first;
			while (prevNode->prev != temp) {
				prevNode = prevNode->prev;
			}
			if (prevNode != NULL) {
				newNode->prev = temp;
				prevNode->prev = newNode;
				index++;
			}
		}
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
	char quit;
	do
	{
		int input;
		std::cout << "To test the Queue functionality enter 1, to test the Binary tree enter 2.\n";
		std::cin >> input;

		switch (input)
		{
		case 1: {
			system("CLS");
			std::cout << "Queue\n";

			Node node1;
			Node node2;
			Node node3;
			Node node4;
			Node node5;

			Student student;

			node1.name = "Ahmed";
			node2.name = "Amr";
			node3.name = "Mohamed";
			node4.name = "Mahmoud";

			node5.name = "Merna";

			student.enqueue(&node1);
			student.enqueue(&node2);
			student.enqueue(&node3);
			student.enqueue(&node4);

			std::cout << "Using Enqueue" << "\n";
			student.printQueue();

			Node* oldNode = student.dequeue();
			std::cout << "\nUsing Dequeue: " << oldNode->name << "\n\n";

			std::cout << "Using search by index\nStudent name: " << student.findStudent(2)->name << "\n\n";

			student.addAtIndex(&node5, 2);

			student.printQueue();
			std::cout << "Press any button to continue and 'q' to quit" << '\n';
			std::cin >> quit;
			break;
		}
		case 2: {
			system("CLS");
			std::cout << "Binary tree\n";
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

			std::cout << "\nUsing insert \nRoot data: " << tree.root->name << '\n';
			TreeNode* solution = tree.findStud(tree.root, 3);

			if (solution != NULL)
				std::cout << "\nUsing search by id. \nStudent Name: " << solution->name << '\n';

			std::cout << "Press any button to continue and 'q' to quit" << '\n';
			std::cin >> quit;

			break;
		}
		default:
			break;
		}
	} while (tolower(quit) != 'q');
}
