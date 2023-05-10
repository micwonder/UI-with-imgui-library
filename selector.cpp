#include "selector.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

Selector::Selector() {}
Selector::Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _align)
{
    select_event = new SelectEvent;
	button_id = _button_id;
    popup_id = _popup_id;
	for (int i = 0; i < _items.size(); ++i)
		items.push_back(_items[i]);
	buttonpos = _pos;
	popupsize = _size;
	current_item = items[0];
	current_index = 0;
    button_clicked = false;
    align = _align;
    type = TEXT_BUTTON;
}

Selector::Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _align, GLuint _image)
{
    select_event = new SelectEvent;
    button_id = _button_id;
    popup_id = _popup_id;
    for (int i = 0; i < _items.size(); ++i)
        items.push_back(_items[i]);
    buttonpos = _pos;
    popupsize = _size;
    current_item = items[0];
    current_index = 0;
    button_clicked = false;
    align = _align;
    type = IMAGE_BUTTON;
    image = _image;
}

Selector::~Selector()
{
}

void Selector::doModal(ImVec2 _pos, ImVec2 _size)
{
    buttonpos = _pos;
    popupsize = _size;
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    if (type == 0)
        buttonsize = ImGui::CalcTextSize(current_item.data());
    else
        buttonsize = ImVec2(30, 30);
    if (align == ALIGN_LEFT)
        popuppos = buttonpos + ImVec2(0, buttonsize.y);
    else
        popuppos = buttonpos + buttonsize - ImVec2(popupsize.x, 0);
    if (type == TEXT_BUTTON) {
        ImGui::SetWindowPos(buttonpos);
        if (ImGui::TextButton(button_id.data(), current_item.data())) { button_clicked = true; }
    }
    else {
        ImGui::SetCursorScreenPos(buttonpos);
        if (ImGui::ImageButton(button_id.data(), (void*)(intptr_t)image, {30, 30})) { button_clicked = true; }
    }
    if (button_clicked) {
        button_clicked = render();
    }
    ImGui::PopFont();
}

bool Selector::render()
{
    bool selected = true;
    int past_index = current_index;
    ImGui::SetNextWindowSize(popupsize);
    ImGui::SetNextWindowPos(popuppos);
    ImGui::OpenPopup(popup_id.data());
    if (ImGui::BeginPopup(popup_id.data(), ImGuiWindowFlags_ChildWindow))
    {
        for (int n = 0; n < items.size(); n++)
        {
            bool is_selected = (current_item == items[n]);
            if (ImGui::Selectable(items[n].data(), is_selected))
            {
                current_item = items[n];
                current_index = n;
                if (past_index != current_index)
                    select_event->OnEvent({ (void*)current_index, current_item.data()});
                selected = false;
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndPopup();
    }
    return selected;
}

int Selector::currentIndex() { return current_index; }
std::string Selector::currentItem() { return current_item; }
void Selector::removeSelect() { button_clicked = false; }