#include "imgui.h"
#include "clean_gui.hpp"

#include <string>

class InputTexts : CleanGui
{
	std::string text;
	std::string str_id;
	ImVec2 pos, size;
	ImU32 color_dark, color_light, color_edge;
	int type;
	bool status;
	GLuint img_email, img_pass, img_eye_on, img_eye_off;
	float curve;
public:
	Event* text_edit_event;
	InputTexts& operator = (const InputTexts&);
	InputTexts();
	~InputTexts();
	InputTexts(std::string _str_id, ImVec2 _pos, ImVec2 _size, ImU32 _color_dark, ImU32 _color_light, ImU32 _color_edge, int _type, GLuint _img_email, GLuint _img_pass, GLuint _img_eye_on, GLuint _img_eye_off, float _curve = 10.0f);
	void render(ImVec2 _pos, ImVec2 _size, ImColor bgcolor);
	bool isEmpty() { return text[0] == '\0'; }
};