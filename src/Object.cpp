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

vector<sf::Vector3i> Object::GetTriangles() 
{
    //return triangles stored in triangles vector 
    return triangles; 
} 

vector<Vector3f> Object::GetWorldPoints()
{
    //calculate the position of all the vertices in world units and return array of these positions
    //setup emtpy array to hold the positions of points

    vector<Vector3f> worldPoints;

    /*
        convert position from local units to world units for each vertex in points array
        and push into the worldPoints array;
    */

    for(Vector3f point : points)
    {
        /*  convert the point from vector3f to matrix so we can operate on it in matrix multiplication 
            and addition
            coord is matrix representation of a point in format
            | x |
            | y |
            | z |

        */

        Matrix <float, 3, 1> coord;
        coord << point.x, point.y, point.z;

        /*
            apply the scale and rotation by multiplying the coord matrix with rotation and scaling
            matrix. First we multiply these matrices amongst themselves in order of
            scaling -> rotation-Z -> rotation-Y -> rotation-X
            the apply translate at last and set the point.x , point.y , point.z with the matrix 
            elemnts 00, 10, 20. push the point into vector container
        */

        // Eigen::MatrixXf transformed = (m_scale * m_rotZ * m_rotY * m_rotX) * coord;
        // transformed = transformed + m_translate;
        // point.x = transformed(0, 0);
        // point.y = transformed(1, 0);
        // point.z = transformed(2, 0);
        

        coord = (m_scale * m_rotZ * m_rotY * m_rotX) * coord;
        coord = coord + m_translate;
        point.x = coord(0, 0);
        point.y = coord(1, 0);
        point.z = coord(2, 0);

        worldPoints.push_back(point);
    }

    

    return worldPoints;
}
