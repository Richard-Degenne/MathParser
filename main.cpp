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
#include "Natural.h"
#include "Digit.h"

using namespace std;

int main(int argc, const char* argv[])
{
	Natural	a("22435");
	Natural b("54321");
	cout << a*b << endl;
	return EXIT_SUCCESS;
}