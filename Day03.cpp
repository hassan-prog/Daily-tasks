#include <iostream>
#include <vector>

#define LOG(v) std::cout << v

using namespace std;

void Swap(vector<int>* numbers, int index1, int index2) {
	int temp = (*numbers)[index1];
	(*numbers)[index1] = (*numbers)[index2];
	(*numbers)[index2] = temp;
}

void BubbleSort(vector<int>* numbers) {
	for (int i = 0; i < (*numbers).size(); i++) {
		for (int j = i + 1; j < numbers->size(); j++)
		{
			if ((*numbers)[i] > (*numbers)[j])
				Swap(numbers, i, j);
		}
	}
}

vector<int> insertionSort(vector<int> numbers) {
	int j;
	for (int i = 0; i < numbers.size(); i++) {
		int key = numbers[i];
		j = i - 1;

		while (j >= 0 && key < numbers[j]) {
			numbers[j + 1] = numbers[j];
			j--;
		}
		numbers[j + 1] = key;
	}
	return numbers;
}

vector<int> MergeSort(vector<int> numbers) {
	int size = numbers.size();
	if (size <= 2) {
		if (size == 2) {
			if (numbers[0] > numbers[1])
				Swap(&numbers, 0, 1);
			return numbers;
		}
		return numbers;
	}

	vector<int> vec1;
	vector<int> vec2;

	for (int i = 0; i < size / 2; i++) {
		vec1.push_back(numbers[i]);
	}
	for (int i = size / 2; i < size; i++) {
		vec2.push_back(numbers[i]);
	}
}

void PrintVector(vector<int>* numbers) {
	for (int i = 0; i < (*numbers).size(); i++) {
		LOG((*numbers)[i]);
	}
}

int main()
{
	std::vector<int> numbers = { 9,2,3,0,6,3,5 };
	PrintVector(&numbers);
	cout << '\n';

	numbers = insertionSort(numbers);

	PrintVector(&numbers);
	cout << '\n';
	BubbleSort(&numbers);

	PrintVector(&numbers);
	cout << '\n';

}
