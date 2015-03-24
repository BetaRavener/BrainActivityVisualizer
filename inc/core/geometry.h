#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/common.hpp>
#include <vector>

namespace geom2d
{
    typedef std::vector<glm::vec2> Intersections;

    class Line
    {
    public:
        Line(const glm::vec2& begin, const glm::vec2& vec);

        glm::vec2 begin() const;
        glm::vec2 end() const;
        glm::vec2 vec() const;

        void move(const glm::vec2 &vec);
        void rotate(float angle);
        void turnLeft();
        void turnRight();

        enum class IntersectionMode {Line, Ray, Inf};
        bool intersects(const Line& line, Intersections* intersections = nullptr,
                        IntersectionMode m1 = IntersectionMode::Line,
                        IntersectionMode m2 = IntersectionMode::Line);

    private:
        glm::vec2 _begin;
        glm::vec2 _vec;
    };

    class Triangle
    {
    public:
        Triangle(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
        Triangle(const Triangle& other);

        glm::vec2 a();
        glm::vec2 b();
        glm::vec2 c();

    private:
        glm::vec2 _vertices[3];
    };

    class Circle
    {
    public:
        Circle();
        Circle(const glm::vec2& c, float r);

        glm::vec2 center();
        void center(const glm::vec2& c);

        float radius();
        void radius(float r);

        static Circle circumscribeTriangle(Triangle triangle);

    private:
        glm::vec2 _center;
        float _radius;
    };
}

#endif
