#include "Cube.hpp"

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