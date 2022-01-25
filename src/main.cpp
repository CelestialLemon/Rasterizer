#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>

#include "Object/Cube.hpp"
#include "Object/Camera.hpp"

unsigned int RES_X = 500;
unsigned int RES_Y = 500;

void RenderCube(sf::RenderWindow& window)
{
    Camera cam;
    cam.SetResolution(RES_X, RES_Y);
    cam.SetPosition(Vector3f(0, 0, 1.5));
    
    Cube cube;
    cube.SetPosition(Vector3f(0, 0, 6));
    cube.SetRotation(Vector3f(0, 0, 0));
    cube.SetScale(Vector3f(2, 2, 2));

    vector<Vector3f> points = cube.GetWorldPoints();
    vector<sf::Vector3i> triangles = cube.GetTriangles();

    for(auto triangle : triangles)
    {
        Vector2f pointA = cam.WorldToScreenPoint(points[triangle.x]);
        Vector2f pointB = cam.WorldToScreenPoint(points[triangle.y]);
        Vector2f pointC = cam.WorldToScreenPoint(points[triangle.z]);

        sf::Vertex lineAB[] = {
            sf::Vertex(pointA),
            sf::Vertex(pointB)
        };

        sf::Vertex lineBC[] = {
            sf::Vertex(pointB),
            sf::Vertex(pointC)
        };

        sf::Vertex lineCA[] = {
            sf::Vertex(pointC),
            sf::Vertex(pointA)
        };

        window.draw(lineAB, 2, sf::Lines);
        window.draw(lineBC, 2, sf::Lines);
        window.draw(lineCA, 2, sf::Lines);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Rasterizer");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        RenderCube(window);
        window.display();
    }

    return 0;
}