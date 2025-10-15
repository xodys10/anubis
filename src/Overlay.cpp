#include "Overlay.hpp"

ImGuiContext* g_UIContext = nullptr;

void Overlay::Render()
{
	if (!g_UIContext) return;

	ImGuiContext* oldContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(g_UIContext);

	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

	if (ImGui::CollapsingHeader("test??"))
        ImGui::Text("i dotn think this wokrs");

	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::SetCurrentContext(oldContext);
}

void Overlay::Init(HWND hwnd)
{
	g_UIContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(g_UIContext);

	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

	ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init(nullptr);
	Render();
}

void Overlay::Shutdown()
{
	if (!g_UIContext) return;

	ImGuiContext* oldContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(g_UIContext);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext(g_UIContext);
	g_UIContext = nullptr;

	ImGui::SetCurrentContext(oldContext);
}
