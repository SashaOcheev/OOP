#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <ostream>


bool IsEqualDouble(double n1, double n2, double precision = 0.001);
bool IsDivided(double dividend, double divider, double precision = 0.001);
void ProcessVector(std::vector<double> & numbers, double precision = 0.001);
void SortVectorOfDoubles(std::vector<double> & numbers);
