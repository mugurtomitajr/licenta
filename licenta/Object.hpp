//
//  Object.hpp
//  practice
//

#ifndef Object_hpp
#define Object_hpp

#include <cstdio>
#include <glm/vec3.hpp>

class Object {
public:
    Object();
    Object(const Object &p_that);
    ~Object();
    
    Object &operator=(const Object &p_that);
    
    void Render(const double &dt, const double &inter);
    void Update(const double &dt);
    
private:
    Object* _parent = nullptr;
    glm::vec3 _position = glm::vec3();
    
    virtual void _copy(const Object &p_that);
    virtual void _clear();
};

#endif /* Object_hpp */
