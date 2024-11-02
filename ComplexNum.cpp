#include "ComplexNum.h"
#include <iostream>


ComplexNum::ComplexNum(const ComplexNum& num) {
	this->realNum = num.realNum;
	this->Imaginary = num.Imaginary;
}

//ComplexNum::ComplexNum() {
//	this->realNum = 0;
//	this->Imaginary = 0;
//	ComplexNum::counter++;
//}

ComplexNum::ComplexNum(float real, float imag) {
	this->realNum = real;
	this->Imaginary = imag;
}

//ComplexNum::ComplexNum(float real) {
//	this->realNum = real;
//	this->Imaginary = 0;
//	ComplexNum::counter++;
//}

float ComplexNum::getReal() {
	return realNum;
}

void ComplexNum::setReal(float real) {
	this->realNum = real;
}

float ComplexNum::getImag() {
	return Imaginary;
}

void ComplexNum::setImag(float imag) {
	this->Imaginary = imag;
}


void ComplexNum::Display() {
	std::cout << realNum;
	if (Imaginary >= 0) {
		std::cout << " + " << Imaginary << "i";
	}
	else {
		std::cout << " - " << -Imaginary << "i";
	}
	std::cout << '\n';
}


ComplexNum ComplexNum::operator+(const ComplexNum& addResult) {
	ComplexNum result;
	result.setReal(realNum + addResult.realNum);
	result.setImag(Imaginary + addResult.Imaginary);
	return result;
}
ComplexNum ComplexNum::operator-(const ComplexNum& subResult) {
	ComplexNum result;
	result.setReal(realNum - subResult.realNum);
	result.setImag(Imaginary - subResult.Imaginary);
	return result;
}
void ComplexNum::operator=(const ComplexNum& equalResult) {
	realNum = equalResult.realNum;
	Imaginary = equalResult.Imaginary;
}
bool ComplexNum::operator!=(const ComplexNum& compareResult) {
	if (realNum != compareResult.realNum || Imaginary != compareResult.Imaginary)
		return true;
	return false;
}
bool ComplexNum::operator== (const ComplexNum& compareResult){
	if (realNum == compareResult.realNum && Imaginary == compareResult.Imaginary)
		return true;
	return false;
}

//implicit casting 
ComplexNum::operator float() {
	float realResult;
	float imagResult;

	realResult = realNum * realNum;
	imagResult = Imaginary * Imaginary * -1;

	float result = realResult + imagResult;

	return result;
}