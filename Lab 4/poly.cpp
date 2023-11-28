// FILE: poly.h
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// CLASS PROVIDED:
//   class polynomial (in the namespace coen79_lab4)
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//
//
//
// The value semantics (copy constructor and assignment operator) are valid for
// the polynomial class.
//
//

//#ifndef COEN79_POLY_H
//#define COEN79_POLY_H

#include <iostream>  // Provides ostream
#include <math.h>
#include <assert.h>
#include "poly.h"

using namespace coen79_lab4;

namespace coen79_lab4
{
    void polynomial::update_current_degree() {
        for (int i = 0; i < MAXIMUM_DEGREE - 1; i++) {
            if (poly[i + 1] == 0) {
                current_degree = i;
                break;
            }
        }
    }
    // CONSTRUCTOR for the polynomial class
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for (unsigned int i = 0; i <= MAXIMUM_DEGREE; i++)
            poly[i] = 0;
        poly[exponent] = c;
        current_degree = exponent;
    }
    //     PRECONDITION: exponent <= MAXIMUM_DEGREE
    //     POSTCONDITION: This polynomial has been created with all zero
    //     coefficients, except for coefficient c for the specified exponent.
    //     When used as a default constructor (using default values for
    //     both arguments), the result is a polynomial with all zero
    //     coefficients.
    //
    // MODIFICATION MEMBER FUNCTIONS for the polynomial class
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] = coefficient;
        current_degree = exponent;
    }
    //     PRECONDITION: exponent <= MAXIMUM_DEGREE.
    //     POSTCONDITION: Sets the coefficient for the specified exponent.
    //
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] += amount;
        current_degree = exponent;
    }
    //     PRECONDITION: exponent <= MAXIMUM_DEGREE.
    //     POSTCONDITION: Adds the given amount to the coefficient of the
    //     specified exponent.
    //
    void polynomial::clear() {
        for (int i = 0; i <= (unsigned int)degree(); i++)
            poly[i] = 0;
        current_degree = 0;
    }
    //     POSTCONDITION: All coefficients of this polynomial are set to zero.
    //
    // CONSTANT MEMBER FUNCTIONS for the polynomial class
    polynomial polynomial::antiderivative() const {
        polynomial anti(0, degree() + 1);
        assert(degree() < MAXIMUM_DEGREE);
        for (int i = anti.current_degree; i >= 0; i--) {
            anti.poly[i] = poly[i - 1] / i;
        }
        anti.poly[0] = 0;
        return anti;
    }
    //     PRECONDITION: degree( ) < MAXIMUM_DEGREE
    //     POSTCONDITION: The return value is the antiderivative (indefinite integral)
    //     of this polynomial.
    //     NOTE: The return polynomial always has a constant term of zero.
    //
    double polynomial::coefficient(unsigned int exponent) const {
        if (current_degree > MAXIMUM_DEGREE)
            return 0;
        else
            return poly[exponent];
    }
    //     POSTCONDITION: Returns coefficient at specified exponent of this
    //     polynomial.
    //     NOTE: For exponents > MAXIMUM_DEGREE, the return value is always zero.
    //
    double polynomial::definite_integral(double x0, double x1) const {
        polynomial anti = antiderivative();
        return eval(x0) + eval(x1);
    }
    //     POSTCONDITION: Returns the value of the definite integral computed from
    //     x0 to x1.  The answer is computed analytically.
    //
    unsigned int polynomial::degree() const {
        int degree = 0;
        for (int i = MAXIMUM_DEGREE; i > 0; i--)
            if (poly[i] != 0) {
                degree = i;
                break;
            }
        return degree;
    }
    //     POSTCONDITION: The function returns the value of the largest exponent
    //     with a non-zero coefficient.
    //     If all coefficients are zero, then the function returns zero (even
    //     though, technically, this polynomial does not have a degree).
    //
    polynomial polynomial::derivative() const {
        polynomial derive(0, degree() - 1);
        int i = 0;
        for (; i <= derive.current_degree; i++) {
            derive.poly[i] = poly[i + 1] * (i + 1);
        }
        return derive;
    }
    //     POSTCONDITION: The return value is the first derivative of this
    //     polynomial.
    //
    double polynomial::eval(double x) const {
        double y = 0;
        for (int i = 1; i <= current_degree; i++) {
            y += poly[i] * pow(x, i);
        }
        y += poly[0];
        return y;
    }
    //     POSTCONDITION: The return value is the value of this polynomial with the
    //     given value for the variable x.
    //
    bool polynomial::is_zero() const {
        if (poly[current_degree] == 0)
            return true;
        return false;
    }
    //     POSTCONDITION: The return value is true if and only if the polynomial
    //     is the zero polynomial.
    //
    unsigned int polynomial::next_term(unsigned int e) const {
        if (poly[e + 1] != 0)
            return (unsigned int)e + 1;
        else
            return 0;
    }
    //     POSTCONDITION: The return value is the next exponent n which is LARGER
    //     than e such that coefficient(n) != 0.
    //     If there is no such term, then the return value is zero.
    //
    unsigned int polynomial::previous_term(unsigned int e) const {
        if (poly[e - 1] != 0)
            return (unsigned int)e - 1;
        else
            return 0;
    }
    //     POSTCONDITION: The return value is the next exponent n which is SMALLER
    //     than e such that coefficient(n) != 0.
    //     If there is no such term, then the return value is UINT_MAX
    //     from <climits>.
    //
    // CONSTANT OPERATORS for the polynomial class
    double polynomial::operator( ) (double x) const {
        double y = 0;
        for (int i = 0; i < current_degree; i++) {
            y += poly[i] * pow(x, i);
        }
        return y;
    }
    //     Same as the eval member function.
    //

    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        unsigned int degree = 0;
        if (p1.degree() <= p2.degree())
            degree = p2.degree();
        else
            degree = p1.degree();
        polynomial p3(0, degree);
        for (unsigned int i = 0; i <= degree; i++)
            p3.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        unsigned int degree = 0;
        if (p1.degree() <= p2.degree())
            degree = p2.degree();
        else
            degree = p1.degree();
        polynomial p3(0, degree);
        for (unsigned int i = 0; i < degree; i++)
            p3.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= 30);
        unsigned int degree = p1.degree() + p2.degree();
        polynomial p3(0, degree);
        unsigned int i, j;
        for (i = 0; i <= p1.degree(); i++)
        {
            for (j = 0; j <= p2.degree(); j++) {
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        return p3;
    }
    //
    //
    // NON-MEMBER OUTPUT FUNCTIONS for the polynomial Class
    ostream& operator << (ostream& out, const polynomial& p) {
        if (p.coefficient(p.degree()) < 0)
            out << "-" << p.coefficient(p.degree()) * -1 << "x^" << p.degree();
        else if (p.coefficient(p.degree()) > 0)
            out << p.coefficient(p.degree()) << "x^" << p.degree();
        for (int i = p.degree() - 1; i >= 0; i--) {
            if (p.coefficient(i) < 0 && p.coefficient(i) != 1) {
                if (i > 1)
                    out << " - " << p.coefficient(i) * -1 << "x^" << i;
                else if (i == 1)
                    out << " - " << p.coefficient(i) * -1 << "x";
                else
                    out << " - " << p.coefficient(i) * -1;
            }
            else if (p.coefficient(i) > 0 && p.coefficient(i) != 1) {
                if (i > 1)
                    out << " + " << p.coefficient(i) << "x^" << i;
                else if (i == 1)
                    out << " + " << p.coefficient(i) << "x";
                else
                    out << " + " << p.coefficient(i);
            }
            else if (p.coefficient(i) == 1)
                if (i > 1)
                    out << " + x^" << i;
                else if (i == 1)
                    out << " + x";
                else
                    out << " + " << i;
            else if (p.coefficient(i) == -1)
                if (i > 1)
                    out << " - x^" << i;
                else if (i == 1)
                    out << " - x";
                else
                    out << " - " << i;
        }
        return out;
}