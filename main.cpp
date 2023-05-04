#include "Gui.hpp"
#include <vector>
#include <string>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

void Draw_ProgressBar(float value, ImVec2 size)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += 5;
    pos.y += 5;
    ImU32 col_a = ImGui::GetColorU32(IM_COL32(0x66, 0xa6, 0xff, 0xff));
    ImU32 col_b = ImGui::GetColorU32(IM_COL32(0x89, 0xf7, 0xfe, 0xff));
    int aR = 0x66, aG = 0xa6, aB = 0xff, aA = 0xff, bR = 0x89, bG = 0xf7, bB = 0xfe, bA = 0xff;
    ImU32 col_bg = ImGui::GetColorU32(IM_COL32(0x2b, 0x2d, 0x3c, 0xff));
    ImU32 color[11] = {col_a};

    for (int i = 1; i < 11; ++i)
    {
        int cR = aR + (int)(1.0 * (bR - aR) / 10 * i);
        int cG = aG + (int)(1.0 * (bG - aG) / 10 * i);
        int cB = aB + (int)(1.0 * (bB - aB) / 10 * i);
        int cA = aA + (int)(1.0 * (bA - aA) / 10 * i);
        color[i] = ImGui::GetColorU32(IM_COL32(cR, cG, cB, cA));
    }
    ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), col_bg, 0.0f, ImDrawFlags_None);
    int count = 1;
    while (value >= 0.1)
    {
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * count, pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll);
        count++;
        value -= 0.1;
    }
    if (value > 0){ ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1), pos.y), ImVec2(pos.x + 1.0 * size.x / 10 * (count - 1 + value / 0.1), pos.y + size.y), col_bg, color[count - 1], color[count], color[count], color[count - 1], 5.0f, ImDrawFlags_RoundCornersAll); }
}

void Draw_Graph(std::vector<char*> x_label, std::vector<float> y_label, ImVec2 size)
{
    ImVec2 pos = ImGui::GetWindowPos();
    ImU32 col_a = ImGui::GetColorU32(IM_COL32(0x66, 0xa6, 0xff, 0xff));
    ImU32 col_b = ImGui::GetColorU32(IM_COL32(0x89, 0xf7, 0xfe, 0xff));
    ImU32 col_bg = ImGui::GetColorU32(IM_COL32(0x21, 0x24, 0x30, 0xff));

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
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
        ImGui::SetCursorScreenPos(ImVec2(pos.x + ImGui::CalcTextSize(max_text).x - ImGui::CalcTextSize(txt).x, pos.y + 1.0 * size.y / 6 * i));
        ImGui::Text(txt);
    }
    ImVec2 y_label_pos = ImVec2(pos.x + 30, pos.y + size.y / 6 * 5);
    ImGui::SetCursorScreenPos(y_label_pos);
    float gy = pos.y + size.y / 6 * 4 + ImGui::CalcTextSize(max_text).y / 2;
    float width = 20;
    float height = size.y / 6 * 4;
    ImGui::GetWindowDrawList()->AddLine({ pos.x + ImGui::CalcTextSize(max_text).x, pos.y + height + +ImGui::CalcTextSize(max_text).y / 2 }, {pos.x + size.x, pos.y + height + +ImGui::CalcTextSize(max_text).y / 2}, IM_COL32(0xff, 0xff, 0xff, 0xff));
    for (int i = 0; i < x_label.size(); ++i)
    {
        ImVec2 txtsize;
        if (i == 0)
            txtsize = ImVec2(0, 0);
        else
            txtsize = ImGui::CalcTextSize(x_label[i - 1]);
        y_label_pos = ImVec2(y_label_pos.x + txtsize.x + 5, y_label_pos.y);
        ImGui::SetCursorScreenPos(y_label_pos);
        ImGui::Text(x_label[i]);
        float gx = y_label_pos.x + ImGui::CalcTextSize(x_label[i]).x / 2;
        ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded(ImVec2(int(gx - width / 2), int(gy - height * y_label[i] / maxVal)), ImVec2(int(gx + width / 2), int(gy)), col_bg, col_a, col_a, col_b, col_b, 5.0f, ImDrawFlags_RoundCornersAll);
    }
    ImGui::PopFont();
}

void Overview_Page(Gui& gui)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0x21, 0x24, 0x30, 0xff));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);

    // Usage Time child
    std::vector<char*> week_x_label = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    std::vector<float> week_y_label = { 480, 1440, 1200, 960, 720, 180, 540, 60 };

    std::vector<char*> month_x_label = { "1-7", "8-14", "15-21", "22-28", "29-last" };
    std::vector<float> month_y_label = { 1200, 960, 720, 180, 1800 };

    std::vector<char*> year_x_label = { "1-3", "4-6", "7-9", "10-12" };
    std::vector<float> year_y_label = { 480, 1200, 720, 540 };
    static int time_flag = 0;
    ImGui::GetWindowDrawList()->AddRect({ 594, 534 }, { 1076, 676 }, IM_COL32(0x00, 0x00, 0x00, 0xff), 2.0f, 0, 4.0f);
    ImGui::BeginChild("Usage Time", ImVec2(480, 140), ImVec2(595, 535));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
    ImGui::SetWindowPos(ImVec2(625, 545));
    ImGui::Text("Usage Time (minutes)");
    ImGui::PopFont();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[10]);
    ImGui::SetWindowPos(ImVec2(940, 545));
    if (ImGui::TextButton("##Week", "Week")) { time_flag = 0; }
    ImGui::SetWindowPos(ImVec2(980, 545));
    if (ImGui::TextButton("##Month", "Month")) { time_flag = 1; }
    ImGui::SetWindowPos(ImVec2(1025, 545));
    if (ImGui::TextButton("##Year", "Year")) { time_flag = 2; }
    ImGui::SetWindowPos(ImVec2(610, 570));
    if (time_flag == 0)
        Draw_Graph(week_x_label, week_y_label, ImVec2(460, 90));
    else if (time_flag == 1)
        Draw_Graph(month_x_label, month_y_label, ImVec2(460, 90));
    else
        Draw_Graph(year_x_label, year_y_label, ImVec2(460, 90));
    ImGui::PopFont();
    ImGui::EndChild();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void testPage()
{
}

int main()
{
    auto gui = Gui();
    while (gui.isRunning()) 
    {
        gui.renderFrame();
        //gui.start_clean_window();
        //testPage();
        //gui.end_clean_window();
    }
}
