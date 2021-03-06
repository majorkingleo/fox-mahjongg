#include "OutDebug.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <DetectLocale.h>

OutDebug::OutDebug()
: Debug(),
  colored_output(true)
{
#ifdef WIN32
	colored_output = false;
#else
	char *pcTerm =  getenv( "TERM");

	if( pcTerm == NULL || !isatty(fileno(stdout)))
	{
		colored_output = false;
	}
#endif
}


void OutDebug::add( const char *file, unsigned line, const char *function, const std::string & s )
{
	if( colored_output )
	{
		std::cout << "\033[1;33m";
	}

	std::cout << file;

	if( colored_output )
	{
		std::cout << "\033[0m";
	}

	std::cout << ':' << line
			<< " " // << function
			<< s
			<< '\n';
}

void OutDebug::add( const char *file, unsigned line, const char *function, const std::wstring & s )
{
	if( colored_output )
	{
		std::cout << "\033[1;33m";
	}

	std::cout << file;

	if( colored_output )
	{
		std::cout << "\033[0m";
	}

#if !defined WIN32 && !defined _WIN32
	std::cout << ':' << line
			<< " " // << function
			<< DetectLocale::w2out(s)
			<< '\n';
#endif
}
