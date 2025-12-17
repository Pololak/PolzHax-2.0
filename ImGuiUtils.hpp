#pragma once
#include <string>
#include <imgui/imgui.h>
#include <string_view>

enum ItemLabelFlags {
	Left = 1u << 0u,
	Right = 1u << 1u,
	Default = Left,
};

namespace ImGui {
	IMGUI_API bool HotKey(const char* label, int& key, float samelineOffset = 0.f, const ImVec2& size = ImVec2(100.f, 0.f), const char* placeholder = "...");

	IMGUI_API void ItemLabel(std::string_view title, ItemLabelFlags flags);
}