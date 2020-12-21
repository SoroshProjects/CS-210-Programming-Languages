/*
 * Mammal.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */


#include "Mammal.h"


Mammal::Mammal() {
	Nurse = -1;
}

void Mammal::SetNurse(int Nurse) {
	this->Nurse = Nurse;
}

int Mammal::GetNurse() {
	return Nurse;
}
