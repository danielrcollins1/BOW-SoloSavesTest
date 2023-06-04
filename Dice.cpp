/*
	Name: Dice.cpp
	Copyright: 2022
	Author: Daniel R. Collins
	Date: 26-11-22 00:55
	Description: Implementation of the Dice class
*/
#include "Dice.h"
#include <cstdlib>
#include <cstring>
#include <ctime>

// Initializer
void Dice::init() {
	srand(time(0));
}

// Roll one die in static context
int Dice::roll(int sides) {
	return rand() % sides + 1;
}

// Roll multiple dice in static context
int Dice::roll(int num, int sides) {
	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += roll(sides);
	return sum;
}

// Constructor (full)
Dice::Dice(int num, int sides_, int mul, int add) {
	number = num;
	sides = sides_;
	multiplier = mul;
	addition = add;
}

// Constructor (NdS+A)
Dice::Dice(int num, int sides, int add):
	Dice(num, sides, 1, add) {}

// Constructor (NdS)
Dice::Dice(int num, int sides):
	Dice(num, sides, 1, 0) {}

// Constructor (1dS)
Dice::Dice(int sides):
	Dice(1, sides, 1, 0) {}

// Constructor (from string description)
Dice::Dice(const char* desc):
	Dice(1, 0, 1, 0) {

	// Check for constant value
	char *ptr;
	if (!(ptr = strchr(desc, 'd'))) {
		number = 0;
		addition = atoi(desc);
		return;
	}

	// Get sides & number
	sides = atoi(ptr + 1);
	number = atoi(desc);
	if (number == 0) {
		number = 1;
	}

	// Get multiplier or divisor
	if ((ptr = strchr(desc, 'x')))
		multiplier = atoi(ptr + 1);
	if ((ptr = strchr(desc, '/')))
		multiplier = - atoi(ptr + 1);

	// Get addition or subtraction
	if ((ptr = strchr(desc, '+')))
		addition = atoi(ptr + 1);
	if ((ptr = strchr(desc, '-')))
		addition = - atoi(ptr + 1);
}

// Get string representation
std::string Dice::toString() const {
	if (!number || !multiplier)
		return std::to_string(addition);
	std::string s =
	    std::to_string(number) + "d" + std::to_string(sides);
	if (multiplier > 1)
		s += "x" + std::to_string(multiplier);
	else if (multiplier < 0)
		s += "/" + (std::to_string(- multiplier));
	if (addition > 0)
		s += "+" + std::to_string(addition);
	else if (addition < 0)
		s += "-" + (std::to_string(- addition));
	return s;
}

// Roll the dice
int Dice::roll() const {
	int baseRoll = roll(number, sides);
	return adjustRoll(baseRoll);
}

// Adjust base roll for multiplier & addition
int Dice::adjustRoll(int roll) const {
	if (multiplier >= 0)
		roll *= multiplier;
	else
		roll = (roll - 1) / (- multiplier) + 1;
	roll += addition;
	return roll;
}

// Roll percentile dice from static context
int Dice::rollPct() {
	return roll(100);
}

// Flip a coin from static context
bool Dice::coinFlip() {
	return rand() % 2;
}

// Get the minimum roll
int Dice::minRoll() const {
	return adjustRoll(number);
}

// Get the maximum roll
int Dice::maxRoll () const {
	return adjustRoll(number * sides);
}

// Get the average roll
float Dice::avgRoll() const {
	return (float) (minRoll() + maxRoll()) / 2;
}

// Roll with some lower bound
int Dice::boundRoll (int floor) const {
	int baseRoll = roll();
	return baseRoll > floor ? baseRoll : floor;
}
