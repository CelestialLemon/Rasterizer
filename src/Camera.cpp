#include "Object/Camera.hpp"

Camera::Camera()
{
    resX = 500;
    resY = 500;
    focalLength = 0.5f;
    v_sensor_size = 1.0f;
    h_sensor_size = 1.0f;
}

Camera::Camera(float _fl, int _resX, int _resY, Vector3f _pos, float _v, float _h)
{
    focalLength = _fl;
    resX = _resX;
    resY = _resY;
    origin = _pos;
    v_sensor_size = _v; 
    h_sensor_size = _h;
}

void Camera::SetSensorSize(float _v, float _h) { v_sensor_size = _v; h_sensor_size = _h; } 

void Camera::SetFocalLength(float& const _fl) { focalLength = _fl; }

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
    //if outside the viewing range (clip)
    if(p.z < focalLength) return Vector2f(FLT_MAX, FLT_MAX);

    //cp is point p in camera space co-ordinates
    Vector3f cp = WorldToCameraSpace(p);

    float x = (focalLength * cp.x) / cp.z;
    float y = (focalLength * cp.y) / cp.z;

    x = (x + h_sensor_size) * (resX / 2);
    y = (y + v_sensor_size) * (resY / 2);

    return Vector2f(x, y);
}