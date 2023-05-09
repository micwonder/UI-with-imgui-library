#include "imgui.h"

class Tiles
{
	ImVec2 windowpos;
	ImVec2 windowsize;
	ImVec2 grids;
	ImVec2 curpos;
	ImVec2 cursize;
	float spacing;
	float thick;
public:
	Tiles();
	Tiles(ImVec2 _windowpos, ImVec2 _windowsize, ImVec2 _grids = ImVec2(1, 1), float _spacing = 5.0f, float _sick = 2.0f);
	~Tiles();
	void addTile(char* str_id, ImVec2 tilepos, ImVec2 tilesize, ImU32 color);
	void endTile();
	ImVec2 curPos();
	ImVec2 curSize();
};