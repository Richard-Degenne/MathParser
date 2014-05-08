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
	Integer a("123456789"), c("987654321");

	cout << a*c << endl;
	return EXIT_SUCCESS;
}