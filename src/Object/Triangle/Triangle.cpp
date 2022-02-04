#include "Triangle.hpp"

Triangle::Triangle(Vector3f& const _a, Vector3f& const _b, Vector3f& const _c)
{
	a = _a;
	b = _b;
	c = _c;
}

Triangle::Triangle(Vector3f&& _a, Vector3f&& _b, Vector3f&& _c)
{
	a = _a;
	b = _b;
	c = _c;
}
