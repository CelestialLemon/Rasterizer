#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "../Object.hpp"

#define PI 3.14159265f

using Eigen::Matrix;
using std::vector;
using sf::Vector3f;


////////////////////////    DETAILS    ///////////////////////////////
/*
    origin is the point at the center of the cube i.e center of geometry or
    center of mass if the object has uniform density

    The cube has initial dimmensions as length = 2, breadth = 2, height = 2
    The scale represents how the cube is scaled along different local axes.
    scale.x represents scaling along local x-axis and similar for scale.y and scale.z

    The cube has initial rotations as x-rot = 0 deg, y-rot = 0 deg and  z-rot = 0 deg
    The rot represents how the cube is rotated along different local axes.
    rot.x represents scaling along local x-axis and similar for rot.y and rot.z

    the array points is used to store the vertices of the shape.
    Since a cube has 8 vertices and this number is fixed for all cubes we initialize the array 
    directly when a new cube constructor is called

    the array of triangles contains triangles. Each element is a vector3i where x represents the
    index of first point of triangle in points array, y represents index of second point of triangle in the points array
    and z represent the index of third point;

    m_scale is the scaling matrix
    m_rotX is matrix used for rotating a point about x-axis, and similarly m_rotY and m_rotZ are used for 
    rotation about y and z axes respectively

    m_translate is the translation matrix used to translate a point
*/


class Cube : public Object
{
    
    void InitializePoints();
    void InitializeTriangles();

    public:
    Cube();
};