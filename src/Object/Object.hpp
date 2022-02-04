#pragma once

#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <vector>

#include "Triangle/Triangle.hpp"

#define PI 3.14159265f

using Eigen::Matrix;
using std::vector;
using sf::Vector3f;

float operator* (Vector3f& const a, Vector3f& const b);

class Object
{
    protected:
    Vector3f origin;
    Vector3f scale;
    Vector3f rot;
    vector<Vector3f> points;
    vector<sf::Vector3i> triangles;

    Matrix <float, 3, 3> m_scale;
    Matrix <float, 3, 3> m_rotX, m_rotY, m_rotZ;
    Matrix <float, 3, 1> m_translate;

    virtual void InitializePoints();
    virtual void InitializeTriangles();

    void ComputeScaleMatrix();
    void ComputeRotationMatrices();
    void ComputeTranslateMatrix();

    public:
    Object();

    void SetPosition(Vector3f _origin);
    void SetRotation(Vector3f _rot);
    void SetScale(Vector3f _scale);

    Vector3f GetPosition();
    Vector3f GetRotation();
    Vector3f GetScale();

    vector<Vector3f> GetWorldPoints();
    vector<sf::Vector3i> GetTriangles();
    float ContainingSphereRadius();
};