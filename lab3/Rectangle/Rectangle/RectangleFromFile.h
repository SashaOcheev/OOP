#pragma once

#include "stdafx.h"
#include "CRectangle.h"

CRectangle SetRectangleFromFile(std::string const& fileName);
void PutRectangleToOstream(CRectangle const& rect, std::string const& rectName, std::ostream & outStream);
void PutRectanglentersectionsToOstream(std::string const& fileName1, std::string const& fileName2, std::ostream & outStream);