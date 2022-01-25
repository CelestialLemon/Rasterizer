#include <SFML/Graphics.hpp>
#include "Object/Object.hpp"
using sf::Vector3f;
using sf::Vector2f;

class Camera : public Object
{
    int resX;
    int resY;

    float v_sensor_size;
    float h_sensor_size;

    float focalLength;

    public:
    Camera();
    Camera(float _fl, int _resX, int _resY, Vector3f _pos, float _v, float _h);

    void SetFocalLength(float& const _fl);
    void SetResolution(unsigned int& const _resX, unsigned int& const _resY);
    void SetSensorSize(float _v, float _h);

    Vector3f WorldToCameraSpace(Vector3f& const p);
    Vector2f WorldToScreenPoint(Vector3f& const p);
};