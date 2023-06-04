/*
	Name: BOW Saves Test
	Copyright: 2022
	Author: Daniel R. Collins
	Date: 2022-12-26
	Description: Test solo saving throws at BOW scale.
*/
#include "Dice.h"
#include <cmath>
#include <iostream>
#include <assert.h>
using namespace std;

// Game constants
const Dice hitDice("9d8+9");
const Dice damageDice("6d6");
const int saveTarget = 12;

// Simulator constants
const int NUM_TRIALS = 10000;

// Dice constants (from Troll Dice)
const float CHANCE_AT_LEAST_ON_2D6[] = {
	1.00000, 0.97222, 0.91667, 0.83333, 0.72222, 0.58333,
	0.41667, 0.27778, 0.16667, 0.08333, 0.02778, 0.00000
};
const int SIZE_2D6_SPACE = 12;

// Do a bunch of trials with spillover damage
// Return ratio of targets killed
double doManyTrials () {
	int numDead = 0;
	int hitPoints = hitDice.roll();
	for (int trial = 0; trial < NUM_TRIALS; trial++) {
		int damage = damageDice.roll();
		if (Dice::roll(20) >= saveTarget) {
			damage /= 2;
		}
		while (damage >= hitPoints) {
			numDead++;
			damage = damage - hitPoints;
			hitPoints = hitDice.roll();
		}
		hitPoints -= damage;		
	}
	return (double) numDead / NUM_TRIALS;
}

// Convert ratio to closest 2d6 target
int getClosestMark (double ratio) {
	assert(0.0 <= ratio && ratio <= 1.0);
	
	// Get first index of lower-bound for given ratio
	int idx;
	for (idx = 0; idx < SIZE_2D6_SPACE; idx++) {
		if (CHANCE_AT_LEAST_ON_2D6[idx] <= ratio) {
			break;	
		}
	}
	
	// If first index, we're done
	if (idx == 0) {
		return 2;		
	}
	
	// See if we're closer to upper-bound index or one before
	float highVal = CHANCE_AT_LEAST_ON_2D6[idx - 1];
	float lowVal = CHANCE_AT_LEAST_ON_2D6[idx];
	float stepSize = highVal - lowVal;
	return (ratio - lowVal < stepSize / 2) ?
		idx + 2 : idx + 1;
}

// Print test results
void printTest () {
	cout << "Test results (ratio, 2d6 target):\n";
	double killRatio = doManyTrials();
	double liveRatio = 1 - killRatio;
	int target = getClosestMark(liveRatio);
	cout << liveRatio << " " << target << endl;
}

// Test 2d6 mark function
void testMarks () {
	assert(getClosestMark(1.00000) == 2);
	assert(getClosestMark(0.97222) == 3);
	assert(getClosestMark(0.91667) == 4);
	assert(getClosestMark(0.99900) == 2);
	assert(getClosestMark(0.97000) == 3);
	assert(getClosestMark(0.02778) == 12);
	assert(getClosestMark(0.02000) == 12);
	assert(getClosestMark(0.01000) == 13);
	assert(getClosestMark(0.00000) == 13);
	cout << "Tests complete\n";
}

// Main test driver
int main (int argc, char** argv) {
	Dice::init();
	//testMarks();
	printTest();
	return 0;
}
