#pragma once
#include "UrlParsingError.h"
#include <map>
#include <string>
#include <algorithm>


class CHttpUrl
{
public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	std::invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	void Init(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80);
	std::string GetCorrectDomain(const std::string & domain);
	std::string GetCorrectDocument(const std::string & document);
	Protocol GetCorrectProtocol(const std::string & protocol);
	unsigned short GetCorrecPort(const unsigned short port);
};
