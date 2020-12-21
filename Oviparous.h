/*
 * Oviparous.h
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */


#ifndef OVIPAROUS_H_
#define OVIPAROUS_H_

#include "Animal.h"
using namespace std;

class Oviparous : public Animal {
	public:
		void SetEggs(int eggs);
		int GetEggs();

		Oviparous();

	private:
		int eggs;
};



#endif /* OVIPAROUS_H_ */
