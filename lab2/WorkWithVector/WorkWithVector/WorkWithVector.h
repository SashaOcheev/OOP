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
void Foo(std::vector<double> & numbers, double precision = 0.001);
