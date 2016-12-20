// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"

int main()
{
	auto vect = ReadBodies(std::cin);
	GetMaxMassBody(std::cout, vect);
	GetMinWeightBody(std::cout, vect);

    return 0;
}

