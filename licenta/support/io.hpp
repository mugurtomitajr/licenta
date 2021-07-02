//
//  io.hpp
//  practice
//

#ifndef io_hpp
#define io_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace io {

glm::vec3 MovementDirectionFromKeyboard(bool *p_keyPressedArray);
int NumberKeyPressed(bool *p_keyPressedArray);

std::string StringFromFile(const char *p_filepath);

std::string FilenameFromFilepath(const char* p_filepath);
std::string RootpathFromFilepath(const char* p_filepath);

}

#endif /* io_hpp */
