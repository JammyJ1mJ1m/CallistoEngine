#include "SceneManager.h"


SceneManager::SceneManager(const int pWidth, const int pHeight)  
{
	_width = pWidth;
	_height = pHeight;
	_window = nullptr;
}

void SceneManager::Run()
{

#if OPENGL
	/*_window = new Window_GL(new shootergame  _width, _height);
	_window->Initialise();*/
#endif // OPENGL

}
