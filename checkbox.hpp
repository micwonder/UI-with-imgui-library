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
	ImU32 bgcolor;
	bool checked;
	float width;
	bool line;
	
public:
	Event* check_event;
	CheckBox();
	CheckBox(std::string _label, ImVec2 _pos, ImVec2 _size, ImFont* _font, bool _checked, ImU32 _bgcolor = IM_COL32(255, 255, 255, 255), bool _line = false, float _width = 0);
	void render(ImVec2 _pos, ImVec2 _size);
	void setWidth(float _width) { width = _width; }
};