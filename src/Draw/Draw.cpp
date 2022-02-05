#include "Draw.hpp"

sf::Color operator/(sf::Color color, float d)
{
	return sf::Color(color.r / d, color.g / d, color.b / d);
}

float NormalizeFactor(float& const dy, float& const dx)
{
	float absDy = abs(dy);
	float absDx = abs(dx);

	if (absDy > absDx) return absDy;
	else return absDx;
}


void DrawLine(Vertex& const a, Vertex& const b, sf::RenderWindow& window)
{
	//swap so that x is on the right
	if (a.position.x > b.position.x) std::swap(a, b);

	float dy = b.position.y - a.position.y;
	float dx = b.position.x - a.position.x;
	
	float dr = (b.color.r - a.color.r) / dx;
	float dg = (b.color.g - a.color.g) / dx;
	float db = (b.color.b - a.color.b) / dx;

	float nf = NormalizeFactor(dy, dx);
	dy /= nf;
	dx /= nf;

	sf::RectangleShape pixel;
	pixel.setPosition(a.position);
	pixel.setSize(sf::Vector2f(1.0f, 1.0f));
	pixel.setFillColor(a.color);
	
	float red = a.color.r, green = a.color.g, blue = a.color.b;

	printf("%f %f %f\n", dr, dg, db);
	while (round(pixel.getPosition().x) != round(b.position.x) ||
		round(pixel.getPosition().y) != round(b.position.y))
	{
		window.draw(pixel);
		pixel.setPosition(pixel.getPosition() + sf::Vector2f(dx, dy));
		red += dr;
		green += dg;
		blue += db;
		pixel.setFillColor(sf::Color(red, green, blue));
	}

}