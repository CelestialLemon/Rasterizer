#include "Object/Object.hpp"
 
void Object::InitializePoints()
{
    //default object has no points;
    points.clear();
}

void Object::InitializeTriangles()
{
    //default object has no triangles;
    triangles.clear();
}

void Object::ComputeScaleMatrix()
{
    m_scale <<
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, scale.z;
}

void Object::ComputeRotationMatrices()
{
    float fac = PI / 180;
    float xInRad = rot.x * fac;
    float yInRad = rot.y * fac;
    float zInRad = rot.z * fac;

    //std::cout << "x : " << xInRad << " y : " << yInRad << " z : " << zInRad << "\n";
    
    m_rotX <<
        1, 0, 0,
        0, cos(xInRad), -sin(xInRad),
        0, sin(xInRad), cos(xInRad);

    m_rotY <<
        cos(yInRad), 0, sin(yInRad),
        0, 1, 0,
        -sin(yInRad), 0, cos(yInRad);

    m_rotZ <<
        cos(zInRad), -sin(zInRad), 0,
        sin(zInRad), cos(zInRad), 0,
        0, 0, 1;

}

void Object::ComputeTranslateMatrix()
{
    m_translate << origin.x, origin.y, origin.z;
}

Object::Object()
{
    // set orign to center of the world
    
    origin = Vector3f(0, 0, 0);
    
    //set scaling to default 1
    
    scale = Vector3f(1, 1, 1);

    //set default rotation to 0 deg on all axes

    rot = Vector3f(0, 0, 0);

    //compute the transform matrices and intialize the points and tirnalges

    ComputeScaleMatrix();
    ComputeRotationMatrices();
    ComputeTranslateMatrix();
}

void Object::SetPosition(Vector3f _origin) 
{ 
    origin = _origin; 

    //calculate new translate matrix when object changes position
    ComputeTranslateMatrix(); 
}

void Object::SetRotation(Vector3f _rot) 
{ 
    rot = _rot; 

    //calculate new rotation matrix when object changes rotation
    ComputeRotationMatrices(); 
}

void Object::SetScale(Vector3f _scale) 
{ 
    scale = _scale; 

    //calculate scaling matrix when object changes scale
    ComputeScaleMatrix(); 
}

Vector3f Object::GetPosition() { return origin; }
Vector3f Object::GetRotation() { return rot; }
Vector3f Object::GetScale() { return scale; } 
