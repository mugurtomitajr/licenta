//
//  calculations.cpp
//  practice
//

#include "calculations.hpp"

glm::vec3 calc::Lerp(glm::vec3 start, glm::vec3 finish, float percent) {
    return start + ((finish - start) * percent);
}

GLfloat calc::DistancePointSquare2DSquared(glm::vec2 point, glm::vec2 center, GLfloat sideLength) {
    glm::vec2 dist = glm::vec2(0.0f, 0.0f);
    dist.x = fmax(abs(point.x - center.x) - sideLength / 2.0f, 0.0f);
    dist.y = fmax(abs(point.y - center.y) - sideLength / 2.0f, 0.0f);
    return dist.x * dist.x + dist.y * dist.y;
}
