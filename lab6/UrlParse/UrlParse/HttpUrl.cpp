#include "stdafx.h"
#include "HttpUrl.h"

CHttpUrl::CHttpUrl(std::string const & url)
{
	auto protocolPos = url.find("://");
	if (protocolPos == std::string::npos)
	{
		throw CUrlParsingError("Url must has protocol before \"://\".");
	}
	auto protocolString = url.substr(0, protocolPos);
	auto protocol = GetCorrectProtocol(protocolString);

	auto documentPos = url.find('/', protocolPos + 3);
	if (documentPos == std::string::npos)
	{
		documentPos = url.length();
	}
	
	auto domain = url.substr(protocolPos + 3, documentPos - protocolPos - 3);
	
	auto document = url.substr(documentPos);
	auto port = (protocol == Protocol::HTTP) ? int(Protocol::HTTP) : int(Protocol::HTTPS);

	Init(domain, document, protocol, port);
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
{
	Init(domain, document, protocol, port);
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_protocol == Protocol::HTTP && m_port == int(Protocol::HTTP) || m_protocol == Protocol::HTTPS && m_port == int(Protocol::HTTPS)
		? "" : ":" + std::to_string(m_port));
	return (GetProtocol() == Protocol::HTTP ? "http" : "https") + std::string("://")
		+ GetDomain() + port + GetDocument();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::Init(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
{
	auto newDomain = GetCorrectDomain(domain);
	auto newDocument = GetCorrectDocument(document);
	std::swap(m_domain, newDomain);
	std::swap(m_document, newDocument);
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetCorrectDomain(const std::string & domain) const
{
	if (domain.empty())
	{
		throw CUrlParsingError("Domain must be not empty.");
	}
	if (!std::all_of(domain.begin(), domain.end(), [](char ch) {
		return ch == '.' || ch == '-' || isalnum(ch);
	}))
	{
		throw CUrlParsingError("Domain must has only digits, letters \".\" or \"-\" characters.");
	}
	if (domain.front() == '-' || domain.front() == '.')
	{
		throw CUrlParsingError("Domain can not begin by \"-\" or \".\".");
	}
	if (domain.find('.') == std::string::npos)
	{
		throw CUrlParsingError("Domain must has at least two levels.");
	}
	if (domain.find("..") != std::string::npos)
	{
		throw CUrlParsingError("Subdomain can not be empty.");
	}
	return domain;
}

std::string CHttpUrl::GetCorrectDocument(const std::string & document) const
{
	if (std::any_of(document.begin(), document.end(), [](char ch) {
		return ch == '\\' || ch == ':' || ch == '?' || ch == '|' || ch == '<' || ch == '\"' || ch == '>' || ch == '*';
	}))
	{
		throw CUrlParsingError("Document name can not contain \\, :, ?, |, \", *, <, > characters.");
	}
	if (document.find("//") != std::string::npos)
	{
		throw CUrlParsingError("Document path can not contain folder without name.");
	}
	return (document.empty() || document.front() != '/' ? "/" + document : document);
}

Protocol CHttpUrl::GetCorrectProtocol(const std::string & protocol) const
{
	auto lowerCaseProtocol = protocol;
	std::transform(lowerCaseProtocol.begin(), lowerCaseProtocol.end(), lowerCaseProtocol.begin(), ::tolower);
	if (lowerCaseProtocol != "http" && lowerCaseProtocol != "https")
	{
		throw CUrlParsingError("Protocol must be \"http\" or \"https\".");
	}
	return (lowerCaseProtocol == "http") ? Protocol::HTTP : Protocol::HTTPS;

}

unsigned short CHttpUrl::GetCorrectPort(const std::string &port) const
{
	return 0;
}
