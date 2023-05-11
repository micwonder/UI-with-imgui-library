#include "checkbox.hpp"

CheckBox::CheckBox() {}
CheckBox::CheckBox(std::string _label, ImVec2 _pos, ImVec2 _size, ImFont* _font, bool _checked) : label(_label), pos(_pos), size(_size), font(_font), checked(_checked) { check_event = new CheckEvent; }
void CheckBox::render(ImVec2 _pos, ImVec2 _size)
{
	bool last_checked = checked;
	pos = _pos;
	size = _size;
	ImGui::PushFont(font);
	ImGui::SetWindowPos(pos);
	ImGui::Checkbox(label.data(), &checked);
	if (last_checked != checked)
		check_event->OnEvent({ (void*)checked });
	ImGui::PopFont();
}