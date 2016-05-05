#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <boost/algorithm/string/replace.hpp>

std::string FindAndReplace(std::string const& subject, std::string const& search, std::string const& replace);