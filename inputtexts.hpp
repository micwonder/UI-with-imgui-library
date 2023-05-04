#include "imgui.h"
#include "clean_gui.hpp"

#include <string>

class InputTexts : CleanGui
{
	char* text;
	char* str_id;
	ImVec2 pos, size;
	ImU32 color_dark, color_light, color_edge;
	int type;
	bool status;
	GLuint img_email, img_pass, img_eye_on, img_eye_off;
public:
	InputTexts();
	InputTexts(char* _str_id, ImVec2 _pos, ImVec2 _size, ImU32 _color_dark, ImU32 _color_light, ImU32 _color_edge, int _type, GLuint _img_email, GLuint _img_pass, GLuint _img_eye_on, GLuint _img_eye_off);
	~InputTexts();
	void render(ImVec2 _pos, ImVec2 _size);
};