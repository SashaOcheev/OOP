#include "stdafx.h"
#include "../UrlParse/stdafx.h"
#include "../UrlParse/HttpUrl.h"
#include <functional>

void VerifyParts(const CHttpUrl &httpurl, const std::string &url, Protocol protocol, const std::string &domain, const std::string &document, unsigned short port)
{
	BOOST_CHECK(httpurl.GetProtocol() == protocol);
	BOOST_CHECK_EQUAL(httpurl.GetDomain(), domain);
	BOOST_CHECK_EQUAL(httpurl.GetDocument(), document);
	BOOST_CHECK_EQUAL(httpurl.GetPort(), port);
	BOOST_CHECK_EQUAL(httpurl.GetURL(), url);
}

bool IsCorrectMessage(const CUrlParsingError& ex, const std::string &correctMsg)
{
	BOOST_CHECK_EQUAL(ex.what(), correctMsg);
	return true;
}

BOOST_AUTO_TEST_SUITE(test_url)

	BOOST_AUTO_TEST_SUITE(Set_By_Parts)
	
		BOOST_AUTO_TEST_CASE(ordinary_parameters)
		{
			CHttpUrl httpurl("arcadefire.com", "images/pic.jpg", Protocol::HTTP, 10);
			VerifyParts(httpurl, "http://arcadefire.com/images/pic.jpg", Protocol::HTTP, "arcadefire.com", "/images/pic.jpg", 10);
		}

		BOOST_AUTO_TEST_CASE(dot_in_end_is_correct)
		{
			CHttpUrl httpurl("arcadefire.com.", "images/pic.jpg", Protocol::HTTP, 10);
			VerifyParts(httpurl, "http://arcadefire.com./images/pic.jpg", Protocol::HTTP, "arcadefire.com.", "/images/pic.jpg", 10);
		}

		BOOST_AUTO_TEST_CASE(port_equals_80_by_default)
		{
			CHttpUrl httpurl("arcadefire.com", "images/pic.jpg", Protocol::HTTP);
			VerifyParts(httpurl, "http://arcadefire.com/images/pic.jpg", Protocol::HTTP, "arcadefire.com", "/images/pic.jpg", 80);
		}

		BOOST_AUTO_TEST_CASE(protocol_equals_http_by_default)
		{
			CHttpUrl httpurl("arcadefire.com", "images/pic.jpg");
			VerifyParts(httpurl, "http://arcadefire.com/images/pic.jpg", Protocol::HTTP, "arcadefire.com", "/images/pic.jpg", 80);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Set_By_String)

		BOOST_AUTO_TEST_CASE(port_equals_80_when_portal_equals_http_by_default)
		{
			CHttpUrl httpurl("http://arcadefire.com/images/pic.jpg");
			VerifyParts(httpurl, "http://arcadefire.com/images/pic.jpg", Protocol::HTTP, "arcadefire.com", "/images/pic.jpg", 80);
		}

		BOOST_AUTO_TEST_CASE(port_equals_443_when_portal_equals_https_by_default)
		{
			CHttpUrl httpurl("https://arcadefire.com/images/pic.jpg");
			VerifyParts(httpurl, "https://arcadefire.com/images/pic.jpg", Protocol::HTTPS, "arcadefire.com", "/images/pic.jpg", 443);
		}

		BOOST_AUTO_TEST_CASE(dot_in_end_is_correct)
		{
			CHttpUrl httpurl("http://arcadefire.com./images/pic.jpg");
			VerifyParts(httpurl, "http://arcadefire.com./images/pic.jpg", Protocol::HTTP, "arcadefire.com.", "/images/pic.jpg", 80);
		}

		BOOST_AUTO_TEST_CASE(protocol_is_insensitive)
		{
			CHttpUrl httpurl("HTTPS://arcadefire.com/images/pic.jpg");
			VerifyParts(httpurl, "https://arcadefire.com/images/pic.jpg", Protocol::HTTPS, "arcadefire.com", "/images/pic.jpg", 443);
		}

	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(Exceptions_By_Parts)

		BOOST_AUTO_TEST_SUITE(Exceptions_In_Domain)
			BOOST_AUTO_TEST_CASE(empty)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must be not empty."));
			}

			BOOST_AUTO_TEST_CASE(invalid_charachters)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("ar*cadefire.com", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has only digits, letters \".\" or \"-\" characters."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl(".arcadefire.com", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_minus)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("-arcadefire.com", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}
			
			BOOST_AUTO_TEST_CASE(without_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("com", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has at least two levels."));
			}

			BOOST_AUTO_TEST_CASE(dot_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire..com", "/images/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Subdomain can not be empty."));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(Exceptions_In_Path)
			BOOST_AUTO_TEST_CASE(incorrect_charachters)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire.com", "/ima*ges/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document name can not contain \\, :, ?, |, \", *, <, > characters."));
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire.com", "/images?/pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document name can not contain \\, :, ?, |, \", *, <, > characters."));
			}

			BOOST_AUTO_TEST_CASE(slash_by_slash)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("arcadefire.com", "/images//pic.jpg", Protocol::HTTP, 80), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document path can not contain folder without name."));
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(Exceptions_In_Url)

		BOOST_AUTO_TEST_CASE(without_protocol_delim)
		{
			BOOST_CHECK_EXCEPTION(CHttpUrl("http:/arcadefire.com/images/pic.jpg"), CUrlParsingError
				, std::bind(IsCorrectMessage, std::placeholders::_1, "Url must has protocol before \"://\"."));
		}

		BOOST_AUTO_TEST_SUITE(Exceptions_In_Domain)
			BOOST_AUTO_TEST_CASE(empty)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http:///images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must be not empty."));
			}

			BOOST_AUTO_TEST_CASE(invalid_charachters)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://arc*adefire.com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has only digits, letters \".\" or \"-\" characters."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://.arcadefire.com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}

			BOOST_AUTO_TEST_CASE(begins_by_minus)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://-arcadefire.com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain can not begin by \"-\" or \".\"."));
			}

			BOOST_AUTO_TEST_CASE(without_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Domain must has at least two levels."));
			}

			BOOST_AUTO_TEST_CASE(dot_by_dot)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://arcadefire..com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Subdomain can not be empty."));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(Exceptions_In_Path)
			BOOST_AUTO_TEST_CASE(incorrect_charachters)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://arcadefire.com/ima*ges/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document name can not contain \\, :, ?, |, \", *, <, > characters."));
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://arcadefire.com/images?/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document name can not contain \\, :, ?, |, \", *, <, > characters."));
			}

			BOOST_AUTO_TEST_CASE(slash_by_slash)
			{
				BOOST_CHECK_EXCEPTION(CHttpUrl("http://arcadefire.com/images//pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Document path can not contain folder without name."));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Exceptions_In_Protocol)
			BOOST_AUTO_TEST_CASE(not_http_or_https)
			{
				BOOST_CHECK_THROW(CHttpUrl("ftp://arcadefire.com/images/pic.jpg"), CUrlParsingError
					, std::bind(IsCorrectMessage, std::placeholders::_1, "Protocol must be \"http\" or \"https\"."));
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()