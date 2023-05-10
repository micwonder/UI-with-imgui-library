#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>

#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")

#include "design/MenuBg.h" // Background picture
#include "design/abyssinica.h" // Original font -> 0

// Blur
#include "blur.hpp"
#include "design/GeneralBg.h"
#include "design/icon_font.h"

LPDIRECT3D9              g_pD3D = NULL;
LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
D3DPRESENT_PARAMETERS    g_d3dpp = {};

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImFont* ico = nullptr;
ImFont* tab_ico = nullptr;
ImFont* tab_ico_two = nullptr;
ImFont* general_icon = nullptr;
ImFont* abys = nullptr;
ImFont* rubik = nullptr;
ImFont* rubik_input = nullptr;
ImFont* Reem_font = nullptr;
ImFont* sans = nullptr;

int tabs = 0, tab_count = 0, tab_menu = 0;
int general_tab = tab_menu;

int animation_tab = 255;
bool active_tab = false;

//picture in
IDirect3DTexture9* picture_0 = nullptr;
IDirect3DTexture9* picture_1 = nullptr;

static bool check_0 = false;
static bool check_1 = false;
static int slider_0 = 1850;
static int slider_1 = 1850;
static int key0, m0 = 1;
static bool multi_items_count[5];
const char* multi_items[6] = { "One", "Two", "Three", "Four", "Five", "Six" };
static bool check_2 = false;
static int selectedItem1 = 0;
static const char* items1[]{ "100mc", "250mc", "500mc", "1000mc", "10.000mc" };
static int key1, m1 = 1;
static float slider_2 = 1.f;
static float slider_3 = 1.f;
static bool check_3 = false;
static bool check_4 = false;
static float slider_4 = 0.f;
static float slider_5 = 1.f;

float color_edit4[4] = { 1.00f, 1.00f, 1.00f, 1.000f };
float color_edit5[4] = { 0.30f, 0.30f, 1.00f, 1.000f };
float color_edit6[4] = { 0.70f, 0.00f, 0.00f, 1.000f };

// ׁמגלוסעםûו
float color_edit7[4] = { 0.20f, 0.20f, 0.50f, 1.000f };
static float slider_6 = 0.f;

static float slider_rotation = 0.f;

bool active_menu = false;
bool check_picker = false;
bool check_slider = false;
bool check_combo = false;

static const char* items2[]{ "One", "Two", "Three" };
static int selectedItem2 = 0;

int main(int, char**)
{

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX9 Example", WS_POPUP, 0, 0, 1920, 1060, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    rubik_input = io.Fonts->AddFontFromMemoryTTF(&rubik_font_medium, sizeof rubik_font_medium, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 17, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 23, NULL, io.Fonts->GetGlyphRangesCyrillic());

    tab_ico_two = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 33, NULL, io.Fonts->GetGlyphRangesCyrillic());

    general_icon = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    Reem_font = io.Fonts->AddFontFromMemoryTTF(&Reem, sizeof Reem, 45, NULL, io.Fonts->GetGlyphRangesCyrillic());

    sans = io.Fonts->AddFontFromMemoryTTF(&open_sans, sizeof open_sans, 28, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {

        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        DWORD window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {

            const auto& p = ImGui::GetWindowPos();
            ImGui::GetBackgroundDrawList()->AddImage(picture_1, ImVec2(-90 + p.x, -90 + p.y), ImVec2(1920 + p.x, 1080 + p.y), ImVec2(0 + p.x, 0 + p.y), ImVec2(1 + p.x, 1 + p.y), ImColor(60, 60, 225, 255));

            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);

            ImGui::SetNextWindowSize(ImVec2(1000, 627));

            ImGui::Begin("Hello, world!", &active_menu, window_flags);
            {

                ImVec2 P1, P2;
                ImDrawList* pDrawList;
                const auto& p = ImGui::GetWindowPos();
                const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
                const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

                ImGuiStyle* style = &ImGui::GetStyle();

                if (picture_1 == nullptr) D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &general, sizeof(general), 1920, 1080, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &picture_1);

                if (picture_0 == nullptr) D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &menu_background, sizeof(menu_background), 616, 549, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &picture_0);

                ImGui::GetWindowDrawList()->AddImage(picture_0, ImVec2(390 + p.x, 80 + p.y), ImVec2(1006 + p.x, 629 + p.y), ImVec2(0 + p.x, 0 + p.y), ImVec2(1 + p.x, 1 + p.y), ImColor(120, 120, 220, 10));

                pWindowDrawList->AddRectFilled(ImVec2(0.000f + p.x, 0.000f + p.y), ImVec2(94 + p.x, 627 + p.y), ImColor(35, 36, 40, 255), 6, ImDrawFlags_RoundCornersLeft); // bar line

                if (ImGui::TextButton("U", "##0", ImVec2(35, 35), ImVec2(932, 26)));

                pWindowDrawList->AddRectFilled(ImVec2(930.000f + p.x, 35.000f + p.y), ImVec2(930.000f + p.x, 48.000f + p.y), ImColor(45, 46, 50, 255), 10); // bar line

                pWindowDrawList->AddCircleFilled(ImVec2(890.000f + p.x, 42.000f + p.y), 19, ImColor(45, 46, 50, 255), 100); // bar line

                pForegroundDrawList->AddText(rubik, 23.f, ImVec2(885.000f + p.x, 30.000f + p.y), ImColor(188, 191, 198, 255), "?");

                ImGui::SetCursorPos(ImVec2(710, 23));

                ImGui::PushItemWidth(150);

                static char search_bar[65] = { "" };
                ImGui::InputText("L", search_bar, 65);

                if (!search_bar[0]) pWindowDrawList->AddText(rubik_input, 20.f, ImVec2(718.000f + p.x, 32.000f + p.y), ImColor(188, 191, 198, 255), "Search");

                ImGui::PopItemWidth();

                ImGui::SetCursorPos(ImVec2(0, 90));

                ImGui::BeginGroup();

                if (ImGui::Tab("A", 0 == tabs, ImVec2(45, 45)) && tabs != 0) {
                    active_tab = true;
                    tabs = 0;
                };

                if (ImGui::Tab("B", 1 == tabs, ImVec2(45, 45)) && tabs != 1) {
                    active_tab = true;
                    tabs = 1;
                };

                if (ImGui::Tab("C", 2 == tabs, ImVec2(45, 45)) && tabs != 2) {
                    active_tab = true;
                    tabs = 2;
                };

                if (ImGui::Tab("D", 3 == tabs, ImVec2(45, 45)) && tabs != 3) {
                    active_tab = true;
                    tabs = 3;
                };

                if (ImGui::Tab("E", 4 == tabs, ImVec2(45, 45)) && tabs != 4) {
                    active_tab = true;
                    tabs = 4;
                };

                if (ImGui::Tab("F", 5 == tabs, ImVec2(45, 45)) && tabs != 5) {
                    active_tab = true;
                    tabs = 5;
                };

                ImGui::EndGroup();

                if (active_tab) {
                    if (animation_tab < 255) {
                        animation_tab += 10 / ImGui::GetIO().Framerate * 120.f;
                    }
                    else {
                        active_tab = false;
                        tab_menu = tabs;
                    }
                }
                else {
                    if (animation_tab > 0) animation_tab -= 10 / ImGui::GetIO().Framerate * 120.f;
                }

                pForegroundDrawList->AddRectFilled(ImVec2(97.000f + p.x, 80.000f + p.y), ImVec2(1000.000f + p.x, 627.000f + p.y), ImColor(27 / 255.f, 28 / 255.f, 30 / 255.f, animation_tab / 255.f), 10); // bar line

                switch (tab_menu) {
                case 0:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "AimBot");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "Improvements in shooting.");
                    break;

                case 1:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "Movement");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "Your middle name is Flash.");
                    break;

                case 2:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "Profile");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "Setting up Your Profile.");
                    break;

                case 3:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "Visual");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "Your eyes will become smarter.");
                    break;

                case 4:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "Miscellaneous");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "About everything.");
                    break;

                case 5:
                    pWindowDrawList->AddText(Reem_font, 45.f, ImVec2(120.000f + p.x, 15.000f + p.y), ImColor(255, 255, 255, 255 - animation_tab), "Settings");
                    pWindowDrawList->AddText(sans, 28.f, ImVec2(120.000f + p.x, 57.000f + p.y), ImColor(215, 215, 215, 215 - animation_tab), "Full menu settings.");
                    break;
                }

                ImGui::BeginChild("0", ImVec2(880, 507), ImVec2(115, 120));

                switch (tab_menu) {

                case 0:

                    ImGui::Checkbox("Bounding box", &check_0);

                    ImGui::SameLine();

                    ImGui::ColorEdit4("##0", (float*)&color_edit5, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                    ImGui::Checkbox("Snap lines", &check_1);

                    ImGui::SliderInt("Max. Distance", &slider_0, 1, 2350);

                    ImGui::SliderInt("Max. Accent", &slider_1, 1, 1000);

                    ImGui::Keybind("HotKey", &key0, &m0);

                    ImGui::MultiCombo("Multicombo", multi_items_count, multi_items, 6);

                    ImGui::Checkbox("Crosshair", &check_2);

                    ImGui::Combo("Trigger delayed", &selectedItem1, items1, IM_ARRAYSIZE(items1), 5);

                    ImGui::Keybind("ESP box", &key1, &m1);

                    ImGui::SliderFloat("ESP. Weight", &slider_2, 0.5f, 2.f, "%.2f");

                    ImGui::SliderFloat("ESP. Height", &slider_3, 0.5f, 2.f, "%.2f");

                    break;

                case 1:

                    ImGui::Checkbox("Motion blur", &check_3);

                    ImGui::SameLine();

                    ImGui::ColorEdit4("##1", (float*)&color_edit6, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                    ImGui::Checkbox("Rotation", &check_4);

                    ImGui::SameLine();

                    ImGui::SliderFloat("##0", &slider_rotation, -180.0f, 180.0f, "%.1f");

                    ImGui::SliderFloat("Max. Weight", &slider_4, 0.0f, 0.5f, "%.1f");

                    ImGui::SliderFloat("Max. Height", &slider_5, 0.0f, 0.5f, "%.1f");

                    ImGui::ColorEdit4("Color Picker", (float*)&color_edit4, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

                    break;

                case 2:

                    ImGui::Checkbox("CheckBox & Picker", &check_picker);

                    ImGui::SameLine();

                    ImGui::ColorEdit4("##0", (float*)&color_edit7, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

                    ImGui::Checkbox("CheckBox & Slider", &check_slider);

                    ImGui::SameLine();

                    ImGui::SliderFloat("##1", &slider_6, 0.0f, 100.0f);

                    ImGui::Checkbox("CheckBox & Combo", &check_combo);

                    ImGui::SameLine();

                    ImGui::Combo("##2", &selectedItem2, items2, IM_ARRAYSIZE(items2), 5);

                    break;

                case 5:

                    for (int i = 0; i < 7; i++)
                        ImGui::ConfigList("Config", "0", true);

                    break;

                }

                ImGui::Spacing();

                ImGui::EndChild();

            }
            ImGui::End();

        }

        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
