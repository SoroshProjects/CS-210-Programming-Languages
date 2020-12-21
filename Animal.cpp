/*
 * Animal.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */
#include<iostream>

#include "Animal.h"

using namespace std;

// Default constructor ======================================================================================

Animal::Animal() {
	 trackNumber = -1;
	 animalName = "";
	 animalType = "";
	 animalSubType = "";
}


//===========================================================================================================
// Setter Function ==========================================================================================

void Animal::SetTrackNumber(int trackNumber) {
	this->trackNumber = trackNumber;
}

void Animal::SetAnimalName(string animalName) {
			this->animalName = animalName;
		}

void Animal::SetAnimalType(string animalType) {
	this->animalType = animalType;
}

void Animal::SetAnimalSubType(string animalSubType) {
	this->animalSubType = animalSubType;
}

/*void Animal::SetEggs(int eggs) {
	this->eggs = eggs;
}

void Animal::SetNurse(int Nurse) {
	this->Nurse = Nurse;
}
*/

//===========================================================================================================
// Getter Function ==========================================================================================

int Animal::GetTrackNumber() {
	return trackNumber;
}

string Animal::GetAnimalName() {
	return animalName;
}

string Animal::GetAnimalType() {
			return animalType;
		}

string Animal::GetAnimalSubType() {
	return animalSubType;
}

