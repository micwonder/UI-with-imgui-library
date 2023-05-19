#include "inputtexts.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

InputTexts::InputTexts(){}
InputTexts::InputTexts(char* _str_id, ImVec2 _pos, ImVec2 _size, ImU32 _color_dark, ImU32 _color_light, ImU32 _color_edge, int _type, GLuint _img_email, GLuint _img_pass, GLuint _img_eye_on, GLuint _img_eye_off, float _curve) : pos(_pos), size(_size), color_dark(_color_dark), color_light(_color_light), color_edge(_color_edge), type(_type), img_email(_img_email), img_pass(_img_pass), img_eye_on(_img_eye_on), img_eye_off(_img_eye_off), curve(_curve)
{
    text_edit_event = new TextEditEvent;
    str_id = new char[strlen(_str_id)];
    strcpy(str_id, _str_id);
    text = new char[30];
    strcpy(text, "");
    status = false;
}

InputTexts::~InputTexts() {
}
void InputTexts::render(ImVec2 _pos, ImVec2 _size, ImColor bg_color) {
    pos = _pos;
    size = _size;
    float padding_x = 20;
    float padding_y = (ImGui::GetFontSize() - ImGui::GetStyle().FramePadding.y) * 2;
    float width = (size.x - padding_x * 3);
    ImVec2 start_pos = { pos.x + padding_x, pos.y + (size.y - padding_y) / 2 };
    char placeholder[30];
    char temptext[30];

    ImGui::SetCursorPos({ start_pos.x + padding_y, start_pos.y });
    ImGui::SetNextItemWidth(width - padding_y);
    if (type == 0) { strcpy(placeholder, "Email"); }
    else { strcpy(placeholder, "********"); }
    strcpy(temptext, text);
    if (type == 1 && status == false) {
        for (int i = 0; i < strlen(text); ++i) { temptext[i] = '*'; }
    }
    char before[30];
    strcpy(before, text);
    ImGui::InputTextWithHint(str_id, placeholder, text, 30);
    if (strcmp(before, text) != 0)
        text_edit_event->OnEvent({ text });
    ImGui::GetWindowDrawList()->AddRectFilledMultiColorRounded({ start_pos.x - curve, start_pos.y - curve }, { start_pos.x + width + 20 + curve, start_pos.y + padding_y + curve }, bg_color, color_dark, color_light, color_light, color_dark, curve);
    ImGui::GetWindowDrawList()->AddRect({ start_pos.x - curve - 1, start_pos.y - curve - 1 }, { start_pos.x + width + 20 + curve + 2, start_pos.y + padding_y + curve + 2 }, color_edge, curve, 0, 2.0f);
    ImGui::SetCursorPos({start_pos.x + padding_y + 8, start_pos.y + 8 });
    if (text[0] == NULL) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0xff, 0xff, 0xff, 0x7f));
        ImGui::Text(placeholder);
        ImGui::PopStyleColor();
    }
    else { ImGui::Text(temptext); }
    if (type == 0)
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_email, start_pos, start_pos + ImVec2(padding_y, padding_y));
    else {
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_pass, start_pos, start_pos + ImVec2(padding_y, padding_y));
        ImGui::SetCursorScreenPos({ start_pos.x + width + 20 - padding_y, start_pos.y });
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x00, 0x00, 0x00, 0x00));
        if (status == true) {
            if (ImGui::ImageButton("##eye_on", (void*)(intptr_t)img_eye_on, { padding_y - 3, padding_y - 3 })) { status = false; }
        }
        else {
            if (ImGui::ImageButton("##eye_off", (void*)(intptr_t)img_eye_off, { padding_y - 3, padding_y - 3})) { status = true; }
        }
        ImGui::PopStyleColor();
    }
}