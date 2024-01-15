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
#include <stdlib.h>
#include <math.h>

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

static inline double vec2_mag(const Vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
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

static inline Vec2 vec2_set_mag(const Vec2 v, double m)
{
    return vec2_mult(vec2_normalize(v), m);
}

static inline Vec2 vec2_neg(const Vec2 v)
{
    return vec2(-v.x, -v.y);
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
// Returns the magnitude (length) of the vector squared.
static inline double vec2_mag_sq(const Vec2 v);


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
 * Rectangle
 * 
 */
typedef struct Rect {
    Vec2 pos;
    double width;
    double height;
} Rect;


static inline Rect rect(const double x, const double y, const double width, const double height)
{
     Rect r = {
        .pos = vec2(x, y),
        .width = width,
        .height = height
     };
    return r;
}

/**
 * Body is a physics body that lives in an enviroment.
 * 
 *
 */
typedef struct Body {
    Vec2 pos;
    Vec2 vel;
    Vec2 acc;
    double mass;
} Body;

extern Body *body_alloc();
extern void body_init(Body *body, Vec2 pos, double mass);
extern Body *body_new(Vec2 pos, float mass);
extern void body_apply_force(Body *body, const Vec2 force);
extern void body_apply_gravity(Body *body, const Vec2 gravity);
extern void body_update(Body *body, const double dt);

#endif // End PHYSICS2D_H



#define PHYSICS2D_IMPLEMENTATION
#ifdef PHYSICS2D_IMPLEMENTATION

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
    body->pos = vec2_add(body->pos, body->vel);

    body->acc = vec2zero;
}



#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
void noise_seed(int seed)
{
    /* stb_perlin_noise3_seed(x, y, z, 0, 0, 0, seed); */
}
double noise(double x);
double noise2(double x, double y);
double noise3(double x, double y, double z)
{
    return stb_perlin_noise3(x, y, z, 0, 0, 0);
}

void destroy_noise();

#endif // End PHYSICS2D_IMPLEMENTATION
