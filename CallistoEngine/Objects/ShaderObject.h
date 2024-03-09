#pragma once
class ShaderObject
{
	public:
	ShaderObject() = default;
	virtual ~ShaderObject() = default;
	const virtual void UseProgram() = 0;

	// virtual void Create(const char* pVertexShader, const char* pFragmentShader);
	virtual void Render() = 0;
};

