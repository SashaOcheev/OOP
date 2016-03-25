#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>
#include <string>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSetOfInt(std::set<int> const& set, std::ostream &stream);
