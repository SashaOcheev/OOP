#include "stdafx.h"
#include "../UrlParse/stdafx.h"
#include "../UrlParse/HttpUrl.h"
#include <functional>

struct SParts
{
	Protocol protocol;
	std::string domain;
	std::string document;
	unsigned short port;
	std::string url;
};

void VerifyParts(const CHttpUrl &httpurl, const SParts &parts)
{
	BOOST_CHECK(httpurl.GetProtocol() == parts.protocol);
	BOOST_CHECK_EQUAL(httpurl.GetDomain(), parts.domain);
	BOOST_CHECK_EQUAL(httpurl.GetDocument(), parts.document);
	BOOST_CHECK_EQUAL(httpurl.GetPort(), parts.port);
	BOOST_CHECK_EQUAL(httpurl.GetURL(), parts.url);
}

bool IsCorrectMessage(const CUrlParsingError& ex, const std::string &correctMsg)
{
	BOOST_CHECK_EQUAL(ex.what(), correctMsg);
	return true;
}

BOOST_AUTO_TEST_SUITE(Correct_URL)

	struct CorrectParts
	{
		SParts parts;
	
		CorrectParts()
		{
			parts.protocol = Protocol::HTTP;
			parts.domain = "arcadefire.com";
			parts.document = "/images/pic.jpg";
			parts.port = 10;
			parts.url = "http://arcadefire.com/images/pic.jpg";
		}
	};

	BOOST_FIXTURE_TEST_SUITE(Set_By_Parts, CorrectParts)
	
		BOOST_AUTO_TEST_CASE(ordinary_parameters)
		{
			VerifyParts(CHttpUrl(parts.domain, parts.document, parts.protocol, parts.port), parts);
		}

		BOOST_AUTO_TEST_CASE(port_equals_80_by_default)
		{
			parts.port = 80;
			VerifyParts(CHttpUrl(parts.domain, parts.document, parts.protocol), parts);
		}

		BOOST_AUTO_TEST_CASE(protocol_equals_http_by_default)
		{
			parts.protocol = Protocol::HTTP;
			parts.port = 80;
			VerifyParts(CHttpUrl(parts.domain, parts.document), parts);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(Set_By_String, CorrectParts)

		BOOST_AUTO_TEST_CASE(port_equals_80_when_portal_equal_http_by_default)
		{
			parts.port = 80;
			VerifyParts(CHttpUrl(parts.url), parts);
		}

		BOOST_AUTO_TEST_CASE(port_equals_443_when_portal_equal_https_by_default)
		{
			parts.protocol = Protocol::HTTPS;
			parts.url = "https://arcadefire.com/images/pic.jpg";
			parts.port = 443;
			VerifyParts(CHttpUrl(parts.url), parts);
		}

	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_FIXTURE_TEST_SUITE(Exceptions_By_Parts, CorrectParts)

		BOOST_FIXTURE_TEST_SUITE(Exceptions_In_Domain, CorrectParts)
			BOOST_AUTO_TEST_CASE(empty)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must be not empty."));
			}

			BOOST_AUTO_TEST_CASE(invalid_charachters)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("ar*cadefire.com", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has only digits, letters \".\" or \"-\" characters."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl(".arcadefire.com", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_minus)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("-arcadefire.com", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}

			BOOST_AUTO_TEST_CASE(ends_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire.com.", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not come to end by \".\"."));
			}

			BOOST_AUTO_TEST_CASE(without_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("com", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has at least two levels."));
			}

			BOOST_AUTO_TEST_CASE(dot_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire..com", parts.document, parts.protocol, parts.port), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Subdomain can not be empty."));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_FIXTURE_TEST_SUITE(Exceptions_In_Path, CorrectParts)
			BOOST_AUTO_TEST_CASE(incorrect_charachters)
			{
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "/ima*ges/pic.jpg", parts.protocol, parts.port), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "/images?/pic.jpg", parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(slash_by_slash)
			{
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "/images//pic.jpg", parts.protocol, parts.port), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(Exceptions_By_Url, CorrectParts)

		BOOST_AUTO_TEST_CASE(without_protocol_delim)
		{
			BOOST_CHECK_THROW(CHttpUrl("http:/arcadefire.com/images/pic.jpg"), CUrlParsingError);
		}

		BOOST_FIXTURE_TEST_SUITE(Exceptions_In_Domain, CorrectParts)
			BOOST_AUTO_TEST_CASE(empty)
			{
				BOOST_CHECK_THROW(CHttpUrl("http:///images/pic.jpg"), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(invalid_charachters)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://arc*adefire.com/images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(begins_by_dot)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://.arcadefire.com/images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(begins_by_minus)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://-arcadefire.com/images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(ends_by_dot)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://arcadefire.com./images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(without_dot)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://com/images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(dot_by_dot)
			{
				BOOST_CHECK_THROW(CHttpUrl("http://arcadefire..com/images/pic.jpg", parts.document, parts.protocol, parts.port), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_FIXTURE_TEST_SUITE(Exceptions_In_Path, CorrectParts)
			BOOST_AUTO_TEST_CASE(incorrect_charachters)
			{
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "http://arcadefire.com/ima*ges/pic.jpg", parts.protocol, parts.port), CUrlParsingError);
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "http://arcadefire.com/images?/pic.jpg", parts.protocol, parts.port), CUrlParsingError);
			}

			BOOST_AUTO_TEST_CASE(slash_by_slash)
			{
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "http://arcadefire.com/images//pic.jpg", parts.protocol, parts.port), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(Exceptions_In_Protocol, CorrectParts)
			BOOST_AUTO_TEST_CASE(not_http_or_https)
			{
				BOOST_CHECK_THROW(CHttpUrl(parts.domain, "ftp://arcadefire.com/ima*ges/pic.jpg", parts.protocol, parts.port), CUrlParsingError);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()