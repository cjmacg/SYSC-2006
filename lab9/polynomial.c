/* polynomial.c - SYSC 2006 Lab 9 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "polynomial.h"

/* Print a polynomial term in the form ax^n; for example,
 * a term with coefficient 4 and exponent 5 is printed as 4x^5.
 */
void print_term(term_t *term)
{
    printf("%dx^%d\n", term->coeff, term->exp);
    printf("This function should print the term in the form ax^n\n");
}

/* Make a polynomial term with coefficient coeff and exponent exp
 * and return the pointer to the term.
 *
 * Memory for the term is allocated from the heap.
 *
 * Terminate the program via assert if:
 * (1) coeff is 0;
 * (2) malloc fails.
 */
term_t *make_term(int coeff, int exp)
{
    term_t *term = malloc(sizeof(term_t));
    assert(term != NULL);
    term->coeff = coeff;
    assert(term->coeff != 0);
    term->exp = exp;
    return term; //forgot to change this from NULL originally
}

/* Return the value of a polynomial term; i.e., return ax^n for a term with
 * coefficient a and exponent n when evaluated at x.
 * Example: if a term has coefficient 3 and exponent 2 and x is 4.0, 
 * this function returns 3(4.0^2), which is 48.0.
 */
double eval_term(term_t *term, double x)
{
    //don't know if I need to cast to double somewhere below
    //I assume that's handled by return type.
    //I think pow is allowed considering math.h is already included.
    return term->coeff * pow(x,(term->exp));
}

/* Make a polynomial that has 0 terms and return the pointer to the polynomial. 
 * The polynomial can store up to MAX_TERMS terms (see polynomial.h).
 *
 * Memory for the polynomial is allocated from the heap.
 *
 * Terminate the program via assert if malloc fails.
 */
polynomial_t *make_polynomial(void)
{
    polynomial_t *polynomial = malloc(sizeof(polynomial_t));
    assert(polynomial != NULL);
    polynomial->num_terms = 0;
    return polynomial;
}

/* Add a term to a polynomial.
 *
 * This function doesn't check if the polynomial already contains a term with the
 * same exponent as the term being added; in other words, it's the caller's 
 * reponsibility to ensure that the polynomial doesn't have terms with duplicate 
 * exponents.
 *
 * Terminate the program via assert if there's no room in the polynomial for 
 * additional terms.
 */
void add_term(polynomial_t *poly, term_t *term)
{
    assert(poly->num_terms != MAX_TERMS);
    //poly structs terms is termpointer array indexable to largest new entry, which is entry num terms
    //so sets address of termpointer array entry to param term pointer to set
    poly->terms[poly->num_terms] = term;
    poly->num_terms++; //increase term count by one
}

/* Return the value of a polynomial when it is evaluated at x.
 *
 * Terminate the program via assert if the polynomial has 0 terms.
 */
double eval_polynomial(polynomial_t *poly, double x)
{
    assert(poly->num_terms != 0);
    double result = 0;
    //doesn't use walking pointer, but should be good?
    for (int i = 0; i < poly->num_terms; i++) {
        result += eval_term(poly->terms[i], x);
    }
    return result;
}
