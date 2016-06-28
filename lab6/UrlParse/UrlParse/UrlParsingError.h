#pragma once
class CUrlParsingError :
	public std::invalid_argument
{
public:
	CUrlParsingError(const std::string & msg);
};

