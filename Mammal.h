/*
 * Mammal.h
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */


#ifndef MAMMAL_H_
#define MAMMAL_H_

#include "Animal.h"
using namespace std;

class Mammal : public Animal {
	public:
		void SetNurse(int Nures);
		int GetNurse();

		Mammal();

	private:
		int Nurse;
};


#endif /* MAMMAL_H_ */

