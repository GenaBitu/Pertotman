/**
 * @file Space.hpp
 * File with Space
 * @author GenaBitu
 **/

#ifndef SPACE_HPP
#define SPACE_HPP
#include "Libs.hpp"
class Level;
class RendObj;

class Space: public RendObj
{
    public:
     Space* up;
     Space* down;
     Space* left;
     Space* right;
     int dist;
     Space(GLfloat xIn, GLfloat yIn, GLTexture srcTextures);
     void neighbours(Level* thisLevel);
     void compute(GLint ThisDist, char from = 'a');
};

#endif //SPACE_HPP
