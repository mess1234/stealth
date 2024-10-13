#ifndef __VECTOR_H
#define __VECTOR_H
/**
 * @file vector.h
 * @brief Vector module.
 * @author CHERRATI Sid-Ali
 * @author MESSEANT ADRIEN
 * @date 12/01/2023
*/
typedef struct _Vector
{
    double y; /* vertical coordinate */
    double x; /* horizontal coordinate */
} Vector;

/**
 * @brief Test if two vectors are equals.
 *
 * @param v pointer to a vector (must not be NULL)
 * @param w pointer to a vector (must not be NULL)
 * @return int 1 if *v and *w are equals, 0 otherwise.
 */
int equals(Vector *v, Vector *w);

/**
 * @brief Return the sum of v and w.
 *
 * @param v a vector
 * @param w a vector
 * @return Vector v + w
 */
Vector add(Vector v, Vector w);

/**
 * @brief Return the difference of v and w.
 *
 * @param v a vector
 * @param w a vector
 * @return Vector v - w
 */
Vector sub(Vector v, Vector w);

/**
 * @brief Return v scaled by num.
 *
 * @param v a vector
 * @param num a number
 * @return Vector num * v
 */
Vector scale(Vector v, double num);

/**
 * @brief Return v rotated 90° clockwise.
 *
 * @param v a vector
 * @return Vector {+v.x, -v.y}
 */
Vector rotate_cw(Vector v);

/**
 * @brief Return v rotated 90° counterclockwise.
 *
 * @param v a vector
 * @return Vector {-v.x, +v.y}
 */
Vector rotate_ccw(Vector v);

/**
 * @brief Return v with truncated coordinates.
 *
 * @param v a vector
 * @return Vector {floor(v.y), floor(v.x)}
 */
Vector floored(Vector v);

/**
 * @brief Return the norm of the vector v (== its distance to zero).
 *
 * @param v a vector
 * @return double |v|
 */
double norm(Vector v);

/**
 * @brief Return the euclidean distance between the points v and w.
 *
 * @param v a vector
 * @param w a vector
 * @return double |v - w|
 */
double dist(Vector v, Vector w);

#endif /* __VECTOR_H */
