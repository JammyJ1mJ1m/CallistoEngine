#include "TransformComponent.h"

const float TransformComponent::convertDegreeToRad(const float pDeg) const
{
	return pDeg * 3.141592 / 180.0f;
}

TransformComponent::TransformComponent(const DirectX::XMVECTOR& pPosition, const DirectX::XMVECTOR& pRotation, const DirectX::XMVECTOR& pScale) :
	mPosition(pPosition),
	mOGPosition(pPosition),
	mScale(pScale),
	mOGScale(pScale)
{
	mRotation.m128_f32[0] = convertDegreeToRad(pRotation.m128_f32[0]);
	mRotation.m128_f32[1] = convertDegreeToRad(pRotation.m128_f32[1]);
	mRotation.m128_f32[2] = convertDegreeToRad(pRotation.m128_f32[2]);
	mOGRotation = mRotation;
	mWorld = DirectX::XMMatrixScaling(pScale.m128_f32[0], pScale.m128_f32[1], pScale.m128_f32[2]);

	mWorld *= DirectX::XMMatrixRotationX(mRotation.m128_f32[0]);
	mWorld *= DirectX::XMMatrixRotationY(mRotation.m128_f32[1]);
	mWorld *= DirectX::XMMatrixRotationZ(mRotation.m128_f32[2]);


	mWorld *= DirectX::XMMatrixTranslation(pPosition.m128_f32[0], pPosition.m128_f32[1], pPosition.m128_f32[2]);
}

TransformComponent::TransformComponent(const TransformComponent& A)
{
	create(A);
}

IComponent::ComponentTypes TransformComponent::GetType() const
{
	return IComponent::ComponentTypes::COMPONENT_TRANSFORM;
}

const void TransformComponent::ApplyTransforms()
{
	mWorld = DirectX::XMMatrixIdentity() *
		DirectX::XMMatrixScaling(GetScale().m128_f32[0], GetScale().m128_f32[1], GetScale().m128_f32[2]) *
		DirectX::XMMatrixRotationX(GetRotation().m128_f32[0]) *
		DirectX::XMMatrixRotationY(GetRotation().m128_f32[1]) *
		DirectX::XMMatrixRotationZ(GetRotation().m128_f32[2]) *
		DirectX::XMMatrixTranslation(GetPosition().m128_f32[0], GetPosition().m128_f32[1], GetPosition().m128_f32[2]);
}

TransformComponent::~TransformComponent() = default;