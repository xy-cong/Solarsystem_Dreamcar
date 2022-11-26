

#include "GLcamera.hpp"
#include <iostream>
#include <cmath>

GLcamera::GLcamera(){
    std::cout << "A camera with No Parameters! " << std::endl;
}

GLcamera::GLcamera(GLfloat EYEX, GLfloat EYEY, GLfloat EYEZ, GLfloat VIEW)
{
    this->EYEX = EYEX;
    this->EYEY = EYEY;
    this->EYEZ = EYEZ; 
    this->VIEW = VIEW;
}

void GLcamera::GLRotate(GLfloat VIEW_ROTATE){
    this->VIEW += VIEW_ROTATE;
    std::cout << "VIEW: " <<  VIEW << std::endl;
    if(this->VIEW >= 180)
        this->VIEW = 180;
    if(this->VIEW <= -180)
        this->VIEW = -180;
}

void GLcamera::GLmove(GLfloat move_up_and_down, GLfloat move_right_and_left, GLfloat move_forward_and_backward)
{
    this->EYEZ += move_up_and_down;

    this->EYEX += move_forward_and_backward*sin(this->VIEW);
    this->EYEY += move_forward_and_backward*cos(-this->VIEW);

    this->EYEX += move_right_and_left*cos(this->VIEW);
    this->EYEY += move_right_and_left*sin(this->VIEW);
    // this->EYEX += move_right_and_left;
    // this->EYEY += move_forward_and_backward;
}
