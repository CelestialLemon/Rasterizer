#include "Object/Cube.hpp"

void Cube::InitializePoints()
{
    /*
        Since a cube has 8 points we initilize the 8 vertices when constructor is called
        The cube has initial dimmensions as 2 x 2 x 2
    */
    points.push_back(Vector3f(1, 1, 1));
    points.push_back(Vector3f(-1, 1, 1));
    points.push_back(Vector3f(-1, -1, 1));
    points.push_back(Vector3f(1, -1, 1));

    points.push_back(Vector3f(1, 1, -1));
    points.push_back(Vector3f(-1, 1, -1));
    points.push_back(Vector3f(-1, -1, -1));
    points.push_back(Vector3f(1, -1, -1));
}

void Cube::InitializeTriangles()
{
    /*
        This initilizes the points the the triangles. Values set manually
    */
    //back face
    triangles.push_back(sf::Vector3i(0, 1, 2));
    triangles.push_back(sf::Vector3i(0, 3, 2));
    //front face
    triangles.push_back(sf::Vector3i(4, 7, 6));
    triangles.push_back(sf::Vector3i(4, 5, 6));
    //left face
    triangles.push_back(sf::Vector3i(1, 2, 6));
    triangles.push_back(sf::Vector3i(1, 5, 6));
    //right face
    triangles.push_back(sf::Vector3i(0, 4, 7));
    triangles.push_back(sf::Vector3i(0, 3, 7));
    //top face
    triangles.push_back(sf::Vector3i(0, 1, 5));
    triangles.push_back(sf::Vector3i(0, 4, 5));
    //bottom face
    triangles.push_back(sf::Vector3i(3, 2, 6));
    triangles.push_back(sf::Vector3i(3, 7, 6));
}



Cube::Cube()
{
    InitializePoints();
    InitializeTriangles();
}



vector<sf::Vector3i> Cube::GetTriangles() 
{
    //return triangles stored in triangles vector 
    return triangles; 
} 

vector<Vector3f> Cube::GetWorldPoints()
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