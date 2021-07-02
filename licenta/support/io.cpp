//
//  io.cpp
//  practice
//

#include "io.hpp"

glm::vec3 io::MovementDirectionFromKeyboard(bool *p_keyPressedArray) {
    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
    if(p_keyPressedArray[GLFW_KEY_W]) {
        direction.z += 1;
    }
    
    if(p_keyPressedArray[GLFW_KEY_S]) {
        direction.z -= 1;
    }
    
    if(p_keyPressedArray[GLFW_KEY_A]) {
        direction.x -= 1;
    }
    
    if(p_keyPressedArray[GLFW_KEY_D]) {
        direction.x += 1;
    }
    
    if(p_keyPressedArray[GLFW_KEY_SPACE]) {
        direction.y += 1;
    }
    
    if(p_keyPressedArray[GLFW_KEY_LEFT_CONTROL]) {
        direction.y -= 1;
    }
    return glm::normalize(direction);
}

int io::NumberKeyPressed(bool *p_keyPressedArray) {
    if(p_keyPressedArray[GLFW_KEY_0]) {
        return 0;
    } else if(p_keyPressedArray[GLFW_KEY_1]) {
        return 1;
    } else if(p_keyPressedArray[GLFW_KEY_2]) {
        return 2;
    } else if(p_keyPressedArray[GLFW_KEY_3]) {
        return 3;
    } else if(p_keyPressedArray[GLFW_KEY_4]) {
        return 4;
    } else if(p_keyPressedArray[GLFW_KEY_5]) {
        return 5;
    } else if(p_keyPressedArray[GLFW_KEY_6]) {
        return 6;
    } else if(p_keyPressedArray[GLFW_KEY_7]) {
        return 7;
    } else if(p_keyPressedArray[GLFW_KEY_8]) {
        return 8;
    } else if(p_keyPressedArray[GLFW_KEY_9]) {
        return 9;
    }
    return -1;
}

std::string io::StringFromFile(const char *p_filepath) {
    std::string content;
    std::ifstream fileStream(p_filepath, std::ios::in);

    if (!fileStream.is_open()) {
        fprintf(stdout, "Failed to read %s! File doesn't exist...\n", p_filepath);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

std::string io::FilenameFromFilepath(const char *p_filepath) {
    std::string filepath(p_filepath);
    long int idx = 0;
    idx = filepath.find_last_of("/");
    if( idx >= 0 ) {
        filepath = filepath.substr(idx + 1);
    }
    
    idx = filepath.find_last_of("\\");
    if( idx >= 0 ) {
        filepath = filepath.substr(idx + 1);
    }
    return filepath;
}

std::string io::RootpathFromFilepath(const char *p_filepath) {
    std::string filepath(p_filepath);
    bool found = false;
    long int idx = 0;
    idx = filepath.find_last_of("/");
    if(idx >= 0) {
        found = true;
        filepath = filepath.substr(0, idx + 1);
    }
    
    idx = filepath.find_last_of("\\");
    if( idx >= 0 ) {
        found = true;
        filepath = filepath.substr(0, idx + 1);
    }
    if( !found ) {
        return "";
    }
    return filepath;
}


