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

    //clips a point against a single plane
    string ClipPointAgainstPlane(Vector3f& const p, Vector3f& const plane, float d);
    //clips triangle against a single plane
    vector<Triangle> ClipTriangleAgainstPlane(Triangle& const t, Vector3f& const plane, float d);
    //clips object against a single plane
    string ClipSphereAgainstPlane(Vector3f& const c, float r, Vector3f& const plane, float d);

    float focalLength;

    public:
    Camera();
    Camera(float _fl, int _resX, int _resY, Vector3f _pos, float _v, float _h);

    void SetFocalLength(float& const _fl);
    void SetResolution(unsigned int& const _resX, unsigned int& const _resY);
    void SetSensorSize(float _v, float _h);

    Vector3f WorldToCameraSpace(Vector3f& const p);
    Vector2f WorldToScreenPoint(Vector3f& const p);
    Vector2f CameraSpaceToScreenPoint(Vector3f& const p);
    vector<Triangle> ClipTriangle(Triangle& const t);
    string ClipObject(Object& const obj);
};