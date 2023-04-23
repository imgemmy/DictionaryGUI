#include "Drawing.h"
#include "DictionaryUI.h"
#include "ColorStyles.h"
#include "Fonts.h"

LPCSTR Drawing::lpWindowName = "DictionaryGUI";
ImVec2 Drawing::vWindowSize = { 600, 800 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

void Drawing::Draw()
{
	if (isActive())
	{
		//Debug metrics window
		#if defined _DEBUG
		ImGui::ShowMetricsWindow();
		#endif // DEBUG

		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ColorStyles::darkGrey);
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ColorStyles::cambridgeGreenHovered);
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ColorStyles::cambridgeGreenHovered);
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ColorStyles::cambridgeGreenHovered);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::PushFont(Fonts::qs_regular28);
		{
			ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
			{
				dictionaryGUI.Render();
			}
			ImGui::End();
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar();

	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
