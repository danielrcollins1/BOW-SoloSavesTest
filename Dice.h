/*
	Name: Dice.h
	Copyright: 2022
	Author: Daniel R. Collins
	Date: 26-11-22 00:53
	Description: Interface to the Dice class
*/
#ifndef DICE_H
#define DICE_H

#include <string>

class Dice {
	public:

		// Static functions
		static void init();
		static int roll(int sides);
		static int roll(int num, int sides);
		static int rollPct();
		static bool coinFlip();

		// Constructors
		Dice(int sides);
		Dice(int num, int sides);
		Dice(int num, int sides, int add);
		Dice(int num, int sides, int mul, int add);
		Dice(const char* desc);

		// Accessors
		int getNum() const { return number; }
		int getSides() const { return sides; }
		int getMul() const { return multiplier; }
		int getAdd() const { return addition; }

		// Mutators
		void setNum(int n) { number = n; }
		void setSides(int s) { sides = s; }
		void setMul(int m) { multiplier = m; }
		void setAdd(int a) { addition = a; }

		// Other functions
		int roll() const;
		int minRoll() const;
		int maxRoll() const;
		float avgRoll() const;
		int boundRoll (int floor) const;
		std::string toString() const;

	private:

		// Data declarations
		int number;      /* Number of dice */
		int sides;       /* Sides on the dice */
		int multiplier;  /* Multiplier (negative = divisor) */
		int addition;    /* Addition (negative = subtraction) */

		// Private functions
		int adjustRoll(int roll) const;
};

#endif