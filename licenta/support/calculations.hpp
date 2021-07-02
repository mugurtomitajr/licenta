//
//  calculations.hpp
//  practice
//

#ifndef calculations_hpp
#define calculations_hpp

#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace calc {

glm::vec3 Lerp(glm::vec3 start, glm::vec3 finish, float percent);

GLfloat DistancePointSquare2DSquared(glm::vec2 point, glm::vec2 center, GLfloat sideLength);

}
#endif /* calculations_hpp */
