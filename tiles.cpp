#include "tiles.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

Tiles::Tiles(){}
Tiles::Tiles(ImVec2 _windowpos, ImVec2 _windowsize, ImVec2 _grids, float _spacing, float _thick, float _curve) : windowpos(_windowpos), windowsize(_windowsize), grids(_grids), spacing(_spacing), thick(_thick), curve(_curve) {
	curpos = windowpos;
	cursize = windowsize;
	thick = thick < curve ? curve : thick;
}

void Tiles::addTile(char* str_id, ImVec2 tilepos, ImVec2 tilesize, ImU32 color){
	curpos = windowpos + windowsize / grids * tilepos;
	cursize = windowsize / grids * tilesize - ImVec2(spacing, spacing);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, thick);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, curve);
	ImGui::PushStyleColor(ImGuiCol_Border, color);
	ImGui::BeginChild(str_id, cursize, curpos, true, ImGuiWindowFlags_HorizontalScrollbar);
}

void Tiles::endTile() { ImGui::EndChild(); ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::PopStyleVar(); }
void Tiles::setSpacing() { ImGui::SetWindowPos(curpos + ImVec2(thick, thick)); }
ImVec2 Tiles::curPos() { return curpos + ImVec2(thick , thick); }
ImVec2 Tiles::curSize() { return cursize - ImVec2(thick * 2, thick * 2); }