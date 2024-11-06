#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class GameObject
{
private:
	void initVariables();
protected:
	Snake* player;
	
	int objPositionX;
	int objPositionY;

	virtual bool checkPlayerPos();

public:
	GameObject();
};