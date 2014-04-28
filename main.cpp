/*
 * main.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/21/14
 * 
 * This file will be used for tests and debug session, but will have no interest for the project itself.
 */

#include <iostream>
#include "Integer.h"
#include "Digit.h"

using namespace std;

int main(int argc, const char* argv[])
{
	Integer a("10001");
	Integer b("2");
	Integer c(a-b);

	cout << "  " << a << endl << "- " << b << endl << "= " << c << endl;
	
	return EXIT_SUCCESS;
}