#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <string>
#include "WICTextureLoader11.h"
#include "DDSTextureLoader.h"

#include <atlbase.h>

class Material final
{
	CComPtr < ID3D11ShaderResourceView> mDiffuseMap = nullptr;
	CComPtr < ID3D11ShaderResourceView> mNormalMap = nullptr;
	const wchar_t* diffuse;
	const wchar_t* normal;

	void create(const Material& A)
	{ 
		mDiffuseMap = A.mDiffuseMap;
		mNormalMap = A.mNormalMap;
		diffuse = A.diffuse;
		normal = A.normal;
	}

	HRESULT loadTexture(const wchar_t* pTexPath, const wchar_t* pNormalPath, ID3D11Device* pDevice);

public:

	Material(const wchar_t* pTextPath, const wchar_t* pNormalPath, ID3D11Device* pDevice);
	Material(const Material& A);				// copy constructor

	Material& operator=(const Material& A)
	{
		if (this != (&A))
		{
			create(A);
		}
		return *this;
	}

	void SetTexures(const CComPtr <ID3D11DeviceContext>& pCtx) const;

	~Material() = default;
};