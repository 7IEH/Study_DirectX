#include "EHTrasnform.h"
#include "EHGameObject.h"
#include "EHConstantBuffer.h"
#include "EHRenderer.h"

namespace EH
{
    Transform::Transform()
        :
          Component(enums::eCommponentType::Transform)
        , mPosition(Math::Vector3(0.f,0.f,0.f))
        , mScale(Math::Vector3(1.f,1.f,1.f))
        , mRotation(Math::Vector3(0.f,0.f,0.f))
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

    void Transform::FixedUpdate()
    {
    }

    void Transform::Render()
    {
    }

    void Transform::SetConstantBuffer()
    {
        ConstantBuffer* cb = renderer::constantBuffers[(UINT)enums::CBYTES::Transform];
        renderer::CBUFFER data;
        data.pos = mPosition;
        data.pad1 = 0;
        data.scale = mScale;
        data.pad2 = 0;

        cb->Bind(&data);
        cb->SetPipline(graphics::ShaderStage::VS);
    }
}