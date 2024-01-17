#include <raylib.h>

#include "physics2d.h"

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
