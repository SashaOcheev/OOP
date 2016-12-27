// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bodies.h"
#include "HandleBodiesFromStream.h"

int main()
{
	auto vect = GetBodiesFromStream(std::cin);
	std::cout << vect.GetMaxMassBody() << std::endl;
	std::cout << vect.GetMinWeightBody() << std::endl;
}

