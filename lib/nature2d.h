#include <raylib.h>

#define PHYSICS2D_IMPLEMENTATION
#include "physics2d.h"

typedef struct Object {

    Body body;

    Shape *colliers;

    void (*init)(struct Object *obj);

    void (*update)(struct Object *obj, double dt);

    void (*draw)(struct Object *obj);

} Object;

void object_free(Object *obj)
{
    collider_free(obj->colliers);
}

void object_update(Object *obj, double dt)
{
    body_update(&obj->body, dt);
}

bool object_detect_collition(Object *o1, Object *o2)
{
    return collider_detect_collisions(o1->body.pos, o1->colliers,o2->body.pos, o2->colliers);
}

void draw_shape(Vec2 start, Shape shape, Color color);

// Default object_draw
void object_draw(Object *obj)
{
    Color gray = { 130, 130, 130, 200 };
    for (int i=0; i<arrlen(obj->colliers); i++) {
        draw_shape(obj->body.pos, obj->colliers[i], gray);
    }
}

Object basic_object = {
    .update = object_update,
    .draw = object_draw,
};

typedef struct World {
    int width, height;

    Object *objects;

} World;

World world_new(int width, int height)
{
    return (World){
        .width = width,
        .height = height,
        .objects = NULL,
    };
}

void world_free(World *world)
{
    if (world==NULL) return;

    int n = arrlen(world->objects);
    for (int i=0; i<n; i++) {
        Object obj = world->objects[i];
        object_free(&obj);
    }
    free(world->objects);
}

void world_add_object(World *world, Object obj)
{
    if (world==NULL) return;
    arrput(world->objects, obj);
}

void world_init(World *world)
{
    if (world==NULL) return;

    int n = arrlen(world->objects);
    for (int i=0; i<n; i++) {
        Object obj = world->objects[i];
        if (obj.init != NULL ) {
            obj.init(&obj);
        }
    }
}

void world_update(World *world, double dt)
{
    if (world==NULL) return;

    int n = arrlen(world->objects);
    for (int i=0; i<n; i++) {
        Object obj = world->objects[i];
        if (obj.update != NULL ) {
            obj.update(&obj, dt);
        }
    }
}

void world_draw(World *world)
{
    if (world==NULL) return;

    int n = arrlen(world->objects);
    for (int i=0; i<n; i++) {
        Object obj = world->objects[i];
        if (obj.draw != NULL ) {
            obj.draw(&obj);
        }
    }
}



Vector2 vector2(Vec2 v)
{
    return (Vector2){
        .x = (float) v.x,
        .y = (float) v.y,
    };
}

void draw_point(Point point, Color color)
{
    DrawPixel(point.x, point.y, color);
}

void draw_line(Line line, Color color)
{
    DrawLine(line.v1.x, line.v1.y, line.v2.x, line.v2.y, color);
}

void draw_circle(Circle circle, Color color)
{
    DrawCircle(circle.center.x, circle.center.y, circle.radius, color);
}

void draw_rect(Rect rect, Color color)
{
    DrawRectangle(rect.pos.x, rect.pos.y, rect.width, rect.height, color);
}

void draw_poly(Poly poly, Color color)
{
}

void draw_shape(Vec2 start, Shape shape, Color color)
{
    Shape s = shape_offset(start, shape);
    switch (shape.type) {
        case POINT: draw_point(s.point, color); break;
        case LINE: draw_line(s.line, color); break;
        case CIRCLE: draw_circle(s.circle, color); break;
        case TRIANGLE: break;
        case RECT: draw_rect(s.rect, color); break;
        case POLY: break;
    }
}
