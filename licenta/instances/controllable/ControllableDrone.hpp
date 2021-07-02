//
//  ControllableDrone.hpp
//  practice
//

#ifndef ControllableDrone_hpp
#define ControllableDrone_hpp

#include <cstdio>
#include "Instance.hpp"
#include "ControllableDronePropeller.hpp"

class ControllableDrone : public Instance {
public:
    ControllableDrone();
    ControllableDrone(Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    
    const char* LoadCustomModelFilepath();
    glm::vec3 LoadCustomModelScale();
    void Start();
    void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    
    void LoadOtherInstances(AssetManager *p_assetManager, RuntimeQueueManager *p_runtimeQueueManager);
    
    glm::vec3 FollowOffset();
    GLfloat YRotationFollowOffset();
private:
    glm::vec3 _front;
    glm::vec3 _right;
    glm::vec3 _up;
    GLfloat _yaw;
    GLfloat _rotationSpeed;
    
    void _checkKeysPressed(double dt, bool *p_keyPressedArray);
    void _recalculateVectors();
};

#endif /* ControllableDrone_hpp */
