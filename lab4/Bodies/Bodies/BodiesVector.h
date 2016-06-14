#pragma once

std::vector<std::shared_ptr<CBody> > ReadBodies(std::istream & strm);
void GetMaxMassBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs);
void GetMinWeightBody(std::ostream &strm, const std::vector<std::shared_ptr<CBody> > & m_bodyPtrs, const double liquidDensity = 1000.0);