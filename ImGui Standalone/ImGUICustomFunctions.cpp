#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGUICustomFunctions.h"

void SetDefaultText(std::string text)
{
    ImGuiContext& g = *GImGui;
    ImVec2 txt_size = ImGui::CalcTextSize(text.c_str());
    ImColor col = ImGui::GetStyleColorVec4(ImGuiCol_Text);
    ImGui::GetWindowDrawList()->AddText({ g.LastItemData.NavRect.Min.x + g.Style.FramePadding.x, g.LastItemData.NavRect.Min.y + g.Style.FramePadding.y }, col, text.c_str());
}