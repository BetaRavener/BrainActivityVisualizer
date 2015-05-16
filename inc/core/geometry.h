// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/common.hpp>
#include <vector>

namespace geom2d
{
    typedef std::vector<glm::vec2> Intersections;

    /**
     * @brief The Line class is a 2D representation of line.
     */
    class Line
    {
    public:
        Line(const glm::vec2& begin, const glm::vec2& vec);

        /**
         * @brief Getter.
         * @return The beggining of the line.
         */
        glm::vec2 begin() const;

        /**
         * @brief Getter.
         * @return The end of the line.
         */
        glm::vec2 end() const;

        /**
         * @brief Getter.
         * @return The vector from begin to end of the line.
         */
        glm::vec2 vec() const;

        /**
         * @brief Moves the line by a vector.
         * @param vec The movement vector.
         */
        void move(const glm::vec2 &vec);

        /**
         * @brief Rotates the line by an angle.
         * @param angle The rotation angle.
         */
        void rotate(float angle);

        /**
         * @brief turnLeft Rotates the line 90 degrees counter-clockwise.
         */
        void turnLeft();

        /**
         * @brief turnRight Rotates the line 90 degrees clockwise.
         */
        void turnRight();

        enum class IntersectionMode {Line, Ray, Inf};

        /**
         * @brief Tests if this and other line intersect.
         * @param line The other line.
         * @param intersections Used to return intersections.
         * @param m1 Intersection mode for this line.
         * @param m2 Intersection mode for the other line.
         * @return True if the lines intersect.
         */
        bool intersects(const Line& line, Intersections* intersections = nullptr,
                        IntersectionMode m1 = IntersectionMode::Line,
                        IntersectionMode m2 = IntersectionMode::Line);

    private:
        glm::vec2 _begin;
        glm::vec2 _vec;
    };

    /**
     * @brief The Triangle class is a 2D representation of a triangle.
     */
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

    /**
     * @brief The Circle class is a 2D representation of a circle.
     */
    class Circle
    {
    public:
        Circle();
        Circle(const glm::vec2& c, float r);

        /**
         * @brief Getter.
         * @return Center of the circle.
         */
        glm::vec2 center();

        /**
         * @brief Setter.
         * @param c Center of the circle.
         */
        void center(const glm::vec2& c);

        /**
         * @brief Getter.
         * @return Radius of the circle.
         */
        float radius();

        /**
         * @brief Setter.
         * @param r Radius of the circle.
         */
        void radius(float r);

        /**
         * @brief Creates new circle by circumscribing a triangle.
         * @param triangle Triangle to circumscribe.
         * @return The resulting circle.
         */
        static Circle circumscribeTriangle(Triangle triangle);

    private:
        glm::vec2 _center;
        float _radius;
    };
}

#endif
