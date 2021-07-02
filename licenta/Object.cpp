//
//  Object.cpp
//  practice
//

#include "Object.hpp"

Object::Object() {
    
}

Object::Object(const Object &p_that) {
    if (this != &p_that) {
        this -> _clear();
        this -> _copy(p_that);
    }
}

Object::~Object() {
    this -> _clear();
}

Object& Object::operator=(const Object &p_that) {
    if (this != &p_that) {
        this -> _clear();
        this -> _copy(p_that);
    }
    return *this;
}

void Object::Render(const double &dt, const double &inter) {
    
}

void Object::Update(const double &dt) {
    
}

void Object::_clear() {
    
}

void Object::_copy(const Object &p_that) {
    this -> _position = p_that._position;
}
		
