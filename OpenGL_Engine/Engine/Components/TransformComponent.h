#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>

#include "IComponent.h"

class TransformComponent : public IComponent
{
	DirectX::XMVECTOR mPosition;
	DirectX::XMVECTOR mOGPosition;
	DirectX::XMVECTOR mRotation;
	DirectX::XMVECTOR mOGRotation;
	DirectX::XMVECTOR mScale;
	DirectX::XMVECTOR mOGScale;
	DirectX::XMMATRIX mWorld;



	void create(const TransformComponent& A)
	{

		// assign members
		mPosition = A.mPosition;
		mOGPosition = A.mOGPosition;
		mRotation = A.mRotation;
		mOGRotation = A.mOGRotation;
		mScale = A.mScale;
		mOGScale = A.mOGScale;
		mWorld = A.mWorld;
	}

	const float convertDegreeToRad(const float pDeg) const;

public:
	TransformComponent() = default;
	TransformComponent(const DirectX::XMVECTOR& pPosition, const DirectX::XMVECTOR& pRotation, const DirectX::XMVECTOR& pScale);// default constructor
	TransformComponent(const TransformComponent& A);				// copy constructor
	TransformComponent& operator = (const TransformComponent& A)	// assignment operator
	{
		if (this != (&A))
		{
			create(A);
		}
		return *this;
	}

	ComponentTypes GetType() const override;

	const inline DirectX::XMVECTOR& GetPosition() const { return mPosition; }
	const inline DirectX::XMVECTOR& GetOGPosition() const { return mOGPosition; }

	const inline DirectX::XMVECTOR& GetRotation() const { return mRotation; }
	const inline DirectX::XMVECTOR& GetOGRotation() const { return mOGRotation; }

	const inline DirectX::XMVECTOR& GetScale() const { return mScale; }
	const inline DirectX::XMVECTOR& GetOGScale() const { return mOGScale; }

	const inline DirectX::XMMATRIX& GetWorld() const { return mWorld; }
	const inline void SetPos(const DirectX::XMVECTOR& pPos) { mPosition = pPos; }
	const inline void SetRotation(const DirectX::XMVECTOR& pRot) { mRotation = pRot; }
	const inline void SetScale (const DirectX::XMVECTOR& pScale) { mScale = pScale; }
	const inline void SetWorld(const DirectX::XMMATRIX& pMat) { mWorld = pMat; }

	const void ApplyTransforms();

	~TransformComponent();
};

