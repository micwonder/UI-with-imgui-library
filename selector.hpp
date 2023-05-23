#include "imgui.h"
#include "clean_gui.hpp"
#include <vector>
#include <string>
#include <ctime>

#define TEXT_BUTTON 0
#define IMAGE_BUTTON 1
#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1

class Selector
{
	std::string button_id, popup_id;
	std::vector<std::string> items;
	ImVec2 buttonpos, popuppos;
	ImVec2 buttonsize, popupsize;
	std::string current_item;
	int current_index;
	bool button_clicked;
	GLuint image;
	int type;
	int align;
	bool oversize = false;
public:
	Event* select_event;
	std::time_t cT;
	Selector();
	Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _align);
	Selector(std::string _button_id, std::string _popup_id, std::vector<std::string> _items, ImVec2 _pos, ImVec2 _size, int _algin, GLuint _image);
	~Selector();
	Selector& operator = (const Selector& other);
	void doModal(ImVec2 _pos, ImVec2 _size);
	bool render();
	int currentIndex();
	void removeSelect() { button_clicked = false; }
	bool isClicked() { return button_clicked; }
	std::string currentItem();
	void updateValue(std::vector<std::string> _items);
	float getWidth();
	float getContentHeight();
};