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
	Integer a("3345354652134");
	Integer inc("354645");

		cout << a*inc << endl;
	return EXIT_SUCCESS;
}