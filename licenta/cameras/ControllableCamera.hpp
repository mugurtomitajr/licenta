//
//  ControllableCamera.hpp
//  practice
//

#ifndef ControllableCamera_hpp
#define ControllableCamera_hpp

#include <cstdio>
#include "Camera.hpp"

class ControllableCamera : public Camera {
public:
    ControllableCamera();
    ControllableCamera(GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch);
    ~ControllableCamera();
    
    void Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray);
private:
    bool _checkMouseChange(glm::vec2 p_deltaMouse);
    void _checkKeysPressed(const double &dt, bool *p_keyPressedArray);
};

#endif /* ControllableCamera_hpp */
