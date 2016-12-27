// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "program.h"
#include "GetBodies.h"

int main()
{
	auto vect = ReadBodies(std::cin);
	std::cout << vect.GetMaxMassBody() << std::endl;
	std::cout << vect.GetMinWeightBody() << std::endl;
}

