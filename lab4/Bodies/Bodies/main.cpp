// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"



int main()
{
	//auto vect = ReadBodies(std::cin);
	//GetMaxMassBody(std::cout, vect);
	//GetMinWeightBody(std::cout, vect);
	auto compound1 = std::make_shared<CCompound>(CCompound());
	compound1->AddBody(std::make_shared<CCone>(CCone(1, 1, 1)));
	auto compound0 = std::make_shared<CCompound>(CCompound());
	compound0->AddBody(compound1);
	compound1->AddBody(compound0);

	std::cout << compound1->ToString() << std::endl;
    return 0;
}

