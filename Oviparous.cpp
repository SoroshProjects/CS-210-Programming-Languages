/*
 * Oviparous.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */


#include "Oviparous.h"

Oviparous::Oviparous() {
	eggs = -1;
}

void Oviparous::SetEggs(int eggs) {
	this->eggs = eggs;
}

int Oviparous::GetEggs() {
	return eggs;
}
