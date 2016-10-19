// UrlParse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpUrl.h"

void GetUrl()
{
	std::string URL = "";
	std::cout << "Enter URL: ";
	while (std::getline(std::cin, URL))
	{
		try
		{
			auto httpurl = CHttpUrl(URL);
			std::cout << "URL: " << httpurl.GetURL() << std::endl;
			std::cout << "Protocol: " << (httpurl.GetProtocol() == Protocol::HTTP ? "http" : "https") << std::endl;
			std::cout << "Document: " << httpurl.GetDocument() << std::endl;
			std::cout << "Port: " << httpurl.GetPort() << std::endl;
		}
		catch (CUrlParsingError &e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "Enter URL: ";
	}
}

int main()
{
	GetUrl();

    return 0;
}

