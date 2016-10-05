#pragma once
#include "UrlParsingError.h"
#include <map>
#include <string>
#include <algorithm>


class CHttpUrl
{
public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80)
	{
		if (IsCorrectDomain(domain) && IsCorrectDocument(document) && IsCorrectProtocol(protocol) && IsCorrectPort(port))
		{
			m_domain = domain;
			m_document = document;
			m_protocol = protocol;
			m_port = port;
			return;
		}
	}

	std::string GetURL() const
	{
		std::string protocol = (m_protocol == Protocol::HTTP) ? "http" : "https";
		std::string port = (m_port == static_cast<unsigned short>(m_protocol)) ? "" : std::string(":") + std::to_string(m_port);
		return protocol + "://" + m_domain + port + m_document;
	}

	std::string GetDomain() const
	{
		return m_domain;
	}

	std::string GetDocument() const
	{
		return m_document;
	}

	Protocol GetProtocol() const
	{
		return m_protocol;
	}

	unsigned short GetPort() const
	{
		return m_port;
	}

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	bool IsCorrectDomain(const std::string & domain)
	{
		if (domain.empty())
		{
			throw CUrlParsingError("Domain is empty");
		}
		bool isCorrectCharachters = std::all_of(domain.begin(), domain.end(), [](const char ch) {
			return isalnum(ch) && (ch == '-') && (ch == '.');
		});
		if (!isCorrectCharachters || domain.front() == '-' || domain.front() == '.' ||
			domain.back() == '-' || domain.back() == '.' || domain.find("..") != std::string::npos)
		{
			throw CUrlParsingError("Domain has invalid sequence of characters");
		}
		return true;
	}

	bool IsCorrectDocument(const std::string & document)
	{
		
	}
};
