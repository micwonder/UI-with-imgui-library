#include "imgui.h"
#include <vector>
#include <string>

class Popups
{
	std::string id;
	std::vector<std::string> items;
	ImVec2 pos, size;
	std::string current_item;
	int current_index;
public:
	Popups(std::string _id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size);
	~Popups();
	bool render();
	int currentIndex();
	std::string currentItem();
};