#include "imgui.h"
#include "clean_gui.hpp"
#include <vector>
#include <string>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#define BUTTON_NORMAL 0
#define BUTTON_TEXT 1
#define BUTTON_IMAGE 2

class Button
{
	std::string id;
	ImVec2 pos, size;
	int type;
	std::string text;
	ImFont* font;
	GLuint image;
	float curve;
public:
	Event* click_event;
	Button();
	~Button();
	Button(std::string _id, std::string _text, ImVec2 _pos, ImVec2 _size, ImFont* _font, int _type, float _curve = 0.0f);
	Button(std::string _id, ImVec2 _pos, ImVec2 _size, GLuint _image, float _curve = 10.0f);
	bool render(ImVec2 _pos, ImVec2 _size);
	Button& operator=(const Button&);
};