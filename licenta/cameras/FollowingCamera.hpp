//
//  FollowingCamera.hpp
//  practice
//

#ifndef FollowingCamera_hpp
#define FollowingCamera_hpp

#include <cstdio>

#include "Camera.hpp"
#include "Instance.hpp"
#include "calculations.hpp"

class FollowingCamera : public Camera {
public:
    FollowingCamera();
    FollowingCamera(Instance* p_target, GLfloat p_verticalFov, GLfloat p_displayRatio, glm::vec3 p_position, glm::vec3 p_up, GLfloat p_yaw, GLfloat p_pitch);
    ~FollowingCamera();
    void Start();
    void Update(const double &dt, glm::vec2 p_deltaMouse, bool *p_keyPressedArray);
    void Stop();
private:
    Instance *_target;
    bool _checkMouseChange(glm::vec2 p_deltaMouse, GLfloat yRotationFollowOffset);
    void _checkKeysPressed(const double &dt, bool *p_keyPressedArray);
};

#endif /* FollowingCamera_hpp */
