#ifndef OPENGL_EDITORSTYLE_H
#define OPENGL_EDITORSTYLE_H

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"
#include "../../imgui/imgui_impl_glfw.h"
#include "../../imgui/imgui_impl_opengl3.h"

class EditorStyle {
    public:
            static void Apply() {
                ImGui::StyleColorsDark();
                auto& style = ImGui::GetStyle();

                const auto font_size	= 16.0f;
                const auto roundness	= 2.0f;

                const auto text						= ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
                const auto white					= ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                const auto black					= ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                const auto background_very_dark		= ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
                const auto background_dark			= ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
                const auto background_medium		= ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
                const auto background_light			= ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
                const auto highlight_blue			= ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
                const auto highlight_blue_hovered	= ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
                const auto highlight_blue_active	= ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
                const auto bar_background			= ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
                const auto bar						= ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
                const auto bar_hovered				= ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
                const auto bar_active				= ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

                // Spatial
                style.WindowBorderSize		= 1.0f;
                style.FrameBorderSize		= 0.0f;
                //style.WindowMinSize		= ImVec2(160, 20);
                style.FramePadding			= ImVec2(5, 5);
                style.ItemSpacing			= ImVec2(6, 5);
                //style.ItemInnerSpacing	= ImVec2(6, 4);
                style.Alpha					= 1.0f;
                style.WindowRounding		= roundness;
                style.FrameRounding			= roundness;
                style.PopupRounding			= roundness;
                //style.IndentSpacing		= 6.0f;
                //style.ItemInnerSpacing	= ImVec2(2, 4);
                //style.ColumnsMinSpacing	= 50.0f;
                //style.GrabMinSize			= 14.0f;
                style.GrabRounding			= roundness;
                style.ScrollbarSize			= 20.0f;
                style.ScrollbarRounding		= roundness;

                // Colors
                style.Colors[ImGuiCol_Text]						= text;
                //style.Colors[ImGuiCol_TextDisabled]			= ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
                style.Colors[ImGuiCol_WindowBg]					= background_dark;
                //style.Colors[ImGuiCol_ChildBg]				= ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
                style.Colors[ImGuiCol_Border]					= black;
                //style.Colors[ImGuiCol_BorderShadow]			= ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                style.Colors[ImGuiCol_FrameBg]					= bar;
                style.Colors[ImGuiCol_FrameBgHovered]			= highlight_blue;
                style.Colors[ImGuiCol_FrameBgActive]			= highlight_blue_hovered;
                style.Colors[ImGuiCol_TitleBg]					= background_very_dark;
                //style.Colors[ImGuiCol_TitleBgCollapsed]		= ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
                style.Colors[ImGuiCol_TitleBgActive]			= bar;
                style.Colors[ImGuiCol_MenuBarBg]				= background_very_dark;
                style.Colors[ImGuiCol_ScrollbarBg]				= bar_background;
                style.Colors[ImGuiCol_ScrollbarGrab]			= bar;
                style.Colors[ImGuiCol_ScrollbarGrabHovered]		= bar_hovered;
                style.Colors[ImGuiCol_ScrollbarGrabActive]		= bar_active;
                style.Colors[ImGuiCol_CheckMark]				= highlight_blue_hovered;
                style.Colors[ImGuiCol_SliderGrab]				= highlight_blue_hovered;
                style.Colors[ImGuiCol_SliderGrabActive]			= highlight_blue_active;
                style.Colors[ImGuiCol_Button]					= bar_active;
                style.Colors[ImGuiCol_ButtonHovered]			= highlight_blue;
                style.Colors[ImGuiCol_ButtonActive]				= highlight_blue_active;
                style.Colors[ImGuiCol_Header]					= highlight_blue; // selected items (tree, menu bar etc.)
                style.Colors[ImGuiCol_HeaderHovered]			= highlight_blue_hovered; // hovered items (tree, menu bar etc.)
                style.Colors[ImGuiCol_HeaderActive]				= highlight_blue_active;
                style.Colors[ImGuiCol_Separator]				= background_light;
                //style.Colors[ImGuiCol_SeparatorHovered]		= ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
                //style.Colors[ImGuiCol_SeparatorActive]		= ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
                style.Colors[ImGuiCol_ResizeGrip]				= background_medium;
                style.Colors[ImGuiCol_ResizeGripHovered]		= highlight_blue;
                style.Colors[ImGuiCol_ResizeGripActive]			= highlight_blue_hovered;
                style.Colors[ImGuiCol_PlotLines]				= ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
                //style.Colors[ImGuiCol_PlotLinesHovered]		= ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
                style.Colors[ImGuiCol_PlotHistogram]			= highlight_blue; // Also used for progress bar
                style.Colors[ImGuiCol_PlotHistogramHovered]		= highlight_blue_hovered;
                style.Colors[ImGuiCol_TextSelectedBg]			= highlight_blue;
                style.Colors[ImGuiCol_PopupBg]					= background_dark;
                style.Colors[ImGuiCol_DragDropTarget]			= background_light;
                //style.Colors[ImGuiCol_ModalWindowDarkening]	= ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
            }

};

#endif //OPENGL_EDITORSTYLE_H
