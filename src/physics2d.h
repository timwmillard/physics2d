#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static inline double map(const double value, const double start1, const double stop1, const double start2, const double stop2)
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

#endif // End PHYSICS2D_H


extern Body *body_alloc();
extern void body_init(Body *body, Vec2 pos, double mass);
extern Body *body_new(Vec2 pos, float mass);
extern void body_apply_force(Body *body, const Vec2 force);
extern void body_apply_gravity(Body *body, const Vec2 gravity);
extern void body_update(Body *body, const double dt);


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

void body_apply_force(Body *body, const Vec2 force) {
    // Newtons law
    // ∑F = ma or a = F / m
    Vec2 acc = vec2_div(force, body->mass);
    body->acc = vec2_add(body->acc, acc);
}

void body_apply_gravity(Body *body, const Vec2 gravity) {
    body->acc = vec2_add(body->acc, gravity);
}

void body_update(Body *body, const double dt) {
    // Mutiply by delta time
    Vec2 acc = vec2_mult(body->acc, dt);

    body->vel = vec2_add(body->vel, acc);
    body->pos = vec2_add(body->pos, body->vel);

    body->acc = vec2zero;
}

#endif // End PHYSICS2D_IMPLEMENTATION
