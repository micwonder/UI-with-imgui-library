#include "popups.hpp"

Popups::Popups(std::string _id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size)
{
	id = _id;
	for (int i = 0; i < _items.size(); ++i)
		items.push_back(_items[i]);
	pos = _pos;
	size = _size;
	current_item = items[0];
	current_index = 0;
}

Popups::~Popups()
{
}

bool Popups::render()
{
    bool selected = true;
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(pos);
    ImGui::OpenPopup(id.data());
    if (ImGui::BeginPopup(id.data(), ImGuiWindowFlags_ChildWindow))
    {
        for (int n = 0; n < items.size(); n++)
        {
            bool is_selected = (current_item == items[n]);
            if (ImGui::Selectable(items[n].data(), is_selected))
            {
                current_item = items[n];
                current_index = n;
                selected = false;
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndPopup();
    }
    return selected;
}

int Popups::currentIndex() { return current_index; }
std::string Popups::currentItem() { return current_item; }