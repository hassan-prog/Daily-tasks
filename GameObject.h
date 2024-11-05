#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class GameObject
{
private:
	void initVariables();
protected:
	Snake* player;
	
	float objPositionX;
	float objPositionY;

	virtual bool checkPlayerPos();

public:
	GameObject();
};