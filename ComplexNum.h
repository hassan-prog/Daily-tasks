#pragma once
class ComplexNum
{
private:
	float realNum = 0;
	float Imaginary = 0;

public:
	ComplexNum(const ComplexNum& num);

	//ComplexNum();
	ComplexNum(float real = 0, float imag = 0);
	//ComplexNum(float real = 0);

	//~ComplexNum();

	float getReal();
	void setReal(float real);

	float getImag();
	void setImag(float imaginary);

	void Display();

	ComplexNum operator+ (const ComplexNum& addResult);
	ComplexNum& operator++ (); //pre-fix
	ComplexNum operator++ (int); //post-fix
	ComplexNum operator- (const ComplexNum& subResult);
	ComplexNum& operator-- (); //pre-fix
	ComplexNum operator-- (int); //post-fix


	void operator= (const ComplexNum& equalResult);
	bool operator!= (const ComplexNum& compareResult);
	bool operator== (const ComplexNum& compareResult);

	//casting
	operator float();
};