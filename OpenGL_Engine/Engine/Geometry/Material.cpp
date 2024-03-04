#include "Material.h"

// rename this into LoadMaterial, and make CreateWICTex... into its own method to avoid repeating code
HRESULT Material::loadTexture(const wchar_t* pTexPath, const wchar_t* pNormalPath, ID3D11Device* pDevice)
{
	HRESULT hr = DirectX::CreateDDSTextureFromFile(pDevice, pTexPath, nullptr, &mDiffuseMap);
	//HRESULT hr = DirectX::CreateWICTextureFromFile(pDevice, pTexPath, nullptr, &mDiffuseMap);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Cannot find the specified diffuse texture", L"Error", MB_OK);
		hr = DirectX::CreateDDSTextureFromFile(pDevice, L"Textures/Default/default.dds", nullptr, &mDiffuseMap);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"Default texture missing, it should be located in: Textures/Default/default.dds", L"Error", MB_OK);
			return hr;
		}

		hr = DirectX::CreateDDSTextureFromFile(pDevice, L"Textures/Default/Default_normal.dds", nullptr, &mNormalMap);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"Default normal missing, it should be located in: Textures/Default/Default_normal.dds", L"Error", MB_OK);
			return hr;
		}
	}
	else {

		hr = DirectX::CreateDDSTextureFromFile(pDevice, pNormalPath, nullptr, &mNormalMap);
		if (FAILED(hr))
			return hr;
	}



}

Material::Material(const wchar_t* pTextPath, const wchar_t* pNormalPath, ID3D11Device* pDevice)
{
	diffuse = pTextPath;
	normal = pNormalPath;
	loadTexture(pTextPath, pNormalPath, pDevice);
}

Material::Material(const Material& A)
{
	create(A);
}


void Material::SetTexures(const CComPtr <ID3D11DeviceContext>& pCtx) const
{
	pCtx->PSSetShaderResources(0, 1, &mDiffuseMap.p);
	pCtx->PSSetShaderResources(1, 1, &mNormalMap.p);
}