#pragma once
#include "SFML/Graphics.hpp"
using sf::Vector3f;

class Triangle
{
public:
	Vector3f a;
	Vector3f b;
	Vector3f c;

	Triangle(Vector3f& const _a, Vector3f& const _b, Vector3f& const _c);
	Triangle(Vector3f&& _a, Vector3f&& _b, Vector3f&& _c);
};