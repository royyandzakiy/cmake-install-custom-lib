#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #if defined(COMPILEDLL)
    #define EXPORT __declspec(dllexport)
  #elif defined(COMPILELIB)
    #define EXPORT
  #else
    #define EXPORT __declspec(dllimport)
  #endif
#else
  #define EXPORT
#endif

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>

class ComplexNumber {
public:
	EXPORT ComplexNumber(double real, double imaginary);
	EXPORT ~ComplexNumber();

	EXPORT double Re() const;
	EXPORT double Im() const;
  EXPORT void setRe(double real);
  EXPORT void setIm(double imaginary);

  EXPORT void conjugate();
  EXPORT double magnitude() const;
	
	EXPORT ComplexNumber operator+(const ComplexNumber &other);
  EXPORT ComplexNumber operator-(const ComplexNumber &other);
  EXPORT ComplexNumber operator*(const ComplexNumber &other);
  EXPORT ComplexNumber operator/(const ComplexNumber &other);

  EXPORT friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &c);

private:
  void isNan(double real, double imaginary) const;
	
private:
	double _real;
	double _imaginary;
};