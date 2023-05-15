#include "imgui.h"
#include "clean_gui.hpp"
#include <vector>
#include <string>

class Graph
{
protected:
	ImVec2 pos, size;
	ImFont* font;
	ImU32 darkcolor, lightcolor, bgcolor;
	int current;
public:
	Graph() {}
	Graph(ImVec2 _pos, ImVec2 _size, ImFont* _font, ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor) : pos(_pos), size(_size), font(_font), darkcolor(_darkcolor), lightcolor(_lightcolor), bgcolor(_bgcolor) { current = 0; }
	void updateColor(ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor) { darkcolor = _darkcolor; lightcolor = _lightcolor; bgcolor = _bgcolor; }
	void updatePosSize(ImVec2 _pos, ImVec2 _size) { pos = _pos; size = _size; }
	void updateFont(ImFont* _font) { font = _font; }
	void render() {}
};

class LineGraph : public Graph
{
	std::vector<float> histogram;
public:
	LineGraph() {}
	LineGraph(ImVec2 _pos, ImVec2 _size, ImFont* _font, ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor, std::vector<float> _histogram);
	void updateHistogram(std::vector<float> _historgram);
	void render();
};

class VarGraph : public Graph
{
	std::vector<std::vector<float>> values;
	std::vector<std::vector<std::string>> valuenames;
	std::vector<std::string> states;
public:
	VarGraph() {}
	VarGraph(ImVec2 _pos, ImVec2 _size, ImFont* _font, ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor, std::vector<std::string> _states, std::vector<std::vector<std::string>> _valuenames, std::vector<std::vector<float>> _values);
	void updateStates(std::vector<std::string> _states);
	void updateValue(int n, std::vector<std::string> _valuename, std::vector<float> _value);
	void updateValues(std::vector<std::vector<std::string>> _valuesnames, std::vector<std::vector<float>> _values);
	float getContentX();
	void render();
};