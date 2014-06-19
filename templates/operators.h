/**
 * \file    operators.h
 * \brief	Operators templates file
 * \details This file defines some templates for operators overloading
 *
 * \warning Not implemented yet
 *
 * \author Richard Degenne
 * \date 05-27-2014
 *
 */

#ifndef MathParser_operators_h
#define MathParser_operators_h

template <class T>
T operator+(T const&, T const&);

template <class T>
T operator-(T const&, T const&);

template <class T>
T operator*(T const&, T const&);

template <class T>
T operator/(T const&, T const&);

template <class T>
T operator%(T const&, T const&);


// Template implementation
#include "operators.tpp"

#endif
