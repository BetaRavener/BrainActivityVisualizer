// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "geometry.h"
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stdexcept>

using namespace geom2d;

Line::Line(const glm::vec2& begin, const glm::vec2& vec) :
    _begin(begin),
    _vec(vec)
{

}

glm::vec2 Line::begin() const
{
    return _begin;
}

glm::vec2 Line::end() const
{
    return _begin + _vec;
}

glm::vec2 Line::vec() const
{
    return _vec;
}

void Line::move(const glm::vec2& vec)
{
    _begin += vec;
}

void Line::rotate(float angle)
{
    _vec = glm::rotate(_vec, angle);
}

void Line::turnLeft()
{
    _vec = glm::rotate(_vec, glm::half_pi<float>());
}

void Line::turnRight()
{
    _vec = glm::rotate(_vec, -glm::half_pi<float>());
}

bool Line::intersects(const Line& line, Intersections* intersections,
                       IntersectionMode m1, IntersectionMode m2)
{
    glm::vec2 p1 = begin();
    glm::vec2 vecA = vec();

    glm::vec2 p2 = line.begin();
    glm::vec2 vecB = line.vec();

    float denominator = vecB.y * vecA.x - vecB.x * vecA.y;

    if (glm::epsilonEqual(denominator, 0.0f, glm::epsilon<float>()))
    {
        // Lines parallel
        return false;
    }

    glm::vec2 diff = p1 - p2;
    float t = (vecB.x * diff.y - vecB.y * diff.x) / denominator;
    float u = (vecA.x * diff.y - vecA.y * diff.x) / denominator;

    // Test if intersection belongs to geometry
    bool belongs1 = false, belongs2 = false;

    switch(m1)
    {
    case IntersectionMode::Inf:
        belongs1 = true;
        break;
    case IntersectionMode::Ray:
        belongs1 = t >= 0.0;
        break;
    case IntersectionMode::Line:
        belongs1 = (t >= 0.0 && t <= 1.0);
        break;
    }

    switch(m2)
    {
    case IntersectionMode::Inf:
        belongs2 = true;
        break;
    case IntersectionMode::Ray:
        belongs2 = u >= 0.0;
        break;
    case IntersectionMode::Line:
        belongs2 = (u >= 0.0 && u <= 1.0);
        break;
    }

    if (belongs1 && belongs2)
    {
        if (intersections != nullptr)
            intersections->push_back(begin() + vec() * t);

        return true;
    }

    return false;
}

Triangle::Triangle(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) :
    _vertices({a,b,c})
{
}

Triangle::Triangle(const Triangle& other) :
    _vertices(other._vertices)
{

}

glm::vec2 Triangle::a()
{
    return _vertices[0];
}

glm::vec2 Triangle::b()
{
    return _vertices[1];
}

glm::vec2 Triangle::c()
{
    return _vertices[2];
}

Circle::Circle() :
    _center(glm::vec2(0.0f, 0.0f)),
    _radius(0.0f)
{
}

Circle::Circle(const glm::vec2& c, float r) :
    _center(c),
    _radius(r)
{
}

glm::vec2 Circle::center()
{
    return _center;
}

void Circle::center(const glm::vec2& c)
{
    _center = c;
}

float Circle::radius()
{
    return _radius;
}

void Circle::radius(float r)
{
    _radius = r;
}

Circle Circle::circumscribeTriangle(Triangle triangle)
{
    Line side1(triangle.a(), triangle.c() - triangle.a());
    Line side2(triangle.b(), triangle.c() - triangle.b());

    // Move into center of sides
    side1.move(side1.vec() / 2.0f);
    side2.move(side2.vec() / 2.0f);

    // Rotate to perpedicular direction
    side1.turnLeft();
    side2.turnLeft();

    // Find intersection considering lines as infinite
    Intersections intersections;
    if (side1.intersects(side2, &intersections, Line::IntersectionMode::Inf, Line::IntersectionMode::Inf))
    {
        glm::vec2 center = intersections.front();
        float radius = glm::length(center - triangle.a());
        return Circle(center, radius);
    }
    else
    {
        throw new std::runtime_error("Circumscribed circle doesn't exist. (All points in triangle linear?)");
    }
}
