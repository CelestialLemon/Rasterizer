#include <SFML/Graphics.hpp>
#include <string>
#include "../Object.hpp"
using sf::Vector3f;
using sf::Vector2f;
using std::string;

class Camera : public Object
{
    int resX;
    int resY;

    float v_sensor_size;
    float h_sensor_size;

    //cp denotes clipping plane
    Vector3f leftCp, rightCp, topCp, bottomCp;
    //distance clipping plane clips objects if they get closer than min distance
    Vector3f minDistanceCp;
    //clipping planes should be set if focalLength or sensor sizes change
    void SetClippingPlanes();

    //clips object against a single plane
    string ClipObjectAgainstPlane(Vector3f& const c, float r, Vector3f& const plane, float d);

    float focalLength;

    public:
    Camera();
    Camera(float _fl, int _resX, int _resY, Vector3f _pos, float _v, float _h);

    void SetFocalLength(float& const _fl);
    void SetResolution(unsigned int& const _resX, unsigned int& const _resY);
    void SetSensorSize(float _v, float _h);

    Vector3f WorldToCameraSpace(Vector3f& const p);
    Vector2f WorldToScreenPoint(Vector3f& const p);
    string ClipObject(Object& const obj);
};