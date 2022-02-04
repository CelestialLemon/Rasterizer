#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>

#include "Object/Cube/Cube.hpp"
#include "Object/Camera/Camera.hpp"

unsigned int RES_X = 1280;
unsigned int RES_Y = 720;

void HandleInput(Camera& cam)
{
    float moveSpeed = 0.01f;
    float rotSpeed = 0.5f;

    Vector3f pos = cam.GetPosition();
    Vector3f rot = cam.GetRotation();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        pos.x -= moveSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        pos.x += moveSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        pos.z += moveSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        pos.z -= moveSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        pos.y += moveSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        pos.y -= moveSpeed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7))
        rot.x += rotSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4))
        rot.x -= rotSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8))
        rot.y += rotSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5))
        rot.y -= rotSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9))
        rot.z += rotSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6))
        rot.z -= rotSpeed;

    cam.SetPosition(pos);
    cam.SetRotation(rot);
}

void RenderCube(sf::RenderWindow& window, Camera& cam, Cube& cube)
{
    string toClip = cam.ClipObject(cube);
    if (toClip == "inside") printf("inside\n");
    else if (toClip == "outside") printf("outside\n");
    else if (toClip == "partial") printf("partial\n");
    else printf("error\n");
    HandleInput(cam);
    if (toClip == "outside") return;
    vector<Vector3f> points = cube.GetWorldPoints();
    vector<sf::Vector3i> triangles = cube.GetTriangles();

    for(auto triangle : triangles)
    {
        Vector2f pointA = cam.WorldToScreenPoint(points[triangle.x]);
        Vector2f pointB = cam.WorldToScreenPoint(points[triangle.y]);
        Vector2f pointC = cam.WorldToScreenPoint(points[triangle.z]);

        // sf::Vertex lineAB[] = {
        //     sf::Vertex(pointA),
        //     sf::Vertex(pointB)
        // };

        // sf::Vertex lineBC[] = {
        //     sf::Vertex(pointB),
        //     sf::Vertex(pointC)
        // };

        // sf::Vertex lineCA[] = {
        //     sf::Vertex(pointC),
        //     sf::Vertex(pointA)
        // };

        // window.draw(lineAB, 2, sf::Lines);
        // window.draw(lineBC, 2, sf::Lines);
        // window.draw(lineCA, 2, sf::Lines);

        sf::VertexArray triangle(sf::Triangles, 3);

        triangle[0].position = pointA;
        triangle[1].position = pointB;
        triangle[2].position = pointC;

        window.draw(triangle);
    }
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Camera cam;
    cam.SetResolution(RES_X, RES_Y);
    float fl = 2.0f;
    cam.SetFocalLength(fl);
    cam.SetSensorSize(0.9, 1.6);
    cam.SetPosition(Vector3f(0, 0, 0));

    Cube cube;
    cube.SetPosition(Vector3f(0, 0, 15));
    cube.SetRotation(Vector3f(0, 0, 0));
    cube.SetScale(Vector3f(1, 1, 1));

    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Rasterizer", sf::Style::Default, settings);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        RenderCube(window, cam, cube);
        window.display();
    }

    return 0;
}