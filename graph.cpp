#include "graph.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

LineGraph::LineGraph(ImVec2 _pos, ImVec2 _size, ImFont* _font, ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor, std::vector<float> _histogram) : Graph(_pos, _size, _font, _darkcolor, _lightcolor, _bgcolor) {
	for(int i = 0; i < _histogram.size(); i ++)
		histogram.push_back(_histogram[i]);
}
void LineGraph::updateHistogram(std::vector<float> _historgram) {
	histogram.clear();
	for (int i = 0; i < _historgram.size(); i++)
		histogram.push_back(_historgram[i]);
}
void LineGraph::render() {
    for (int i = 0; i < (int)(size.x); i++) {
        int hispos = (int)(1.0 * i / size.x * histogram.size());
        int leny = (int)(1.0 * size.y * histogram[hispos]);
        int cury = (int)pos.y + (int)((0.0 + size.y - leny) / 2);
        ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x + i, cury), ImVec2(pos.x + i, cury + leny), lightcolor);
    }
}

VarGraph::VarGraph(ImVec2 _pos, ImVec2 _size, ImFont* _font, ImU32 _darkcolor, ImU32 _lightcolor, ImU32 _bgcolor, std::vector<std::string> _states, std::vector<std::vector<std::string>> _valuenames, std::vector<std::vector<float>> _values) : Graph(_pos, _size, _font, _darkcolor, _lightcolor, _bgcolor) {
	for (int i = 0; i < _states.size(); i++)
		states.push_back(_states[i]);
    for (int i = 0; i < _valuenames.size(); i++) {
        std::vector<std::string> temp;
        for (int j = 0; j < _valuenames[i].size(); j++)
            temp.push_back(_valuenames[i][j]);
        valuenames.push_back(temp);
    }
	for (int i = 0; i < _values.size(); i++) {
		std::vector<float> temp;
		for (int j = 0; j < _values[i].size(); j++)
			temp.push_back(_values[i][j]);
		values.push_back(temp);
	}
}

void VarGraph::updateStates(std::vector<std::string> _states)
{
    states.clear();
    for (int i = 0; i < _states.size(); i++)
        states.push_back(_states[i]);
}
void VarGraph::updateValue(int n, std::vector<std::string> _valuename, std::vector<float> _value) {
	if (n >= values.size())
		return;
	values[n].clear();
	for (int i = 0; i < _value.size(); i++)
		values[n].push_back(_value[i]);
    valuenames[n].clear();
    for (int i = 0; i < _valuename.size(); i++)
        valuenames[n].push_back(_valuename[i]);
}
void VarGraph::updateValues(std::vector<std::vector<std::string>> _valuenames, std::vector<std::vector<float>> _values) {
	valuenames.clear();
	values.clear();

    for (int i = 0; i < _valuenames.size(); i++) {
        std::vector<std::string> temp;
        for (int j = 0; j < _valuenames[i].size(); j++)
            temp.push_back(_valuenames[i][j]);
        valuenames.push_back(temp);
    }
    for (int i = 0; i < _values.size(); i++) {
        std::vector<float> temp;
        for (int j = 0; j < _values[i].size(); j++)
            temp.push_back(_values[i][j]);
        values.push_back(temp);
    }
}

void VarGraph::render(){
    float butpos = 0;
    ImGui::PushFont(font);
    float offset = ImGui::GetScrollX();
    int i;
    float t_off = offset;
    if (offset == cur_off)
    {
        offset = 0;
    }
    for (i = states.size() - 1; i >= 0; i--) {
        std::string id = "##button";
        id += i;
        butpos += (ImGui::CalcTextSize(states[i].data()).x + 10);
        if (t_off == cur_off)
        {
            ImGui::SetWindowPos(pos + ImVec2(size.x - butpos + t_off, 0));
        }
        else
            ImGui::SetWindowPos(pos + ImVec2(size.x - butpos + t_off, 0));
        if (ImGui::TextButton(id.data(), states[i].data()))
        {
            if (current != i)
            {
                current = i;
                cur_off = offset;
            }
        }
    }
    ImVec2 curpos = this->pos + ImVec2(0, ImGui::CalcTextSize(states[current].data()).y) - ImVec2(offset, 0);
    ImVec2 cursize = this->size - ImVec2(0, ImGui::CalcTextSize(states[current].data()).x);
    std::vector<std::string> x_label = valuenames[current];
    std::vector<float> y_label = values[current];
    float maxVal = y_label[0];
    for (int i = 0; i < y_label.size(); ++i)
        if (maxVal < y_label[i])
            maxVal = y_label[i];
    char max_text[10];
    sprintf(max_text, "%.0f", maxVal);
    for (int i = 0; i < 5; ++i)
    {
        char txt[10];
        sprintf(txt, "%d", (int)(maxVal - maxVal / 4 * i));
        ImGui::SetCursorScreenPos(ImVec2(curpos.x + ImGui::CalcTextSize(max_text).x - ImGui::CalcTextSize(txt).x, curpos.y + 1.0 * cursize.y / 6 * i));
        ImGui::Text(txt);
    }
    ImVec2 y_label_pos = ImVec2(curpos.x + 30, curpos.y + cursize.y / 6 * 5);
    ImGui::SetCursorScreenPos(y_label_pos);
    float gy = curpos.y + cursize.y / 6 * 4 + ImGui::CalcTextSize(max_text).y / 2;
    float width = 20;
    float height = cursize.y / 6 * 4;
    ImGui::GetWindowDrawList()->AddLine({ curpos.x + ImGui::CalcTextSize(max_text).x, curpos.y + height + +ImGui::CalcTextSize(max_text).y / 2 }, { curpos.x + getContentX(), curpos.y + height + +ImGui::CalcTextSize(max_text).y / 2}, IM_COL32(0xff, 0xff, 0xff, 0xff));
    for (int i = 0; i < x_label.size(); ++i)
    {
        ImVec2 txtsize;
        if (i == 0)
            txtsize = ImVec2(0, 0);
        else
            txtsize = ImGui::CalcTextSize(x_label[i - 1].data());
        y_label_pos = ImVec2(y_label_pos.x + txtsize.x + 5, y_label_pos.y);
        ImGui::SetCursorScreenPos(y_label_pos);
        ImGui::Text(x_label[i].data());
        float gx = y_label_pos.x + ImGui::CalcTextSize(x_label[i].data()).x / 2;
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(int(gx - width / 2), int(gy - height * y_label[i] / maxVal)), ImVec2(int(gx + width / 2), int(gy)), bgcolor, darkcolor, darkcolor, lightcolor, lightcolor, 5.0f, ImDrawFlags_RoundCornersAll);
    }
    ImGui::PopFont();
}

float VarGraph::getContentX() {
    std::vector<std::string> x_label = valuenames[current];
    std::vector<float> y_label = values[current];
    ImGui::PushFont(font);
    float maxVal = y_label[0];
    for (int i = 0; i < y_label.size(); ++i)
        if (maxVal < y_label[i])
            maxVal = y_label[i];
    char max_text[10];
    sprintf(max_text, "%.0f", maxVal);
    float width = ImGui::CalcTextSize(max_text).x;
    for (int i = 0; i < x_label.size(); i++) {
        width += ImGui::CalcTextSize(x_label[i].data()).x;
    }
    ImGui::PopFont();
    return width + 50;
}