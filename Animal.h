/*
 * Animal.h
 *
 *  Created on: Dec 13, 2020
 *      Author: 1745124_snhu
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include <string>
#include <vector>
using namespace std;

class Animal {
	public:
		void SetEggs(int eggs);
		void SetNurse(int Nurse);
		void SetAnimalName(string animalName);
		void SetTrackNumber(int trackNumber);
		void SetAnimalType(string animalType);
		void SetAnimalSubType(string animalSubType);

		int GetTrackNumber();
		string GetAnimalName();
		string GetAnimalType();
		string GetAnimalSubType();

		Animal();


	protected:

		//vector <Animal*> animals;
		//vector<Animal> animalVector;

	private:
		int trackNumber;
		string animalName;
		string animalType;
		string animalSubType;
};

#endif /* ANIMAL_H_ */
