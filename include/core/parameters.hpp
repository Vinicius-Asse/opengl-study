#pragma once

#include<glm/vec3.hpp>

class Parameters
{
private:
    /* data */
public:
    Parameters();
    ~Parameters();
    
    glm::vec3 worldBounds;
    glm::vec3 noiseDisplacement;
    int   pointsCount;
    float noiseScale;
    float surfaceLevel;
    float surfaceResolution;
    float smoothIntersect;
    float simulationSpeed;
    float gravityForce;
    bool  smooth;
    bool  linearInterp;
    bool  useGPU;

};
