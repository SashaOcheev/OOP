// Bodies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "program.h"
#include "BodiesVector.h"



int main()
{
	CBodiesVector vect;
	vect.ReadBodies(std::cin);
	vect.GetMaxMassBody(std::cout);
	vect.GetMinWeightBody(std::cout);
    return 0;
}

