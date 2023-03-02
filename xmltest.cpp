#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include "tinyxml2.cpp"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#define MAXSIZE 100

#if defined( _MSC_VER ) || defined (WIN32)
	#include <crtdbg.h>
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#else
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

using namespace tinyxml2;
using namespace std;
int gPass = 0;
int gFail = 0;

bool XMLTest (const char* testString, const char* expected, const char* found, bool echo=true, bool extraNL=false )
{
	bool pass;
	if ( !expected && !found )
		pass = true;
	else if ( !expected || !found )
		pass = false;
	else
		pass = !strcmp( expected, found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( !echo ) {
		printf (" %s\n", testString);
	}
	else {
		if ( extraNL ) {
			printf( " %s\n", testString );
			printf( "%s\n", expected );
			printf( "%s\n", found );
		}
		else {
			printf (" %s [%s][%s]\n", testString, expected, found);
		}
	}

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}

bool XMLTest(const char* testString, XMLError expected, XMLError found, bool echo = true, bool extraNL = false)
{
    return XMLTest(testString, XMLDocument::ErrorIDToName(expected), XMLDocument::ErrorIDToName(found), echo, extraNL);
}

bool XMLTest(const char* testString, bool expected, bool found, bool echo = true, bool extraNL = false)
{
    return XMLTest(testString, expected ? "true" : "false", found ? "true" : "false", echo, extraNL);
}

template< class T > bool XMLTest( const char* testString, T expected, T found, bool echo=true )
{
	bool pass = ( expected == found );
	if ( pass )
		printf ("[pass]");
	else
		printf ("[fail]");

	if ( !echo )
		printf (" %s\n", testString);
	else {
		char expectedAsString[64];
		XMLUtil::ToStr(expected, expectedAsString, sizeof(expectedAsString));

		char foundAsString[64];
		XMLUtil::ToStr(found, foundAsString, sizeof(foundAsString));

		printf (" %s [%s][%s]\n", testString, expectedAsString, foundAsString );
	}

	if ( pass )
		++gPass;
	else
		++gFail;
	return pass;
}

void NullLineEndings( char* p )
{
	while( p && *p ) {
		if ( *p == '\n' || *p == '\r' ) {
			*p = 0;
			return;
		}
		++p;
	}
}

int main()
{
    XMLDocument doc;
    doc.LoadFile("FEEA30.arxml");
    // XMLTest("Load books.xml", false, doc.Error());

    {
		XMLElement* rootElement = doc.FirstChildElement();
		// XMLElement* bookElement = rootElement->FirstChildElement();
		// const char* category;
		// bookElement->QueryStringAttribute("category", &category);

		// XMLElement* titleElement = bookElement->FirstChildElement();
		// const char* lang;
		// titleElement->QueryStringAttribute("lang", &lang);
		// const char* title = titleElement->GetText();
		// XMLElement* authorElement = titleElement->NextSiblingElement();
		// const char* author = authorElement->GetText();
		// XMLElement* yearElement = authorElement->NextSiblingElement();
		// const char* year = yearElement->GetText();
		// XMLElement* priceElement = yearElement->NextSiblingElement();
		// const char* price = priceElement->GetText();

		// printf("category of the book: %s\n", category);
		// printf("language of the book: %s\n", lang);
		// printf("title of the book: %s\n", title);
		// printf("author of the book: %s\n", author);
		// printf("year of the book: %s\n", year);
		// printf("price of the book: %s\n", price);

		// doc.Print();
		char targetElement[] = "I-SIGNAL-I-PDU";
		// 找”仅第一个“ I-SIGNAL-I-PDU元素，赋给 StartElement
		doc.AcceptTree(rootElement, targetElement);
		// 从 StartElement开始，读出所有并列的 I-SIGNAL-I-PDU元素
		doc.generateMap3(StartElement);
	}

	// map<string, map<string, int>> maps;

	// maps["bookstore"] = {{"book", 4}, {"pen", 3}};
	// maps["book"] = {{"title", 1}, {"author", 4}, {"year", 1}, {"price", 1}};
	// // 生成map时，如果node节点下只有文本节点，则int代表“所属book具体里有几个author”
	// maps["title"] = {{"Everyday Italian", 1}, {"Harry Potter", 1}, {"XQuery Kick Start", 1}, {"Learning XML", 1}};
	// maps["author"] = {{"Giada De Laurentiis", 1}, {"J K. Rowling", 1}, {"James McGovern", 4}, {"Per Bothner", 4},
	// 							 {"Kurt Cagle", 4}, {"James Linn", 4}, {"Erik T. Ray", 2}, {"Frank", 2}};
	// maps["year"] = {{"2005", 1}, {"2005", 1}, {"2003", 1}, {"2003", 1}};
	// maps["price"] = {{"30.00", 1}, {"29.99", 1}, {"49.99", 1}, {"39.95", 1}};

	// maps["Everyday Italian"] = {"", 0};
	// maps["Harry Potter"] = {"", 0};

    return 0;
}