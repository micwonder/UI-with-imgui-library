#include "checkbox.hpp"

CheckBox::CheckBox() {}
CheckBox::CheckBox(std::string _label, ImVec2 _pos, ImVec2 _size, ImFont* _font, bool _checked, ImU32 _bgcolor, bool _line, float _width) : label(_label), pos(_pos), size(_size), font(_font), checked(_checked), bgcolor(_bgcolor), line(_line), width(_width) { check_event = new CheckEvent; }
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
	ImVec2 spacing = ImGui::GetStyle().ItemSpacing;
	float y = ImGui::GetCursorPosY() - spacing.y / 2 - 20;
	if (line)
	{
		ImGui::GetWindowDrawList()->AddRectFilled({ ImGui::GetCursorScreenPos().x + spacing.y, y }, { ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), y + 24 }, bgcolor);
		ImGui::GetWindowDrawList()->AddRectFilled({ ImGui::GetCursorScreenPos().x + spacing.y, y + 10}, { ImGui::GetCursorScreenPos().x + spacing.y + width, y + 13 }, IM_COL32(0x21, 0x23, 0x2d, 0xff));
	}
	else
		ImGui::GetWindowDrawList()->AddRectFilled({ ImGui::GetCursorScreenPos().x + spacing.y, y }, { ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), y + 24 }, bgcolor);
	ImGui::PopFont();
}