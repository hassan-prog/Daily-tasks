#pragma once
class ComplexNum
{
private:
	int realNum;
	int Imaginary;

public:
	ComplexNum(int real = 0, int imag = 0);

	int getReal();

	int getImag();

	void Display();
};



