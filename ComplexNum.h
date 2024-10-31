#pragma once
class ComplexNum
{
private:
	float realNum = 0;
	float Imaginary = 0;

public:
	static int counter;

	ComplexNum(const ComplexNum& num);

	ComplexNum();
	ComplexNum(float real = 0, float imag = 0);
	ComplexNum(float real = 0);

	~ComplexNum();

	float getReal();
	void setReal(float real);

	float getImag();
	void setImag(float imaginary);

	void Display();
};



