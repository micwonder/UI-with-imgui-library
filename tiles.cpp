#include "tiles.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

Tiles::Tiles(){}
Tiles::~Tiles(){}

void Tiles::addTile(char* str_id, ImVec2 pos, ImVec2 size, ImU32 color)
{
	ImGui::GetWindowDrawList()->AddRect(pos - ImVec2(2, 2), pos + size + ImVec2(2, 2), color, 2.0f, 0, 2.0f);
	ImGui::BeginChild(str_id, size, pos);
}

void Tiles::endTile()
{
	ImGui::EndChild();
}