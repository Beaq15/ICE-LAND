#include "SnowQueen.h"

void SnowQueen::setName(string s) {
	name = s;
}
string SnowQueen::getName() {
	return name;
}

void SnowQueen::heal(int amount) {
	hp += amount; //hp = hp + amount;
	if (hp > hpMax)
		hp = hpMax;

}
void SnowQueen::atkBoost(int amount) {
	str += amount;
}
void SnowQueen::defBoost(int amount) {
	def += amount;
}
