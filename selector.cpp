#include "selector.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

Selector::Selector() {}
Selector::Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _align) : button_id(_button_id), popup_id(_popup_id), buttonpos(_pos), popupsize(_size)
{
    select_event = new SelectEvent;
	for (int i = 0; i < _items.size(); ++i)
		items.push_back(_items[i]);
	current_item = items[0];
	current_index = 0;
    button_clicked = false;
    align = _align;
    type = TEXT_BUTTON;
    image = 0;
    cT = 0;
}
Selector& Selector::operator = (const Selector& other) {
    if (this == &other)
        return *this;
    button_id = other.button_id, popup_id = other.popup_id;
    std::vector<std::string> items;
    buttonpos = other.buttonpos, popuppos = other.popuppos;
    buttonsize = other.buttonsize, popupsize = other.popupsize;
    current_item = other.current_item;
    current_index = other.current_index;
    button_clicked = other.button_clicked;
    image = other.image;
    type = other.type;
    align = other.align;
    oversize = other.oversize;
    select_event = other.select_event;
    cT = other.cT;
    return *this;
}
Selector::Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _align, GLuint _image) : button_id(_button_id), popup_id(_popup_id), buttonpos(_pos), popupsize(_size)
{
    select_event = new SelectEvent;
    for (int i = 0; i < _items.size(); ++i)
        items.push_back(_items[i]);
    current_item = items[0];
    current_index = 0;
    button_clicked = false;
    align = _align;
    type = IMAGE_BUTTON;
    image = _image;
    cT = 0;
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
    if (getWidth() >= popupsize.x)
    {
        popupsize.x = getWidth();
        oversize = false;
    }
    else
        oversize = true;
    if (align == ALIGN_LEFT)
        popuppos = buttonpos + ImVec2(0, buttonsize.y);
    else
        popuppos = buttonpos + buttonsize - ImVec2(popupsize.x, 0);
    popuppos.y += 5;
    if (type == TEXT_BUTTON) {
        std::string temp = " ";
        if (oversize == true) {
            while (1) {
                if (ImGui::CalcTextSize((current_item + temp).data()).x > popupsize.x)
                    break;
                temp += " ";
            }
        }
        if (temp.size() >= 6)
            temp.erase(temp.size() - 6);
        else
            temp = " ";
        ImGui::SetWindowPos(buttonpos);
        float fs = ImGui::GetIO().FontGlobalScale;
        if (ImGui::TextButton(button_id.data(), (current_item + temp + "   ").data())) { button_clicked = !button_clicked; cT = std::time(0); }
        ImVec2 arrowpos = buttonpos + ImGui::CalcTextSize((current_item + temp).data()) + ImVec2(0, 2);
        arrowpos = ImVec2((int)arrowpos.x, (int)arrowpos.y);
        if (button_clicked)
        {
            ImGui::GetWindowDrawList()->AddLine({ arrowpos.x, arrowpos.y}, { arrowpos.x + 5 * fs, arrowpos.y - 10 * fs }, IM_COL32(255, 255, 255, 128));
            ImGui::GetWindowDrawList()->AddLine({ arrowpos.x + 5 * fs, arrowpos.y - 10 * fs }, { arrowpos.x + 10 * fs, arrowpos.y }, IM_COL32(255, 255, 255, 128));

        }
        else
        {
            ImGui::GetWindowDrawList()->AddLine({ arrowpos.x, arrowpos.y - 10 * fs }, { arrowpos.x + 5 * fs, arrowpos.y}, IM_COL32(255, 255, 255, 128));
            ImGui::GetWindowDrawList()->AddLine({ arrowpos.x + 5 * fs, arrowpos.y}, { arrowpos.x + 10 * fs, arrowpos.y - 10 * fs }, IM_COL32(255, 255, 255, 128));
        }
    }
    else {
        ImGui::SetCursorScreenPos(buttonpos);
        if (ImGui::ImageButton(button_id.data(), (void*)(intptr_t)image, { 30, 30 })) { button_clicked = !button_clicked; cT = std::time(0); }
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
    if (popupsize.y > getContentHeight())
        ImGui::SetWindowSize({ popupsize.x, getContentHeight() });
    else
        ImGui::SetNextWindowSize(popupsize);
    ImGui::SetNextWindowPos(popuppos);
    ImGui::SetNextWindowContentSize({ popupsize.x, getContentHeight() });
    ImGui::OpenPopup(popup_id.data());
    if (ImGui::BeginPopup(popup_id.data(), ImGuiWindowFlags_NoFocusOnAppearing))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, 0));
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
        ImGui::PopStyleVar();
        ImGui::EndPopup();
    }
    return selected;
}

int Selector::currentIndex() { return current_index; }
std::string Selector::currentItem() { return current_item; }
void Selector::updateValue(std::vector<std::string> _items) {
    items.clear();
    for (int i = 0; i < _items.size(); i++)
        items.push_back(_items[i]);
    current_index = 0;
    current_item = items[0];
}

float Selector::getWidth() {
    float maxWidth = 0;
    for (int i = 0; i < items.size(); i++)
        if (maxWidth < ImGui::CalcTextSize(items[i].data()).x)
            maxWidth = ImGui::CalcTextSize(items[i].data()).x;
    return maxWidth + 15;
}
float Selector::getContentHeight() {
    return ImGui::CalcTextSize(items[0].data()).y * items.size() + 10;
}