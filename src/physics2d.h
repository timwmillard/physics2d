/*
MIT License
Copyright (c) 2024 Tim Millard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "stb_ds.h"

static inline double map(const double value,
        const double start1, const double stop1,
        const double start2, const double stop2)
{
    return (value - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

static inline double max(const double a, const double b)
{
    return (a > b)? a : b;
}

static inline double min(const double a, const double b)
{
    return (a < b)? a : b;
}
/* generate a random floating point number from min to max 
 * #include <time.h>
 * srand(time(NULL));
 * */
static double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

extern void noise_seed(int seed);
extern double noise(double x);
extern double noise2(double x, double y);
extern double noise3(double x, double y, double z);
/* extern void destroy_noise(); */


/**
 * 2D Vector function
 * 
 */
typedef struct Vec2 {
    double x;
    double y;
} Vec2;

static const Vec2 vec2zero = {0.0f, 0.0f};

static inline Vec2 vec2(const double x, const double y)
{
    Vec2 vec = {x, y};
    return vec;
}

static inline Vec2 vec2_add(const Vec2 a, const Vec2 b)
{
    return vec2(a.x + b.x, a.y + b.y);
}

static inline Vec2 vec2_sub(const Vec2 a, const Vec2 b)
{
    return vec2(a.x - b.x, a.y - b.y);
}

static inline double vec2_dot(const Vec2 a, const Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

// Returns the magnitude (length) of the vector.
static inline double vec2_mag(const Vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

// Returns the magnitude (length) of the vector squared.
static inline double vec2_mag_sq(const Vec2 v)
{
    return v.x * v.x + v.y * v.y;
}

static inline Vec2 vec2_mult(const Vec2 v, const double m)
{
    return vec2(v.x * m, v.y * m);
}

static inline Vec2 vec2_div(const Vec2 v, const double m)
{
    return m == 0 ? vec2zero : vec2(v.x / m, v.y / m);
}

static inline Vec2 vec2_normalize(const Vec2 v)
{
    double mag = vec2_mag(v);
    return mag == 0 ? vec2zero : vec2(v.x/mag, v.y/mag);
}

// Set the magnitude (length) of the vector.
// Returns a new Vec2.
static inline Vec2 vec2_set_mag(const Vec2 v, double m)
{
    return vec2_mult(vec2_normalize(v), m);
}

static inline Vec2 vec2_neg(const Vec2 v)
{
    return vec2(-v.x, -v.y);
}

static inline bool vec2_equal(const Vec2 v1, const Vec2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

/* First seed:
 * #include <time.h>
 * srand(time(NULL));
 */
static inline Vec2 vec2_random()
{
    double x = randfrom(-1, 1);
    double y = randfrom(-1, 1);
    return vec2(x, y);
}

// Limits a vector's magnitude to a maximum value. 
static inline Vec2 vec2_limit(const Vec2 v, double max)
{
    double mag = vec2_mag(v);
    if (mag <= max) return v;
    return vec2_set_mag(v, max);
}

/**
 * Vec2 TODO Funcs


// Limits a vector's magnitude to a maximum value. 
static inline Vec2 vec2_limit(const Vec2 v, double m);

// Calculates the angle a 2D vector makes with the positive x-axis. Angles increase in the clockwise direction.p
static inline double vec2_heading(const Vec2 v);

// Rotates a 2D vector to a specific angle without changing its magnitude. By convention, the positive x-axis has an angle of 0. Angles increase in the clockwise direction.
static inline Vec2 vec2_set_heading(const Vec2 v, double angle);

// Rotates a 2D vector by an angle without changing its magnitude. By convention, the positive x-axis has an angle of 0. Angles increase in the clockwise direction.
static inline Vec2 vec2_rotate(const Vec2 v, double angle);

// Returns the angle between two vectors. The angle returned are signed.
static inline double vec2_angle_between(const Vec2 a, const Vec2 b);

// Calculates new x and y components that are proportionally the same
// distance between two vectors. The amt parameter is the amount to interpolate
// between the old vector and the new vector. 0.0 keeps all components equal to
// the old vector's, 0.5 is halfway between, and 1.0 sets all components equal
// to the new vector's.
static inline double vec2_lerp(const Vec2 a, const Vec2 b, const double amp);

*/

static inline void print_vec2(Vec2 v)
{
    printf("vec2: x=%lf, y=%lf\n", v.x, v.y);
}




/**
 * Body is a physics body that lives in an enviroment.
 * 
 *
 */
typedef struct Body {
    // Position
    Vec2 pos;

    // Velocity
    Vec2 vel;

    // Acceleration
    Vec2 acc;

    // Mass
    double mass;

    double max_speed;

    Vec2 *shapes;
} Body;

extern Body *body_alloc();
extern void body_init(Body *body, Vec2 pos, double mass);
extern Body *body_new(Vec2 pos, float mass);
extern void body_apply_force(Body *body, const Vec2 force);
extern void body_apply_gravity(Body *body, const Vec2 gravity);
extern void body_update(Body *body, const double dt);
extern Vec2 body_momentum(Body *body);

#endif // End PHYSICS2D_H



#define PHYSICS2D_IMPLEMENTATION
#ifdef PHYSICS2D_IMPLEMENTATION


#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

extern Body *body_alloc()
{
    return (Body *) malloc(sizeof(Body));
}

void body_init(Body *body, Vec2 pos, double mass)
{
    body->pos = pos;
    body->vel = vec2zero;
    body->acc = vec2zero;
    body->mass = mass;
    body->max_speed = -1;

    arrput(body->shapes, vec2(1,1));
}

Body *body_new(Vec2 pos, float mass)
{
    // Can't have zero mass body
    if (mass==0)
        return NULL;

    Body *body = body_alloc();
    if (!body)
        return NULL;

    body_init(body, pos, mass);

    return body;
}

void body_apply_force(Body *body, const Vec2 force)
{
    // Newtons law
    // ∑F = ma or a = F / m
    Vec2 acc = vec2_div(force, body->mass);
    body->acc = vec2_add(body->acc, acc);
}

void body_apply_gravity(Body *body, const Vec2 gravity)
{
    body->acc = vec2_add(body->acc, gravity);
}

void body_update(Body *body, const double dt)
{
    // Mutiply by delta time
    Vec2 acc = vec2_mult(body->acc, dt);

    body->vel = vec2_add(body->vel, acc);
    if (body->max_speed >= 0) {
        body->vel = vec2_limit(body->vel, body->max_speed);
    }

    body->pos = vec2_add(body->pos, body->vel);
    body->acc = vec2zero;
}

Vec2 body_momentum(Body *body)
{
    return vec2_mult(body->vel, body->mass);
}

// friction returns a force. 
// f = -1 * u * N v
// 
// n normal force magnature
// coff coffiefient of friction
Vec2 friction(Vec2 vel, double coff, double n)
{
    vel = vec2_normalize(vel);
    return vec2_mult(vel, -coff*n);
}


/**
 * Perlin Noise
 *
 */
/* #define STB_PERLIN_IMPLEMENTATION */
/* #include "stb_perlin.h" */

void noise_seed(int seed)
{
    /* stb_perlin_noise3_seed(x, y, z, 0, 0, 0, seed); */
}
double noise(double x);
double noise2(double x, double y);
double noise3(double x, double y, double z)
{
    /* return stb_perlin_noise3(x, y, z, 0, 0, 0); */
    return 0;
}

void destroy_noise();

/**********************************************
 *
 * Shapes
 *
 */



/**
 * Point
 * 
 */
typedef struct Point {
    Vec2 pos;
} Point;

/**
 * Line
 * 
 */
typedef struct Line {
    Vec2 v1;
    Vec2 v2;
} Line;


/**
 * Circle
 * 
 */
typedef struct Circle {
    Vec2 center;
    double radius;
} Circle;

/**
 * Ellipse
 * 
 */
typedef struct Ellipse {
    Vec2 center;
    double radius_x;
    double radius_y;
} Ellipse;

/**
 * Triangle
 * 
 */
typedef struct Triangle {
    Vec2 v1;
    Vec2 v2;
    Vec2 v3;
} Triangle;

/**
 * Poly
 * 
 */
typedef struct Poly {
    Vec2 *v;
} Poly;

/**
 * Rectangle
 * 
 */
typedef struct Rect {
    Vec2 pos;
    double width;
    double height;
} Rect;



double point_area(Point p) { return 1; }
bool point_collide(Point p1, Point p2) { return vec2_equal(p1.pos, p2.pos); }
bool point_collide_line(Point p, Line l);
bool point_collide_circle(Point p, Circle c);
bool point_collide_ellipse(Point p, Ellipse e);
bool point_collide_triangle(Point p, Triangle t);
bool point_collide_rect(Point p, Rect r);
bool point_collide_poly(Point p, Poly poly);

double line_area(Line l) { return 0; }
bool line_collide(Line l1, Line l2);
bool line_collide_circle(Line l, Circle c);
bool line_collide_ellipse(Line l, Ellipse e);
bool line_collide_triangle(Line l, Triangle t);
bool line_collide_rect(Line l, Rect r);
bool line_collide_poly(Line l, Poly poly);

double circle_area(Circle p) {
    return M_PI * p.radius  * p.radius;
}

bool circle_collide(Circle c1, Circle c2);
bool circle_collide_line(Circle c, Line l);
bool circle_collide_point(Circle c, Point p);
bool circle_collide_ellipse(Circle p, Ellipse e);
bool circle_collide_triangle(Circle p, Triangle t);
bool circle_collide_rect(Circle p, Rect r);
bool circle_collide_poly(Circle p, Poly poly);

typedef enum ShapeType {
    POINT,
    LINE,
    CIRCLE,
    ELLIPSE,
    RECT,
    TRIANGLE,
    POLY,
} ShapeType;

typedef struct Shape {
    ShapeType type;
    union {
        Point point;
        Line line;
        Circle circle;
        Ellipse ellipse;
        Rect rect;
        Triangle triangle;
        Poly poly;
    };
} Shape;

bool shape_collide(Shape s1, Shape s2);

double shape_area(Shape s) {
    switch (s.type) {
        case POINT: return point_area(s.point); break;
        case LINE: return line_area(s.line); break;
        case CIRCLE: return circle_area(s.circle); break;
        case ELLIPSE: return point_area(s.point); break;
        case TRIANGLE: return point_area(s.point); break;
        case RECT: return point_area(s.point); break;
        case POLY: return point_area(s.point); break;
    }
    return false;
}

Vec2 shape_center(Shape s1, Shape s2);

static inline Shape rect(const double x, const double y, const double width, const double height)
{
    Rect r= {
        .pos = vec2(x, y),
        .width = width,
        .height = height,
    };
    Shape s = {
        .type = RECT,
        .rect = r,
    };
    return s;
}

#endif // End PHYSICS2D_IMPLEMENTATION

