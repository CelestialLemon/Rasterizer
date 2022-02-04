#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>

#include "Object/Cube/Cube.hpp"
#include "Object/Camera/Camera.hpp"

unsigned int RES_X = 1280;
unsigned int RES_Y = 720;

vector<sf::Color> colors = {
    sf::Color::Blue,
    sf::Color::Cyan,
    sf::Color::Green,
    sf::Color::Magenta,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue,
    sf::Color::Cyan,
    sf::Color::Green,
    sf::Color::Magenta,
    sf::Color::Red,
    sf::Color::Yellow
};

void HandleInput(Object& cam)
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

void RenderCube(sf::RenderWindow& window,Object& cube, Camera& cam,
        vector<vector<float>>& z_buffer)
{
    auto worldPoints = cube.GetWorldPoints();
    auto triangles = cube.GetTriangles();

    for (sf::Vector3i triangle : triangles)
    {
        Vector3f wPointA = worldPoints[triangle.x];
        Vector3f wPointB = worldPoints[triangle.y];
        Vector3f wPointC = worldPoints[triangle.z];


    }

}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //2d array of colors i.e frame
    vector<vector<float>> z_buffer(RES_Y, vector<float>(RES_X, FLT_MAX));


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
        RenderCube(window, cube, cam);
        window.display();
    }

    return 0;
}