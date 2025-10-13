#pragma once
#include <Windows.h>
#include <string>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>

class Overlay
{
public:

    void __cdecl Init();
    void __cdecl CreateCategory(const std::string& name);
};