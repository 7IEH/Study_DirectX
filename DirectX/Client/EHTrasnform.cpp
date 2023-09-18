#include "EHTrasnform.h"
#include "EHGameObject.h"

namespace EH
{
    Transform::Transform()
        :
          Component(enums::eCommponentType::Transform)
        , mPosition(Math::Vector3(0.f,0.f,0.f))
        , mScale(Math::Vector3(0.f,0.f,0.f))
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
        GameObject* owner = GetOwner();
        float* temp = owner->GetVertexData();
        
        temp[0] = mPosition.x;
        temp[1] = mPosition.y + mScale.y;
        temp[6] = mPosition.x + mScale.x;
        temp[7] = mPosition.y - mScale.y;
        temp[12] = mPosition.x - mScale.x;  
        temp[13] = mPosition.y - mScale.y;

        //owner->SetVertexData(temp);
    }

    void Transform::Render()
    {
    }
}