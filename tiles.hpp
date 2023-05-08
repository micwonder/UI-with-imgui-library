#include "imgui.h"

class Tiles
{
public:
	Tiles();
	~Tiles();
	void addTile(char* str_id, ImVec2 pos, ImVec2 size, ImU32 color);
	void endTile();
};