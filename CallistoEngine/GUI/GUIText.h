#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "../Objects/ShaderObject_GL.h"
#include "../Math/Vector.h"

#include "../inc/freetype/ft2build.h"
#include "GUIElement.h"

//#include "ft2build.h"
#include FT_FREETYPE_H  

class GUIText : public GUIElement
{
	struct TextCharacter {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	const char* mFontShaderVert;
	const char* mFontShaderFrag;
	ShaderObject_GL* mShaderObject;
	unsigned int VAO, VBO;

	//Vector3f mPosition;
	Vector3f mFontColour;
	std::string mText;

	glm::mat4 projection;

	std::map<char, TextCharacter> mTextCharacters;

	int mFontSize;
public:
	GUIText(const char* pText,const Vector3f& pCol,  const Vector3f& pPos, const int pFontSize = 48);
	~GUIText() = default;
	bool Initialise();
	//void Render(int pX, int pY, int width, int height);
	void Resize(const int pWidth, const int pHeight) override;
	void Render() override;

};

