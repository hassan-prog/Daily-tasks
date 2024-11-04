#include <iostream>
#include <vector>

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


float calcArea(GeometricShape* character) {
	return character->calcArea();
}


float calcAvgArea(std::vector<GeometricShape*> shapes) {
	int shapesLength = 0;
	float areaSum = 0;

	for (GeometricShape* shape : shapes)
	{
		areaSum += calcArea(shape);
		shapesLength++;
	}

	return areaSum / shapesLength;
}



int main()
{

	std::vector<GeometricShape*> shapes;

	Circle circleV1(3);
	Circle circleV2(5);
	Triangle triangle(4, 6);
	Square square(4);
	Rectangle rect(5, 4);

	shapes.push_back(&circleV1);
	shapes.push_back(&circleV2);
	shapes.push_back(&triangle);
	shapes.push_back(&square);
	shapes.push_back(&rect);

	float avgArea = calcAvgArea(shapes);

	std::cout << "The average for all areas: " << avgArea << "\n";
}
