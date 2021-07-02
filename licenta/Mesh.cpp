//
//  Mesh.cpp
//  practice
//

#include "Mesh.hpp"

Mesh::Mesh() {
    this -> _vao = 0;
    this -> _vbo = 0;
    this -> _ibo = 0;
    this -> _numOfIndices = 0;
    this -> _diffuseMap = nullptr;
    this -> _propertiesMaterial = nullptr;
}

Mesh::~Mesh() {
    this -> _clear();
}

bool Mesh::Load(GLfloat *p_vertices, unsigned int p_numOfVertices, unsigned int *p_indices, unsigned int p_numOfIndices){
    this -> _numOfIndices = p_numOfIndices;

    glGenVertexArrays(1, &this -> _vao);
    glBindVertexArray(this -> _vao);

    glGenBuffers(1, &this -> _ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(p_indices[0]) * this -> _numOfIndices, p_indices, GL_STATIC_DRAW);

    glGenBuffers(1, &this -> _vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this -> _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p_vertices[0]) * p_numOfVertices, p_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(p_vertices[0]) * 8, 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(p_vertices[0]) * 8, (void*) (sizeof(p_vertices[0]) * 3));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(p_vertices[0]) * 8, (void*) (sizeof(p_vertices[0]) * 5));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    return true;
}

void Mesh::Render(double dt, double inter) {
    glBindVertexArray(this -> _vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> _ibo);
    glDrawElements(GL_TRIANGLES, this -> _numOfIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Texture::Remove();
}

void Mesh::Remove() {
    
}

void Mesh::DiffuseMap(Texture *p_diffuseMap) { this -> _diffuseMap = p_diffuseMap; }

Texture* Mesh::DiffuseMap() { return this -> _diffuseMap; }

void Mesh::PropertiesMaterial(LightingMaterial *p_propertiesMaterial) { this -> _propertiesMaterial = p_propertiesMaterial; }
LightingMaterial* Mesh::PropertiesMaterial() { return this -> _propertiesMaterial; }

void Mesh::_clear() {
    if ( this -> _ibo != 0 ) {
        glDeleteBuffers(1, &this -> _ibo);
        this -> _ibo = 0;
    }

    if ( this -> _vbo != 0 ) {
        glDeleteBuffers(1, &this -> _vbo);
        this -> _vbo = 0;
    }

    if ( this -> _vao != 0 ) {
        glDeleteVertexArrays(1, &this -> _vao);
        this -> _vao = 0;
    }

    this -> _numOfIndices = 0;
    this -> _diffuseMap = nullptr;
    this -> _propertiesMaterial = nullptr;
}

void Mesh::_copy(const Mesh &p_that) {
    
}
        
