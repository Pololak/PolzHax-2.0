#include "pch.h"
#include "menu.h"

#include <imgui-hook.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include <filesystem>
#include <fstream>
#include <chrono>

#include "state.h"

#include "explorer.h"
#include "utils.hpp"
#include "patching.h"

DWORD libcocosbase = (DWORD)GetModuleHandleA("libcocos2d.dll");

ImVec4 color1;
ImVec4 color2;
ImVec4 color3;
ImVec4 color4;
ImVec4 color5;
ImVec4 color6;

bool oneX = true;

void imgui_render() {
	if (oneX) {
		setting().loadState();

		float polzhax_xPos;
		float bypass_xPos;
		float cosmetic_xPos;
		float creator_xPos;
		float level_xPos;
		float universal_xPos;

		if (ImGui::Begin("PolzHax", nullptr)) {
			ImGui::SetWindowPos({ 5,5 });
			polzhax_xPos = ImGui::GetWindowWidth() + 10;
		}

		if (ImGui::Begin("Bypass", nullptr)) {
			ImGui::SetWindowPos({ polzhax_xPos, 5 });
			bypass_xPos = polzhax_xPos + ImGui::GetWindowWidth() + 5;
		}

		if (ImGui::Begin("Cosmetic", nullptr)) {
			ImGui::SetWindowPos({ bypass_xPos, 5 });
			cosmetic_xPos = bypass_xPos + ImGui::GetWindowWidth() + 5;
		}

		if (ImGui::Begin("Creator", nullptr)) {
			ImGui::SetWindowPos({ cosmetic_xPos, 5 });
			creator_xPos = cosmetic_xPos + ImGui::GetWindowWidth() + 5;
		}

		if (ImGui::Begin("Level", nullptr)) {
			ImGui::SetWindowPos({ creator_xPos, 5 });
			level_xPos = creator_xPos + ImGui::GetWindowWidth() + 5;
		}

		// Bypass

		if (setting().onCharFilter) {
			sequence_patch((uint32_t)gd::base + 0x1e3d7, { 0x90, 0x75 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x1e3d7, { 0x75, 0x04 });
		}

		if (setting().onTheVault) {
			sequence_patch((uint32_t)gd::base + 0x1567fb, { 0xe9, 0x72, 0x01, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x1567fb, { 0x0f, 0x85, 0x71, 0x01, 0x00, 0x00 });
		}

		if (setting().onMainLevels) {
			sequence_patch((uint32_t)gd::base + 0x11510b, { 0xe9, 0xa7, 0x02, 0x00, 0x00, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x115b82, { 0xe9, 0x98, 0x00, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x11510b, { 0x0f, 0x84, 0xa6, 0x02, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0x115b82, { 0x0f, 0x8e, 0x97, 0x00, 0x00, 0x00 });
		}

		if (setting().onSliderLimit) {
			sequence_patch((uint32_t)gd::base + 0x2a567, { 0xeb, 0x07 });
			sequence_patch((uint32_t)gd::base + 0x2a57b, { 0xeb, 0x07 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x2a567, { 0x76, 0x07 });
			sequence_patch((uint32_t)gd::base + 0x2a57b, { 0x76, 0x07 });
		}

		if (setting().onTextLength) {
			sequence_patch((uint32_t)gd::base + 0x1e40e, { 0xeb, 0x04 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x1e40e, { 0x7c, 0x04 });
		}

		// Cosmetic

		if (setting().onNoDeathEffect) {
			sequence_patch((uint32_t)gd::base + 0x164c2d, { 0xe9, 0xe7, 0x01, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x164c2d, { 0x0f, 0x84, 0xd5, 0x01, 0x00, 0x00 });
		}

		if (setting().onNoRespawnFlash) {
			sequence_patch((uint32_t)gd::base + 0x1643a1, { 0xe9, 0x9f, 0x00, 0x00, 0x00, 0x00 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x1643a1, { 0x0f, 0x85, 0x9e, 0x00, 0x00, 0x00 });
		}

		if (setting().onPracticePulse) {
			sequence_patch((uint32_t)gd::base + 0x39805, { 0x90, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x176530, { 0x90, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x17655a, { 0xeb, 0x16 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x39805, { 0x75, 0x0c });
			sequence_patch((uint32_t)gd::base + 0x176530, { 0xeb, 0x1a });
			sequence_patch((uint32_t)gd::base + 0x17655a, { 0x74, 0x16 });
		}

		if (setting().onSolidWaveTrail) {
			sequence_patch((uint32_t)gd::base + 0x15f46b, { 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x15f46b, { 0x75, 0x0c });
		}

		if (setting().onTrailAlwaysOff) {
			sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0xe9, 0x56, 0x02, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0x0f, 0x84, 0x55, 0x02, 0x00, 0x00 });
		}

		if (setting().onTrailBugFix) {
			sequence_patch((uint32_t)libcocosbase + 0xad1ad, { 0xbb, 0xff, 0x00, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)libcocosbase + 0xad1ad, { 0xf3, 0x0f, 0x2c, 0xc1, 0x2b, 0xd8 });
		}

		// Creator

		if (setting().onAbsolutePosition) {
			sequence_patch((uint32_t)gd::base + 0x6e3bd, { 0x90, 0x8b, 0xce, 0x90, 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x6e3bd, { 0x51, 0x8b, 0xce, 0xff, 0x50, 0x5c });
		}

		if (setting().onCopyHack) {
			sequence_patch((uint32_t)gd::base + 0x10841f, { 0x8b, 0xce, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x1084b4, { 0xb0, 0x01, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x109620, { 0xeb, 0x18 });
			sequence_patch((uint32_t)gd::base + 0x10a079, { 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x10841f, { 0x0f, 0x44, 0xce });
			sequence_patch((uint32_t)gd::base + 0x1084b4, { 0x0f, 0x95, 0xc0 });
			sequence_patch((uint32_t)gd::base + 0x109620, { 0x74, 0x18 });
			sequence_patch((uint32_t)gd::base + 0x10a079, { 0x75, 0x11 });
		}

		if (setting().onCustomObjectBypass) {
			sequence_patch((uint32_t)gd::base + 0x607c1, { 0xeb, 0x7f });
			sequence_patch((uint32_t)gd::base + 0x608a3, { 0xe9, 0xaf, 0x00, 0x00, 0x00, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x609cf, { 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x607c1, { 0x76, 0x7f });
			sequence_patch((uint32_t)gd::base + 0x608a3, { 0x0f, 0x82, 0xae, 0x00, 0x00, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x609cf, { 0x74, 0x4f });
		}

		if (setting().onFreeScroll) {
			sequence_patch((uint32_t)gd::base + 0x6fe05, { 0xeb, 0x08 });
			sequence_patch((uint32_t)gd::base + 0x6fe1c, { 0xeb, 0x05 });
			sequence_patch((uint32_t)gd::base + 0x6fe35, { 0xeb, 0x08 });
			sequence_patch((uint32_t)gd::base + 0x6fe4c, { 0xeb, 0x05 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x6fe05, { 0x77, 0x08 });
			sequence_patch((uint32_t)gd::base + 0x6fe1c, { 0x77, 0x05 });
			sequence_patch((uint32_t)gd::base + 0x6fe35, { 0x77, 0x08 });
			sequence_patch((uint32_t)gd::base + 0x6fe4c, { 0x77, 0x05 });
		}

		if (setting().onLevelEdit) {
			sequence_patch((uint32_t)gd::base + 0x15baaf, { 0x90, 0x90 });
			sequence_patch((uint32_t)gd::base + 0x75757, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x15baaf, { 0x75, 0x62 });
			sequence_patch((uint32_t)gd::base + 0x75757, { 0x0f, 0x85, 0xca, 0x00, 0x00, 0x00 });
		}

		if (setting().onNoCMark) {
			sequence_patch((uint32_t)gd::base + 0x7d0e0, { 0xb8, 0x00, 0x00, 0x00, 0x00, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x7d0e0, { 0x8b, 0x81, 0x18, 0x02, 0x00, 0x00 });
		}

		if (setting().onObjectBypass) {
			sequence_patch((uint32_t)gd::base + 0x5a727, { 0x68, 0xff, 0xff, 0xff, 0x7f });
			sequence_patch((uint32_t)gd::base + 0x69902, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
			sequence_patch((uint32_t)gd::base + 0x6b895, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
			sequence_patch((uint32_t)gd::base + 0x6bbf9, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
			sequence_patch((uint32_t)gd::base + 0xef1af, { 0xff, 0xff, 0xff, 0x7f });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x5a727, { 0x68, 0x30, 0x75, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0x69902, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0x6b895, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0x6bbf9, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xef1af, { 0x30, 0x75, 0x00, 0x00 });
		}

		if (setting().onScaleSnapBypass) {
			sequence_patch((uint32_t)gd::base + 0x74869, { 0xeb, 0x26 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x74869, { 0x76, 0x26 });
		}

		if (setting().onSmoothTrail) {
			sequence_patch((uint32_t)gd::base + 0xfbd31, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0xfbd31, { 0x0f, 0x82, 0x7f, 0x00, 0x00, 0x00 });
		}

		if (setting().onToolboxBypass) {
			sequence_patch((uint32_t)gd::base + 0xd9f3b, { 0x83, 0xf9, 0x01 });
			sequence_patch((uint32_t)gd::base + 0xd9f40, { 0x83, 0xf9, 0x7f });
			sequence_patch((uint32_t)gd::base + 0xd9f45, { 0xb9, 0x7f, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9f4c, { 0xb8, 0x01, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9fcb, { 0x83, 0xf9, 0x01 });
			sequence_patch((uint32_t)gd::base + 0xd9fd0, { 0x83, 0xf9, 0x7f });
			sequence_patch((uint32_t)gd::base + 0xd9fd5, { 0xb9, 0x7f, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9fdc, { 0xb8, 0x01, 0x00, 0x00, 0x00 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0xd9f3b, { 0x83, 0xf9, 0x06 });
			sequence_patch((uint32_t)gd::base + 0xd9f40, { 0x83, 0xf9, 0x0c });
			sequence_patch((uint32_t)gd::base + 0xd9f45, { 0xb9, 0x0c, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9f4c, { 0xb8, 0x06, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9fcb, { 0x83, 0xf9, 0x02 });
			sequence_patch((uint32_t)gd::base + 0xd9fd0, { 0x83, 0xf9, 0x03 });
			sequence_patch((uint32_t)gd::base + 0xd9fd5, { 0xb9, 0x03, 0x00, 0x00, 0x00 });
			sequence_patch((uint32_t)gd::base + 0xd9fdc, { 0xb8, 0x02, 0x00, 0x00, 0x00 });
		}

		if (setting().onVerifyHack) {
			sequence_patch((uint32_t)gd::base + 0x594e5, { 0xeb, 0x49 });
		}
		else {
			sequence_patch((uint32_t)gd::base + 0x594e5, { 0x75, 0x49 });
		}

		auto* colors = ImGui::GetStyle().Colors;

		color1.x = setting().Overlaycolor[0];
		color1.y = setting().Overlaycolor[1];
		color1.z = setting().Overlaycolor[2];
		color1.w = setting().Overlaycolor[3] - 0.4;

		color2.x = setting().Overlaycolor[0];
		color2.y = setting().Overlaycolor[1];
		color2.z = setting().Overlaycolor[2];
		color2.w = 1;

		color3.x = setting().Overlaycolor[0] + 0.3;
		color3.y = setting().Overlaycolor[1] + 0.3;
		color3.z = setting().Overlaycolor[2] + 0.3;
		color3.w = setting().Overlaycolor[3] + 0.3;

		color4.x = setting().Overlaycolor[0] - 0.1;
		color4.y = setting().Overlaycolor[1] - 0.1;
		color4.z = setting().Overlaycolor[2] - 0.1;
		color4.w = setting().Overlaycolor[3] - 0.1;

		color5.x = setting().Overlaycolor[0] + 0.1;
		color5.y = setting().Overlaycolor[1] + 0.1;
		color5.z = setting().Overlaycolor[2] + 0.1;
		color5.w = setting().Overlaycolor[3] + 0.1;

		color6.x = setting().BGcolor[0];
		color6.y = setting().BGcolor[1];
		color6.z = setting().BGcolor[2];
		color6.w = setting().BGcolor[3];

		//colors[ImGuiCol_Text] = ImVec4(1, 0, 0, 1);
		colors[ImGuiCol_WindowBg] = color6;
		colors[ImGuiCol_Border] = color2;
		colors[ImGuiCol_BorderShadow] = color2;
		colors[ImGuiCol_Button] = color3;
		colors[ImGuiCol_ButtonHovered] = color1;
		colors[ImGuiCol_ButtonActive] = color1;
		colors[ImGuiCol_CheckMark] = ImVec4(1, 1, 1, 1);
		colors[ImGuiCol_FrameBg] = color1;
		colors[ImGuiCol_FrameBgHovered] = color3;
		colors[ImGuiCol_FrameBgActive] = color3;
		colors[ImGuiCol_Tab] = ImVec4(color5.x, color5.y, color5.z, color5.w - 0.2);
		colors[ImGuiCol_TabHovered] = color3;
		colors[ImGuiCol_TabActive] = color3;
		colors[ImGuiCol_TitleBg] = color3;
		colors[ImGuiCol_TitleBgActive] = color3;
		colors[ImGuiCol_TitleBgCollapsed] = color3;
		colors[ImGuiCol_SliderGrab] = color4;
		colors[ImGuiCol_SliderGrabActive] = color4;
		colors[ImGuiCol_TextSelectedBg] = color2;
		colors[ImGuiCol_Header] = color1;
		colors[ImGuiCol_HeaderHovered] = color1;
		colors[ImGuiCol_HeaderActive] = color2;
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0);

		oneX = false;
	}

	if (setting().show) {
		if (setting().explorer) {
			render_explorer_window(setting().explorer);
		}

		if (ImGui::Begin("PolzHax", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)); {
			ImGui::SetWindowFontScale(setting().UISize);

			ImGui::Text("2.011 - v1.0.0");

			ImGui::Checkbox("Auto Save", &setting().onAutoSave);
			ImGui::SameLine();
			if (ImGui::Button("Save"))
				setting().saveState();

			if (ImGui::Button("Cocos Explorer")) {
				setting().explorer = !setting().explorer;
			}

			if (ImGui::Button("Sort Tabs")) {
				float polzhax_xPos;
				float bypass_xPos;
				float cosmetic_xPos;
				float creator_xPos;
				float level_xPos;
				float universal_xPos;

				if (ImGui::Begin("PolzHax", nullptr)) {
					ImGui::SetWindowPos({ 5,5 });
					polzhax_xPos = ImGui::GetWindowWidth() + 10;
				}

				if (ImGui::Begin("Bypass", nullptr)) {
					ImGui::SetWindowPos({ polzhax_xPos, 5 });
					bypass_xPos = polzhax_xPos + ImGui::GetWindowWidth() + 5;
				}

				if (ImGui::Begin("Cosmetic", nullptr)) {
					ImGui::SetWindowPos({ bypass_xPos, 5 });
					cosmetic_xPos = bypass_xPos + ImGui::GetWindowWidth() + 5;
				}

				if (ImGui::Begin("Creator", nullptr)) {
					ImGui::SetWindowPos({ cosmetic_xPos, 5 });
					creator_xPos = cosmetic_xPos + ImGui::GetWindowWidth() + 5;
				}

				if (ImGui::Begin("Level", nullptr)) {
					ImGui::SetWindowPos({ creator_xPos, 5 });
					level_xPos = creator_xPos + ImGui::GetWindowWidth() + 5;
				}
			}
		}

		if (ImGui::Begin("Bypass", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)); {
			ImGui::SetWindowFontScale(setting().UISize);

			if (ImGui::Checkbox("Character Filter", &setting().onCharFilter)) {
				if (setting().onCharFilter) {
					sequence_patch((uint32_t)gd::base + 0x1e3d7, { 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x1e3d7, { 0x75, 0x04 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Lets you input any character in text fields.");

			if (ImGui::Checkbox("Guard Vault", &setting().onTheVault)) {
				if (setting().onTheVault) {
					sequence_patch((uint32_t)gd::base + 0x1567fb, { 0xe9, 0x72, 0x01, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x1567fb, { 0x0f, 0x85, 0x71, 0x01, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Unlocks the guard's vault.");

			ImGui::Checkbox("Icons", &setting().onIcons);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Unlocks all icons and colors.");

			if (ImGui::Checkbox("Main Levels", &setting().onMainLevels)) {
				if (setting().onMainLevels) {
					sequence_patch((uint32_t)gd::base + 0x11510b, { 0xe9, 0xa7, 0x02, 0x00, 0x00, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x115b82, { 0xe9, 0x98, 0x00, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x11510b, { 0x0f, 0x84, 0xa6, 0x02, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x115b82, { 0x0f, 0x8e, 0x97, 0x00, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Unlocks main demon levels.");

			if (ImGui::Checkbox("Slider Limit", &setting().onSliderLimit)) {
				if (setting().onSliderLimit) {
					sequence_patch((uint32_t)gd::base + 0x2a567, { 0xeb, 0x07 });
					sequence_patch((uint32_t)gd::base + 0x2a57b, { 0xeb, 0x07 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x2a567, { 0x76, 0x07 });
					sequence_patch((uint32_t)gd::base + 0x2a57b, { 0x76, 0x07 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Lets sliders be dragged beyond the visible limit.");

			if (ImGui::Checkbox("Text Length", &setting().onTextLength)) {
				if (setting().onTextLength) {
					sequence_patch((uint32_t)gd::base + 0x1e40e, { 0xeb, 0x04 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x1e40e, { 0x7c, 0x04 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Allows for unlimited text length in text inputs.");
		}

		if (ImGui::Begin("Cosmetic", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)); {
			ImGui::SetWindowFontScale(setting().UISize);

			ImGui::Checkbox("Hide Attempts", &setting().onHideAttempts);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Hides the attemps counter in-game.");

			ImGui::Checkbox("Hide Pause Button", &setting().onHidePauseButton);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Hides the pause button when the in-game cursor is enabled.");

			if (ImGui::Checkbox("Hide Pause Menu", &setting().onHidePauseMenu)) {
				if (layers().PauseLayerObject)
				{
					if (setting().onHidePauseMenu) layers().PauseLayerObject->setVisible(0);
					else layers().PauseLayerObject->setVisible(1);
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Hides the pause menu.");

			ImGui::Checkbox("Hide Practice Buttons", &setting().onHidePracticeButtons);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Hides practice buttons.");

			if (ImGui::Checkbox("No Death Effect", &setting().onNoDeathEffect)) {
				if (setting().onNoDeathEffect) {
					sequence_patch((uint32_t)gd::base + 0x164c2d, { 0xe9, 0xe7, 0x01, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x164c2d, { 0x0f, 0x84, 0xd5, 0x01, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("No visual effects on death.");

			ImGui::Checkbox("No Mini Icon", &setting().onNoMiniIcon);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Replaces default mini icon with normal one.");

			ImGui::Checkbox("No Particles", &setting().onNoParticles);
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Disables the particle system.");

			if (ImGui::Checkbox("No Respawn Flash", &setting().onNoRespawnFlash)) {
				if (setting().onNoRespawnFlash) {
					sequence_patch((uint32_t)gd::base + 0x1643a1, { 0xe9, 0x9f, 0x00, 0x00, 0x00, 0x00 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x1643a1, { 0x0f, 0x85, 0x9e, 0x00, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Disables the respawn flash & circle effect.");

			if (ImGui::Checkbox("Practice Pulse", &setting().onPracticePulse)) {
				if (setting().onPracticePulse) {
					sequence_patch((uint32_t)gd::base + 0x39805, { 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x176530, { 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x17655a, { 0xeb, 0x16 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x39805, { 0x75, 0x0c });
					sequence_patch((uint32_t)gd::base + 0x176530, { 0xeb, 0x1a });
					sequence_patch((uint32_t)gd::base + 0x17655a, { 0x74, 0x16 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Pulses orbs & wave in practice mode.");

			if (ImGui::Checkbox("Solid Wave Trail", &setting().onSolidWaveTrail)) {
				if (setting().onSolidWaveTrail) {
					sequence_patch((uint32_t)gd::base + 0x15f46b, { 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x15f46b, { 0x75, 0x0c });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("No blending on the wave trail.");

			if (ImGui::Checkbox("Trail Always Off", &setting().onTrailAlwaysOff)) {
				if (setting().onTrailAlwaysOff) {
					sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0xe9, 0x56, 0x02, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0x0f, 0x84, 0x55, 0x02, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Forces player trail to be always off.");

			if (ImGui::Checkbox("Trail Always On", &setting().onTrailAlwaysOn)) {
				if (setting().onTrailAlwaysOn) {
					sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)libcocosbase + 0xad5b6, { 0x0f, 0x84, 0x55, 0x02, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Forces player trail to be always on.");

			if (ImGui::Checkbox("Trail Bug Fix", &setting().onTrailBugFix)) {
				if (setting().onTrailBugFix) {
					sequence_patch((uint32_t)libcocosbase + 0xad1ad, { 0xbb, 0xff, 0x00, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)libcocosbase + 0xad1ad, { 0xf3, 0x0f, 0x2c, 0xc1, 0x2b, 0xd8 });
				}
			}
		}

		if (ImGui::Begin("Creator", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)); {
			ImGui::SetWindowFontScale(setting().UISize);

			if (ImGui::Checkbox("Absolute Position", &setting().onAbsolutePosition)) {
				if (setting().onAbsolutePosition) {
					sequence_patch((uint32_t)gd::base + 0x6e3bd, { 0x90, 0x8b, 0xce, 0x90, 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x6e3bd, { 0x51, 0x8b, 0xce, 0xff, 0x50, 0x5c });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Locks block position for rotation.");

			if (ImGui::Checkbox("Copy Hack", &setting().onCopyHack)) {
				if (setting().onCopyHack) {
					sequence_patch((uint32_t)gd::base + 0x10841f, { 0x8b, 0xce, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x1084b4, { 0xb0, 0x01, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x109620, { 0xeb, 0x18 });
					sequence_patch((uint32_t)gd::base + 0x10a079, { 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x10841f, { 0x0f, 0x44, 0xce });
					sequence_patch((uint32_t)gd::base + 0x1084b4, { 0x0f, 0x95, 0xc0 });
					sequence_patch((uint32_t)gd::base + 0x109620, { 0x74, 0x18 });
					sequence_patch((uint32_t)gd::base + 0x10a079, { 0x75, 0x11 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Lets you copy any level, without a password.");

			if (ImGui::Checkbox("Custom Object Bypass", &setting().onCustomObjectBypass)) {
				if (setting().onCustomObjectBypass) {
					sequence_patch((uint32_t)gd::base + 0x607c1, { 0xeb, 0x7f });
					sequence_patch((uint32_t)gd::base + 0x608a3, { 0xe9, 0xaf, 0x00, 0x00, 0x00, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x609cf, { 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x607c1, { 0x76, 0x7f });
					sequence_patch((uint32_t)gd::base + 0x608a3, { 0x0f, 0x82, 0xae, 0x00, 0x00, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x609cf, { 0x74, 0x4f });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Removes the object limit for custom objects & lets you save over 100.");

			if (ImGui::Checkbox("Free Scroll", &setting().onFreeScroll)) {
				if (setting().onFreeScroll) {
					sequence_patch((uint32_t)gd::base + 0x6fe05, { 0xeb, 0x08 });
					sequence_patch((uint32_t)gd::base + 0x6fe1c, { 0xeb, 0x05 });
					sequence_patch((uint32_t)gd::base + 0x6fe35, { 0xeb, 0x08 });
					sequence_patch((uint32_t)gd::base + 0x6fe4c, { 0xeb, 0x05 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x6fe05, { 0x77, 0x08 });
					sequence_patch((uint32_t)gd::base + 0x6fe1c, { 0x77, 0x05 });
					sequence_patch((uint32_t)gd::base + 0x6fe35, { 0x77, 0x08 });
					sequence_patch((uint32_t)gd::base + 0x6fe4c, { 0x77, 0x05 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Allows you to scroll out the editor.");

			if (ImGui::Checkbox("Level Edit", &setting().onLevelEdit)) {
				if (setting().onLevelEdit) {
					sequence_patch((uint32_t)gd::base + 0x15baaf, { 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x75757, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x15baaf, { 0x75, 0x62 });
					sequence_patch((uint32_t)gd::base + 0x75757, { 0x0f, 0x85, 0xca, 0x00, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Lets you edit any level through the pause menu.");

			if (ImGui::Checkbox("No (C) Mark", &setting().onNoCMark)) {
				if (setting().onNoCMark) {
					sequence_patch((uint32_t)gd::base + 0x7d0e0, { 0xb8, 0x00, 0x00, 0x00, 0x00, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x7d0e0, { 0x8b, 0x81, 0x18, 0x02, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Removes the (C) mark when uploading copied levels.");

			if (ImGui::Checkbox("Object Bypass", &setting().onObjectBypass)) {
				if (setting().onObjectBypass) {
					sequence_patch((uint32_t)gd::base + 0x5a727, { 0x68, 0xff, 0xff, 0xff, 0x7f });
					sequence_patch((uint32_t)gd::base + 0x69902, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
					sequence_patch((uint32_t)gd::base + 0x6b895, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
					sequence_patch((uint32_t)gd::base + 0x6bbf9, { 0x3d, 0xff, 0xff, 0xff, 0x7f });
					sequence_patch((uint32_t)gd::base + 0xef1af, { 0xff, 0xff, 0xff, 0x7f });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x5a727, { 0x68, 0x30, 0x75, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x69902, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x6b895, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x6bbf9, { 0x3d, 0x30, 0x75, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xef1af, { 0x30, 0x75, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Uncaps the object limit.");

			if (ImGui::Checkbox("Scale Snap Bypass", &setting().onScaleSnapBypass)) {
				if (setting().onScaleSnapBypass) {
					sequence_patch((uint32_t)gd::base + 0x74869, { 0xeb, 0x26 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x74869, { 0x76, 0x26 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Removed snapping to 1.00 when moving the scale slider between 0.97 and 1.03.");

			if (ImGui::Checkbox("Smooth Trail", &setting().onSmoothTrail)) {
				if (setting().onSmoothTrail) {
					sequence_patch((uint32_t)gd::base + 0xfbd31, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0xfbd31, { 0x0f, 0x82, 0x7f, 0x00, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Makes the playtest line in the editor smoother by updating it every frame instead of at 30fps.");


			if (ImGui::Checkbox("Toolbox Button Bypass", &setting().onToolboxBypass)) {
				if (setting().onToolboxBypass) {
					sequence_patch((uint32_t)gd::base + 0xd9f3b, { 0x83, 0xf9, 0x01 });
					sequence_patch((uint32_t)gd::base + 0xd9f40, { 0x83, 0xf9, 0x7f });
					sequence_patch((uint32_t)gd::base + 0xd9f45, { 0xb9, 0x7f, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9f4c, { 0xb8, 0x01, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9fcb, { 0x83, 0xf9, 0x01 });
					sequence_patch((uint32_t)gd::base + 0xd9fd0, { 0x83, 0xf9, 0x7f });
					sequence_patch((uint32_t)gd::base + 0xd9fd5, { 0xb9, 0x7f, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9fdc, { 0xb8, 0x01, 0x00, 0x00, 0x00 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0xd9f3b, { 0x83, 0xf9, 0x06 });
					sequence_patch((uint32_t)gd::base + 0xd9f40, { 0x83, 0xf9, 0x0c });
					sequence_patch((uint32_t)gd::base + 0xd9f45, { 0xb9, 0x0c, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9f4c, { 0xb8, 0x06, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9fcb, { 0x83, 0xf9, 0x02 });
					sequence_patch((uint32_t)gd::base + 0xd9fd0, { 0x83, 0xf9, 0x03 });
					sequence_patch((uint32_t)gd::base + 0xd9fd5, { 0xb9, 0x03, 0x00, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0xd9fdc, { 0xb8, 0x02, 0x00, 0x00, 0x00 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Allows for more objects in the editor toolbox.");

			if (ImGui::Checkbox("Verify Hack", &setting().onVerifyHack)) {
				if (setting().onVerifyHack) {
					sequence_patch((uint32_t)gd::base + 0x594e5, { 0xeb, 0x49 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x594e5, { 0x75, 0x49 });
				}
			}
			if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.5f)
				ImGui::SetTooltip("Lets you upload unverified levels.");
		}

		if (ImGui::Begin("Level", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)); {
			ImGui::SetWindowFontScale(setting().UISize);

			ImGui::Checkbox("Ball Rotation Bug Fix", &setting().onBallRotatingBugFix);

			if (ImGui::Checkbox("Confirm Exit", &setting().onConfirmExit)) {
				if (setting().onConfirmExit) {
					sequence_patch((uint32_t)gd::base + 0x15d670, { 0x90, 0x90, 0x90, 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x15d67d, { 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x15d68d, { 0x90, 0x90, 0x90, 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x15d695, { 0x90, 0x90, 0x90, 0x90, 0x90 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x15d670, { 0xe8, 0x0b, 0x08, 0x02, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x15d67d, { 0x6a, 0x10 });
					sequence_patch((uint32_t)gd::base + 0x15d68d, { 0x68, 0x4c, 0x58, 0x5c, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x15d695, { 0xe8, 0x86, 0xe7, 0xea, 0xff });
				}
			}

			if (ImGui::Checkbox("Corrective Music Sync", &setting().onCorrectiveMusicSync)) {
				if (setting().onCorrectiveMusicSync) {
					sequence_patch((uint32_t)gd::base + 0x179cbe, { 0xeb, 0x08 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x179cbe, { 0x75, 0x08 });
				}
			}

			ImGui::Checkbox("Noclip", &setting().onNoclip);

			if (ImGui::Checkbox("Pause During Completion", &setting().onPauseDuringComplete)) {
				if (setting().onPauseDuringComplete) {
					sequence_patch((uint32_t)gd::base + 0x16a146, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
					sequence_patch((uint32_t)gd::base + 0x16c87a, { 0x00 });
				}
				else {
					sequence_patch((uint32_t)gd::base + 0x16a146, { 0x88, 0x81, 0x42, 0x03, 0x00, 0x00 });
					sequence_patch((uint32_t)gd::base + 0x16c87a, { 0x01 });
				}
			}

			ImGui::Checkbox("Practice Bug Fix", &setting().onPracticeBugFix);

			if (ImGui::Checkbox("Practice Music", &setting().onPracticeMusic)) {
				if (setting().onPracticeMusic) {

				}
				else {

				}
			}

			ImGui::Checkbox("Smart StartPos", &setting().onSmartStartPos);

			ImGui::Checkbox("StartPos Switcher", &setting().onStartPosSwitcher);
		}
	}
}

void imgui_init() {
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("Muli-SemiBold.ttf", 16.f);
	io.Fonts->Build();

	auto* colors = ImGui::GetStyle().Colors;

	color1.x = setting().Overlaycolor[0];
	color1.y = setting().Overlaycolor[1];
	color1.z = setting().Overlaycolor[2];
	color1.w = setting().Overlaycolor[3] - 0.4;

	color2.x = setting().Overlaycolor[0];
	color2.y = setting().Overlaycolor[1];
	color2.z = setting().Overlaycolor[2];
	color2.w = 1;

	color3.x = setting().Overlaycolor[0] + 0.3;
	color3.y = setting().Overlaycolor[1] + 0.3;
	color3.z = setting().Overlaycolor[2] + 0.3;
	color3.w = setting().Overlaycolor[3] + 0.3;

	color4.x = setting().Overlaycolor[0] - 0.1;
	color4.y = setting().Overlaycolor[1] - 0.1;
	color4.z = setting().Overlaycolor[2] - 0.1;
	color4.w = setting().Overlaycolor[3] - 0.1;

	color5.x = setting().Overlaycolor[0] + 0.1;
	color5.y = setting().Overlaycolor[1] + 0.1;
	color5.z = setting().Overlaycolor[2] + 0.1;
	color5.w = setting().Overlaycolor[3] + 0.1;

	color6.x = setting().BGcolor[0];
	color6.y = setting().BGcolor[1];
	color6.z = setting().BGcolor[2];
	color6.w = setting().BGcolor[3];

	//colors[ImGuiCol_Text] = ImVec4(1, 0, 0, 1);
	colors[ImGuiCol_WindowBg] = color6;
	colors[ImGuiCol_Border] = color2;
	colors[ImGuiCol_BorderShadow] = color2;
	colors[ImGuiCol_Button] = color3;
	colors[ImGuiCol_ButtonHovered] = color1;
	colors[ImGuiCol_ButtonActive] = color1;
	colors[ImGuiCol_CheckMark] = ImVec4(1, 1, 1, 1);
	colors[ImGuiCol_FrameBg] = color1;
	colors[ImGuiCol_FrameBgHovered] = color3;
	colors[ImGuiCol_FrameBgActive] = color3;
	colors[ImGuiCol_Tab] = ImVec4(color5.x, color5.y, color5.z, color5.w - 0.2);
	colors[ImGuiCol_TabHovered] = color3;
	colors[ImGuiCol_TabActive] = color3;
	colors[ImGuiCol_TitleBg] = color3;
	colors[ImGuiCol_TitleBgActive] = color3;
	colors[ImGuiCol_TitleBgCollapsed] = color3;
	colors[ImGuiCol_SliderGrab] = color4;
	colors[ImGuiCol_SliderGrabActive] = color4;
	colors[ImGuiCol_TextSelectedBg] = color2;
	colors[ImGuiCol_Header] = color1;
	colors[ImGuiCol_HeaderHovered] = color1;
	colors[ImGuiCol_HeaderActive] = color2;
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0);
}

void setup_imgui_menu() {
	ImGuiHook::setToggleCallback([]() {setting().show = !setting().show; });
	ImGuiHook::setRenderFunction(imgui_render);
	ImGuiHook::setInitFunction(imgui_init);
	ImGuiHook::setupHooks([](auto addr, auto hook, auto orig) {
		MH_CreateHook(addr, hook, orig);
		MH_EnableHook(addr);
		});
}