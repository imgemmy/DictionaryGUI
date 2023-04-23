#include "DictionaryUI.h"
#include <iostream>
#include <string>
#include "ColorStyles.h"
#include "Fonts.h"
#include "Requests.h"
#include "ImGUICustomFunctions.h"

DictionaryUI dictionaryGUI;

void DictionaryUI::Render()
{
	ImGui::BeginChild("##dictionary-ui", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false, 0);
	{
		//Search Bar
		ImGui::BeginChild("##search-bar", ImVec2(ImGui::GetContentRegionAvail().x, 60), false, 0);
		{
				//Search input
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorStyles::cambridgeGreen);
				ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(1, 1, 1, 0.411765));
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10,10));
				ImGui::SetNextItemWidth(350.f);
				ImGui::PushFont(Fonts::qs_bold32);
				{	
					ImGui::InputText("##dictionary-input", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_CharsNoBlank);
					if (buf[0] == 0) SetDefaultText("Enter a word");
				}
				ImGui::PopFont();
				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor(2);

				ImGui::SameLine();

				//Search Button
				ImGui::PushStyleColor(ImGuiCol_Button, ColorStyles::cambridgeGreen);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ColorStyles::cambridgeGreenHovered);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ColorStyles::cambridgeGreen);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 12));
				{
					if (ImGui::ArrowButton("btn", ImGuiDir_Right))
					{
						Requests::clearData();
						requestData.word = buf;
						Requests::sendRequest();
						
					}
				}
				ImGui::PopStyleColor(3);
				ImGui::PopStyleVar(2);

		}
		ImGui::EndChild();

		//Reponse
		if (requestData.hasData)
		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ColorStyles::cambridgeGreen);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20,20));
			ImGui::BeginChild("##response", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
			{
				//Word Response
				{
					ImGui::PushFont(Fonts::qs_regular28);
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
					ImGui::PushStyleColor(ImGuiCol_Button, ColorStyles::cambridgeGreenHovered);
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ColorStyles::cambridgeGreenHovered);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ColorStyles::cambridgeGreenHovered);
					{
						std::string word = "'" + requestData.rWord + "'";
						ImGui::Button(word.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 50));
					}
					ImGui::PopStyleVar(2);
					ImGui::PopStyleColor(3);
					ImGui::PopFont();
				}

				//Meanings Response
				{
					int index = 0;
					for (std::string partOfSpeech : requestData.rPartOfSpeech)
					{
						//Part of Speech
						ImGui::PushFont(Fonts::qs_bold24);
						{
							ImGui::TextWrapped(partOfSpeech.c_str());
						}
						ImGui::PopFont();

						//Definitions
						ImGui::PushFont(Fonts::qs_regular18);
						{
							if (index < requestData.rDefinitions.size()) {
								ImGui::TextWrapped(requestData.rDefinitions[index].c_str());
							}
						}
						ImGui::PopFont();


						//Synonym & Antonym
						ImGui::PushFont(Fonts::qs_regular18);
						{
							ImGui::TextWrapped("Synonyms: "); ImGui::SameLine(); ImGui::TextWrapped(requestData.rSynonyms[index].c_str());
							ImGui::TextWrapped("Antonyms: "); ImGui::SameLine(); ImGui::TextWrapped(requestData.rAntonyms[index].c_str());
						}
						ImGui::PopFont();

						//Incrementer for array index
						index++;
					}
				}
			}
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor();
			ImGui::EndChild();
		}

	}
	ImGui::EndChild();
}
