#include "tiles.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

Tiles::Tiles(){}
Tiles::Tiles(ImVec2 _windowpos, ImVec2 _windowsize, ImVec2 _grids, float _spacing, float _thick) : windowpos(_windowpos), windowsize(_windowsize), grids(_grids), spacing(_spacing), thick(_thick) {
	curpos = windowpos;
	cursize = windowsize;
}
Tiles::~Tiles(){}

void Tiles::addTile(char* str_id, ImVec2 tilepos, ImVec2 tilesize, ImU32 color){
	curpos = windowpos + windowsize / grids * tilepos;
	cursize = windowsize / grids * tilesize - ImVec2(spacing, spacing);
	ImGui::GetWindowDrawList()->AddRect(curpos - ImVec2(thick, thick), curpos + cursize + ImVec2(thick, thick), color, thick, 0, thick * 1.5);
	
	ImGui::BeginChild(str_id, cursize, curpos);
}

void Tiles::endTile() { ImGui::EndChild(); }
ImVec2 Tiles::curPos() { return curpos; }
ImVec2 Tiles::curSize() { return cursize; }