#pragma once
#include <iostream>
#include <string>
#include "Character.h"
class SnowQueen : public Character
{
private:
	string name;

public:

	void setName(string s);
	//replace getName inherited from Character
	string getName();

	void heal(int amount);
	void atkBoost(int amount);
	void defBoost(int amount);
};


