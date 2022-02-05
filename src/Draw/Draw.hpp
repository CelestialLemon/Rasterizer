#pragma once
#include "SFML/Graphics.hpp"

using sf::Vertex;

//takes two vertexes describes in screen co-ordinates and draws a line
void DrawLine(Vertex& const a, Vertex& const b, sf::RenderWindow& window);
