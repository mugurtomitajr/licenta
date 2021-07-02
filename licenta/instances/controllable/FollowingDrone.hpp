//
//  FollowingDrone.hpp
//  practice
//

#ifndef FollowingDrone_hpp
#define FollowingDrone_hpp

#include <cstdio>
#include "Instance.hpp"
#include "ControllableDronePropeller.hpp"

class FollowingDrone : public Instance {
public:
    FollowingDrone();
    FollowingDrone(int p_nb, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    
    const char* LoadCustomModelFilepath();
    glm::vec3 LoadCustomModelScale();
    void Start();
    void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    
    void LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager);
    
    glm::vec3 FollowOffset();
    GLfloat YRotationFollowOffset();
private:
    int _nb;
    glm::vec3 _front;
    glm::vec3 _right;
    glm::vec3 _up;
    GLfloat _yaw;
    GLfloat _rotationSpeed;
    
    void _checkKeysPressed(double dt, bool *p_keyPressedArray);
    void _recalculateVectors();
};

#endif /* FollowingDrone_hpp */
