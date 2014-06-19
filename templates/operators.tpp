/**
 * \file    operators.tpp
 * \brief	Operators templates implementation
 * \details This file defines some templates for operators overloading
 * 
 * \warning Not implemented yet
 *
 * \author Richard Degenne
 * \date 05-27-2014
 *
 */
 
 #include <type_traits>
 
 template <class T>
 T operator+(T const& a, T const& b) {
    T copy{a};
    copy += b;
    return copy;
 }
 
 template <class T>
 T operator-(T const& a, T const& b) {
    T copy{a};
    copy -= b;
    return copy;
 }
 
 template <class T>
 T operator*(T const& a, T const& b) {
    T copy{a};
    copy *= b;
    return copy;
 }
 
 template <class T>
 T operator/(T const& a, T const& b) {
    T copy{a};
    copy /= b;
    return copy;
 }
 
 template <class T>
 T operator%(T const& a, T const& b) {
    T copy{a};
    copy %= b;
    return copy;
 }