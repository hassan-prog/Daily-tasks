#include "ComplexNum.h"
#include <iostream>

int ComplexNum::counter = 0;

ComplexNum::ComplexNum(const ComplexNum& num) {
	this->realNum = num.realNum;
	this->Imaginary = num.Imaginary;
	ComplexNum::counter++;
}

ComplexNum::ComplexNum() {
	this->realNum = 0;
	this->Imaginary = 0;
	ComplexNum::counter++;
}

ComplexNum::ComplexNum(float real, float imag) {
	this->realNum = real;
	this->Imaginary = imag;
	ComplexNum::counter++;
}

ComplexNum::ComplexNum(float real) {
	this->realNum = real;
	this->Imaginary = 0;
	ComplexNum::counter++;
}

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

ComplexNum::~ComplexNum() {
	std::cout << "DESTRUCTION!!!" << '\n';
	ComplexNum::counter--;
}