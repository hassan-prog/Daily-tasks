#include <iostream>

void timeTable(int iterations) {
	int base = 5;
	int result;

	result = base * iterations;
	std::cout << "5 * " << iterations << " = " << result << "\n";
	iterations--;

	if (iterations > 0) {
		timeTable(iterations);
	}
}
