#include <iostream>

class GeometricShape {
public:
	virtual float calcArea() {
		return 0;
	}
};

class Circle : public GeometricShape {
private:
	float radius;
	float pi = 3.1415;

public:
	Circle(float radius) {
		this->radius = radius;
	}

	float calcArea()
		override
	{
		return pi * radius * radius;
	}
};

class Square : public GeometricShape {
private:
	float x;

public:
	Square(float x) {
		this->x = x;
	}

	float calcArea()
		override
	{
		return x * x;
	}
};

class Triangle : public GeometricShape {
private:
	float l;
	float height;

public:
	Triangle(float l, float height) {
		this->l = l;
		this->height = height;
	}

	float calcArea()
		override
	{
		return 0.5 * l * height;
	}
};

class Rectangle : public GeometricShape {

private:
	float x;
	float y;

public:
	Rectangle(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float calcArea()
		override
	{
		return x * y;
	}
};


void calcArea(GeometricShape* character) {
	std::cout << "Area = " << character->calcArea() << '\n';
}

int main()
{
	Circle Circ(3);
	Triangle triangle(4, 6);
	Square square(4);
	Rectangle rect(5, 4);

	calcArea(&Circ);
	calcArea(&triangle);
	calcArea(&square);
	calcArea(&rect);
}
