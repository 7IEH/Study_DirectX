#include "EHTrasnform.h"
#include "EHGameObject.h"

namespace EH
{
    Transform::Transform()
        :
          Component(enums::eCommponentType::Transform)
        , mPosition(Math::Vector3(0.f,0.f,0.f))
        , mScale(Math::Vector3(0.f,0.f,0.f))
        , mDegree(-1.f)
    {
    }

    Transform::~Transform()
    {
    }

    void Transform::Initialize()
    {
    }

    void Transform::Update()
    {
       
    }

    void Transform::Render()
    {
    }
}