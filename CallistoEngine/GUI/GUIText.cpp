#include "GUIText.h"
#include <iostream>
#include "../Graphical/Renderer_GL.h"
#include <filesystem>
#include <string>
#include "GUIManager.h"
#include "../Game.h"

//#include "../Managers/ResourceManager.h"

GUIText::GUIText(const char* pText, const Vector3f& pCol, const Vector3f& pPos, GUIOrigin pOrigin, const int pFontSize) :
	mFontSize(pFontSize)
{
	SetPosition(pPos);
	SetRelativePosition(pPos);
	mFontColour = pCol;
	mText = pText;
	mScale = 1;
	mOrigin = pOrigin;
	Initialise();
}

bool GUIText::InitialiseChild()
{


	// img = ResourceManager::getInstance().LoadTexture("Resources/textures/Default.png");

	mFontShaderVert = "Resources/Shaders/Text/text.vert";

	mFontShaderFrag = "Resources/Shaders/Text/text.frag";

	mShaderObject = new ShaderObject_GL(mFontShaderVert, mFontShaderFrag);
	mShaderObject->UseProgram();

	// TODO  grab the window sizes
	glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(GUIManager::GetInstance().GetUIProjection()));

	//projection = glm::ortho(0.0f, static_cast<float>(1423), 0.0f, static_cast<float>(800));
	//glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));



	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	// find path to font
	std::string font_name = "Resources/Fonts/Antonio/Antonio-Bold.ttf";
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return -1;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, mFontSize);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			TextCharacter textCharacter = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			mTextCharacters.insert(std::pair<char, TextCharacter>(c, textCharacter));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void GUIText::ResizeChild(const int pWidth, const int pHeight)
{


	mShaderObject->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(mShaderObject->GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(GUIManager::GetInstance().GetUIProjection()));

}

void GUIText::Render()
{
	int pX = mPosition.GetX();
	int pY = mPosition.GetY();

	mShaderObject->UseProgram();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUniform3f(glGetUniformLocation(mShaderObject->GetShaderProgram(), "textColor"), mFontColour.GetX(), mFontColour.GetY(), mFontColour.GetZ());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters and render
	for (auto c = mText.begin(); c != mText.end(); c++)
	{
		TextCharacter ch = mTextCharacters[*c];

		float xpos = pX + ch.Bearing.x * mScale;
		float ypos = pY - (ch.Size.y - ch.Bearing.y) * mScale;

		float w = ch.Size.x * mScale;
		float h = ch.Size.y * mScale;

		// Update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// Render the glyph texture over the quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update the content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Render the quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Advance cursor to the next character
		pX += (ch.Advance >> 6) * mScale;  // bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}