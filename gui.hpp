#pragma once

#include "clean_gui.hpp"


class Gui : CleanGui
{
private:
    //ImFont *font;
public:
    Gui();

    ~Gui();

    void renderFrame();

    bool isRunning() const;
};
