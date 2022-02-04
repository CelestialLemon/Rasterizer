#include "Draw.hpp"


float NormalizeFactor(float& const dy, float& const dx)
{
	float absDy = abs(dy);
	float absDx = abs(dx);

	if (absDy > absDx) return absDy;
	else return absDx;
}

void DrawLine(Vertex& const a, Vertex& const b, sf::RenderWindow& window)
{
	//swap so that y is on the right
	if (a.position.y > b.position.y) std::swap(a, b);

	float dy = b.position.y - a.position.y;
	float dx = b.position.x - a.position.x;
	
	sf::Color dc = (b.color - a.color) / dx;

	float nf = NormalizeFactor(dy, dx);
	dy /= nf;
	dx /= nf;

	Vertex currentPoint = a;
	while (currentPoint.position != b.position)
	{
		window.draw(&currentPoint, 1,sf::Points);
	}
}