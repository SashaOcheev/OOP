#pragma once

#include <set>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSetOfInt(std::set<int> const& set, std::ostream &stream);
