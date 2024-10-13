#ifndef __BACKEND_H
#define __BACKEND_H
/**
 * @file backend.h
 * @brief This file take care of all auxiliary functions needed for the rest of\n
 * the moduls
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
#include "vector.h"

#define V 0.5

typedef enum _Direction
{
    RIGHT,
    UP,
    LEFT,
    DOWN
} Direction;

/**
 * @brief Return an integer between a (inclusive) and b (exclusive). a must be
 * less then b.The probability distribution is non uniform.
 *
 * @param a min value
 * @param b max value + 1
 * @return int an element of {a, ..., b-1}
 */
int rand_int(int a, int b);

/**
 * @brief Return a random number between 0 (inclusive) and sup (exclusive)
 *
 * @param min minimum possible result (or max, if sup <= min)
 * @param sup upper bound of result (or lower bound, if sup <= min)
 * @return double some number in [0, sup[
 */
double rand_double(double min, double sup);

/**
 * @brief Return the unit vector corresponding to dir.
 *
 * @param dir a direction
 * @return Vector a unit vector of the form {+-1.0, +-1.0}
 */
Vector dir_to_vec(Direction dir);

/**
 * @brief Linear interpolation between two numbers.
 * 
 * @param start starting value
 * @param end end value
 * @param t proportion
 * @return double interpolated value, equal to start when t == 0, equal to end
 * when t == 1
 */
double lerp(double start, double end, double t);

#endif /* __BACKEND_H */