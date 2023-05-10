#include "imgui.h"
#include "clean_gui.hpp"
#include <vector>
#include <string>

class CheckBox
{
	std::string label;
	ImVec2 pos;
	ImVec2 size;
	ImFont* font;
	bool checked;
public:
	Event* check_event;
	CheckBox();
	CheckBox(std::string _label, ImVec2 _pos, ImVec2 _size, ImFont* _font, bool _checked);
	void render(ImVec2 _pos, ImVec2 _size);
};