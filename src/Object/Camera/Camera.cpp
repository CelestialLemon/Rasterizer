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

Vector2f Camera::CameraSpaceToScreenPoint(Vector3f& const cp)
{
    //cp is point in camera space
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

Vector2f Camera::WorldToScreenPoint(Vector3f& const p)
{

    //cp is point p in camera space co-ordinates
    Vector3f cp = WorldToCameraSpace(p);
    return CameraSpaceToScreenPoint(cp);
    
}

string Camera::ClipPointAgainstPlane(Vector3f& const p, Vector3f& const plane, float d)
{
    float dist = p * plane - d;
    if (dist > 0) return "inside";
    else if (dist < 0) return "outside";
    else return "on-plane";
}

Vector3f LinePlaneIntersection(Vector3f& const a, Vector3f& const b, Vector3f& const plane, float d)
{
    //finds the point of intersection between a line that contains point a and b
    //and plane with a b c represented by vector3f plane and d represented by float d
    //b_a represent b - a;
    Vector3f b_a = b - a;
    float t = (-d - (plane * a)) / (plane * b_a);
    
    //ip is intersection point
    Vector3f ip = a + t * b_a;
    return ip;
}

vector<Triangle> Camera::ClipTriangleAgainstPlane(Triangle& const t, Vector3f& const plane, float d)
{
    //triangle t contains co-ordianates of 3 points in camera space
    //plane contains a b c co-efficient of plane equation
    //d contains d term of plane equation
    int nPointsOutside = 0;

    string aPos = ClipPointAgainstPlane(t.a, plane, d);
    string bPos = ClipPointAgainstPlane(t.b, plane, d);
    string cPos = ClipPointAgainstPlane(t.c, plane, d);
    
    if (aPos == "oustide") nPointsOutside++;
    if (bPos == "oustide") nPointsOutside++;
    if (cPos == "oustide") nPointsOutside++;

    vector<Triangle> clippedTriangles;
    //if all points outside return empty array
    if (nPointsOutside == 3) { clippedTriangles.clear(); }
    //if two points are outside we will have one triangle
    else if (nPointsOutside == 2)
    {
        //_a denotes a' and _b denotes b'
        Vector3f _a, _b;
        //swap points so that b and c are outside and a is inside
        if (bPos == "inside") { std::swap(t.a, t.b); std::swap(aPos, bPos); }
        if (cPos == "inside") { std::swap(t.a, t.c); std::swap(aPos, cPos); }

        _a = LinePlaneIntersection(t.a, t.b, plane, d);
        _b = LinePlaneIntersection(t.a, t.c, plane, d);

        Triangle clippedTriangle = Triangle(t.a, _a, _b);
        clippedTriangles.push_back(clippedTriangle);
    }
    //if one point is outside we will have 2 new triangles
    else if (nPointsOutside == 1)
    {
        //_a denotes a' and _b denotes b'
        Vector3f _a, _b;
        //swap points so that c is outside and a and b are inside
        if (aPos == "outside") { std::swap(t.a, t.c); std::swap(aPos, cPos); }
        if (bPos == "outside") { std::swap(t.b, t.c); std::swap(bPos, cPos); }

        _a = LinePlaneIntersection(t.a, t.c, plane, d);
        _b = LinePlaneIntersection(t.b, t.c, plane, d);

        Triangle clippedTriangle1 = Triangle(t.a, _a, _b);
        Triangle clippedTriangle2 = Triangle(t.a, t.b, _b);

        clippedTriangles.push_back(clippedTriangle1);
        clippedTriangles.push_back(clippedTriangle2);
    }
    else
    {
        //0 points outside
        //return original triangle
        clippedTriangles.push_back(t);
    }

    return clippedTriangles;
}

vector<Triangle> Camera::ClipTriangle(Triangle& const t)
{
    Triangle screenSpace_t = Triangle(WorldToCameraSpace(t.a), WorldToCameraSpace(t.b), WorldToCameraSpace(t.c));
    vector<Triangle> clippedTriangles;
    vector<Triangle> temp;

    clippedTriangles.push_back(screenSpace_t);

    for (int i = 0; i < 5; i++)
    {
        Vector3f plane;
        float d;
        switch (i)
        {
        case 0: 
            plane = leftCp;
            d = 0;
            break;

        case 1:
            plane = rightCp;
            d = 0;
            break;

        case 2:
            plane: topCp;
            d = 0;
            break;

        case 3:
            plane = bottomCp;
            d = 0;
            break;

        case 4:
            plane = minDistanceCp;
            d = focalLength;
            break;

        //this code will never be executed
        default:
            plane = Vector3f(0, 0, 0);
            d = 0;
        }

        for (auto triangle : clippedTriangles)
        {
            auto clippedByPlane = ClipTriangleAgainstPlane(triangle, plane, d);
            temp.insert(temp.end(), clippedByPlane.begin(), clippedByPlane.end());
            clippedTriangles.clear();
            clippedTriangles = temp;
            temp.clear();
        }
    }

    return clippedTriangles;
}


string Camera::ClipSphereAgainstPlane(Vector3f& const c, float r, Vector3f& const plane, float d)
{
    float dist = c * plane - d;
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

    std::string leftClip = ClipSphereAgainstPlane(c, r, leftCp, 0);
    std::string rightClip = ClipSphereAgainstPlane(c, r, rightCp, 0);
    std::string topClip = ClipSphereAgainstPlane(c, r, topCp, 0);
    std::string bottomClip = ClipSphereAgainstPlane(c, r, bottomCp, 0);
    std::string distanceClip = ClipSphereAgainstPlane(c, r, minDistanceCp, focalLength);

    if (leftClip == "outside" || rightClip == "outside" || topClip == "outside"
        || bottomClip == "outside" || distanceClip == "outside")
        return "outside";
    else if (leftClip == "inside" && rightClip == "inside" && topClip == "inside"
        && bottomClip == "inside" && distanceClip == "inside")
        return "inside";
    else
        return "partial";
}