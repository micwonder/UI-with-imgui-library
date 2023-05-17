#include "button.hpp"

Button::Button() {}
Button::~Button() {}
Button::Button(std::string _id, std::string _text, ImVec2 _pos, ImVec2 _size, ImFont* _font, int _type, float _curve) : id(_id), text(_text), pos(_pos), size(_size), font(_font), type(_type), curve(_curve) { click_event = new ClickEvent; }
Button::Button(std::string _id, ImVec2 _pos, ImVec2 _size, GLuint _image, float _curve) : id(_id), pos(_pos), size(_size), image(_image), type(BUTTON_IMAGE), curve(_curve) { click_event = new ClickEvent; }
bool Button::render(ImVec2 _pos, ImVec2 _size)
{
	pos = _pos;
	size = _size;
	ImVec2 padding = ImGui::GetStyle().FramePadding;
	bool clicked = false;
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, curve);
	if (type == BUTTON_NORMAL) {
		ImGui::PushFont(font);
		ImGui::SetCursorScreenPos(pos);
		if (ImGui::Button(text.data(), size))
		{
			click_event->OnEvent({});
			clicked = true;
		}
		ImGui::PopFont();
	}
	else if (type == BUTTON_TEXT) {
		ImGui::PushFont(font);
		ImGui::SetWindowPos(pos);
		if (ImGui::TextButton(id.data(), text.data(), size))
		{
			click_event->OnEvent({});
			clicked = true;
		}
		ImGui::PopFont();
	}
	else {
		ImVec2 r_size = size - ImVec2(padding.x * 2, padding.x * 2);
		ImGui::SetCursorScreenPos(pos);
		if (ImGui::ImageButton(id.data(), (void*)(intptr_t)image, r_size))
		{
			click_event->OnEvent({});
			clicked = true;
		}
	}
	ImGui::PopStyleVar();
	return clicked;
}