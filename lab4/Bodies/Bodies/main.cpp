// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"



int main()
{
	/*auto vect = ReadBodies(std::cin);
	GetMaxMassBody(std::cout, vect);
	GetMinWeightBody(std::cout, vect);*/
	CCompound compound;
	compound.AddBody(std::make_shared<CCone>(CCone(1, 1, 1)));
	compound.AddBody(std::make_shared<CCompound>(compound));
	std::cout << compound.ToString() << std::endl;
    return 0;
}

