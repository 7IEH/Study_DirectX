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
        GameObject* owner = GetOwner();
        float* temp = owner->GetVertexData();
       

        if (mDegree <= 0.f)
        {
            temp[0] = mPosition.x;
            temp[1] = mPosition.y + mScale.y;
            temp[6] = mPosition.x + mScale.x;
            temp[7] = mPosition.y - mScale.y;
            temp[12] = mPosition.x - mScale.x;
            temp[13] = mPosition.y - mScale.y;
        }
        else
        {
           /* temp[0] = mPosition.x - mScale.x * cosf((mDegree + 90) * (3.14f / 180.f));
            temp[1] = mPosition.y + mScale.x * sinf((mDegree + 90) * (3.14f / 180.f));
            temp[6] = mPosition.x + mScale.x * cosf((mDegree) * (3.14f / 180.f));
            temp[7] = mPosition.y + mScale.x * sinf((mDegree) * (3.14f / 180.f));
            temp[12] = mPosition.x - mScale.x * cosf((mDegree) * (3.14f / 180.f));
            temp[13] = mPosition.y - mScale.x * sinf((mDegree) * (3.14f / 180.f));*/
        }

        //owner->SetVertexData(temp);
    }

    void Transform::Render()
    {
    }
}