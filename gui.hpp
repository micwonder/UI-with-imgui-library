#pragma once

#include <GLFW/glfw3.h>

#include "CleanGui.hpp"
#include "imgui.h"


class Gui : CleanGui
{
private:
    ImFont *font;

public:
    Gui();

    ~Gui();

    void renderFrame();

    bool isRunning() const;
};
