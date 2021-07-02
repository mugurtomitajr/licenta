//
//  ControllableDronePropeller.hpp
//  practice
//

#ifndef ControllableDronePropeller_hpp
#define ControllableDronePropeller_hpp

#include <cstdio>

#include <glm/glm.hpp>

#include "Instance.hpp"

class ControllableDronePropeller : public Instance {
public:
    ControllableDronePropeller();
    ControllableDronePropeller(bool p_isLeft, Instance *p_parent, glm::vec3 p_position, glm::vec3 p_rotation, glm::vec3 p_scale);
    
    const char* LoadCustomModelFilepath();
    glm::vec3 LoadCustomModelPosition();
    glm::vec3 LoadCustomModelScale();
    
    void Start();
    void Update(double dt, const glm::vec2 &p_mouseDelta, bool* p_keyPressedArray);
    
private:
    bool _isLeft;
};

#endif /* ControllableDronePropeller_hpp */
