#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include "math.h"
#define _USE_MATH_DEFINES

namespace Util{
    static std::vector<std::string> splitString(const std::string& p_sString, char p_cDelimeter){
        std::vector<std::string> result;
        std::stringstream s_stream(p_sString);
        while(s_stream.good()) {
            std::string substr;
            getline(s_stream, substr, p_cDelimeter);
            result.push_back(substr);
        }
        return result;
    }

    static int randNum(int p_iMin, int p_iMax){
        return rand()%(p_iMax-p_iMin + 1) + p_iMin;
    }

    static float randNum(float p_fMin, float p_fMax){
        return p_fMin + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(p_fMax-p_fMin)));
    } 
    
    static glm::vec3 randVector(glm::vec3 p_vMin, glm::vec3 p_vMax){
        float x = randNum(p_vMin.x, p_vMax.x);
        float y = randNum(p_vMin.y, p_vMax.y);
        float z = randNum(p_vMin.z, p_vMax.z);

        return glm::vec3(x, y, z);
    }

    static glm::vec4 randVector(glm::vec4 p_vMin, glm::vec4 p_vMax){
        float x = randNum(p_vMin.x, p_vMax.x);
        float y = randNum(p_vMin.y, p_vMax.y);
        float z = randNum(p_vMin.z, p_vMax.z);
        float w = randNum(p_vMin.w, p_vMax.w);

        return glm::vec4(x, y, z, w);
    }
};