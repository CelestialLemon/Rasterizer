#include "Camera.hpp"

void Camera::SetClippingPlanes()
{
    //here the fov are half the real fov of camera. i.e for fov of 90deg we only calculate half side i.e 45deg
    float h_fov, v_fov;
    h_fov = atan(h_sensor_size / (focalLength));
    v_fov = atan(v_sensor_size / (focalLength));

    minDistanceCp = Vector3f(0, 0, 1);
    leftCp = Vector3f(cos(h_fov), 0, sin(h_fov));
    rightCp = Vector3f(-cos(h_fov), 0, sin(h_fov));
    topCp = Vector3f(0, -cos(v_fov), sin(v_fov));
    bottomCp = Vector3f(0, cos(v_fov), sin(v_fov));
}

Camera::Camera()
{
    resX = 500;
    resY = 500;
    focalLength = 0.5f;
    v_sensor_size = 1.0f;
    h_sensor_size = 1.0f;
    SetClippingPlanes();
}

Camera::Camera(float _fl, int _resX, int _resY, Vector3f _pos, float _v, float _h)
{
    focalLength = _fl;
    resX = _resX;
    resY = _resY;
    origin = _pos;
    v_sensor_size = _v;
    h_sensor_size = _h;
    SetClippingPlanes();
}

void Camera::SetSensorSize(float _v, float _h) { v_sensor_size = _v; h_sensor_size = _h; SetClippingPlanes(); }

void Camera::SetFocalLength(float& const _fl) { focalLength = _fl; SetClippingPlanes(); }

void Camera::SetResolution(unsigned int& const _resX, unsigned int& const _resY) { resX = _resX; resY = _resY; }

Vector3f Camera::WorldToCameraSpace(Vector3f& const p)
{
    // camera space has its own axes and rotation matrices measure the rotation of cam with
    // respect to the world axes. The camera always points in positive z-axis of camera space
    Matrix <float, 3, 3> scalingAndRotMat = (m_scale * m_rotZ * m_rotY * m_rotX);
    Vector3f temp = p - origin;
    Matrix <float, 3, 1> tempMat;
    tempMat << temp.x, temp.y, temp.z;

    Matrix <float, 3, 1> camSpacePointMat;
    camSpacePointMat = scalingAndRotMat.inverse() * tempMat;

    return Vector3f(camSpacePointMat(0, 0), camSpacePointMat(1, 0), camSpacePointMat(2, 0));
}

Vector2f Camera::WorldToScreenPoint(Vector3f& const p)
{

    //cp is point p in camera space co-ordinates
    Vector3f cp = WorldToCameraSpace(p);

    float x = (focalLength * cp.x) / cp.z;
    float y = (focalLength * cp.y) / cp.z;

    x = (x + h_sensor_size) * (resX / 2);
    y = (y + v_sensor_size) * (resY / 2);

    //do this if the sessor size is not 1, 1
    //don't know why this works but it does
    x /= h_sensor_size;
    y /= v_sensor_size;

    return Vector2f(x, y);
}


string Camera::ClipObjectAgainstPlane(Vector3f& const c, float r, Vector3f& const plane, float d)
{
    float dist = c * plane;
    dist -= d;
    if (dist > r) return "inside"; //completely inside
    else if (dist < -r) return "outside"; // completely outside
    else return "partial"; // partially inside
}

string Camera::ClipObject(Object& const obj)
{
    //here we take origin of the object as the centerOfGeometry
    Vector3f c = obj.GetPosition();
    c = WorldToCameraSpace(c);
    float r = obj.ContainingSphereRadius();

    std::string leftClip = ClipObjectAgainstPlane(c, r, leftCp, 0);
    std::string rightClip = ClipObjectAgainstPlane(c, r, rightCp, 0);
    std::string topClip = ClipObjectAgainstPlane(c, r, topCp, 0);
    std::string bottomClip = ClipObjectAgainstPlane(c, r, bottomCp, 0);
    std::string distanceClip = ClipObjectAgainstPlane(c, r, minDistanceCp, focalLength);

    if (leftClip == "outside" || rightClip == "outside" || topClip == "outside"
        || bottomClip == "outside" || distanceClip == "outside")
        return "outside";
    else if (leftClip == "inside" && rightClip == "inside" && topClip == "inside"
        && bottomClip == "inside" && distanceClip == "inside")
        return "inside";
    else
        return "partial";
}