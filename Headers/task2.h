#include <iostream>

int Factorial(int number) {
	// calling the factorial until we reach number 1 to stop
	if (number < 1)
		return 1;

	return(number * Factorial(number - 1));
}

void FactorialWithPointer(int* number, int number_) {
	// this is to make sure that in the first iteration the value of
	// number_ has to be less than the *number by one
	if (number_ == *number) {
		number_--;
	}

	// this is to multiply the value of number by the value of number_
	*number *= number_;

	// calling the factorial until we reach number 1 to stop
	if (number_ > 1)
		FactorialWithPointer(number, number_ - 1);
}

int pwr(int x, int y) {
	if (y == 0) {
		return 1;
	}
	if (y == 1) {
		return x;
	}
	return x * pwr(x, y - 1);
}

void pwrPtr(int* x, int* y) {
	int originalVal = *x;
	if (*y == 0) {
		*x = 1;
		return;
	}
	if (*y == 1) {
		return;
	}

	*y -= 1;

	pwrPtr(&originalVal, y);

	*x *= originalVal;
}