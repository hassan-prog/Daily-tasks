#include "GameObject.h"

//private functions
void GameObject::initVariables() {
    this->objPositionX = 0;
    this->objPositionY = 0;
}

//protected functions
bool GameObject::checkPlayerPos()
{
    return false;
}

//Constructors & destructors
GameObject::GameObject() {
    this->initVariables();
}

