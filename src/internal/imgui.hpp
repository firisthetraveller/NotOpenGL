#ifndef __IMGUI_FISH__
#define __IMGUI_FISH__

#include "../Config.hpp"
#include "imgui.h"

inline void imguiInit() {
  ImGui::Begin("Parameters");

  if (ImGui::CollapsingHeader("Boid parameters")) {
    ImGui::SliderFloat("Visual range", &Config::getInstance().VISUAL_RANGE, 0.f,
                       0.3f);
    ImGui::SliderFloat("Vital space", &Config::getInstance().MIN_DISTANCE, 0.f,
                       0.1f);
    ImGui::SliderFloat("Speed limit", &Config::getInstance().SPEED_LIMIT, 0.f,
                       0.01f);
  }

  if (ImGui::CollapsingHeader("Behavior parameters")) {
    ImGui::SliderFloat("Separation", &Config::getInstance().SEPARATION_FACTOR,
                       0.f, 0.05f);
    ImGui::SliderFloat("Alignment", &Config::getInstance().ALIGNMENT_FACTOR,
                       0.f, 0.1f);
    ImGui::SliderFloat("Cohesion", &Config::getInstance().COHESION_FACTOR, 0.f,
                       0.005f);
  }

  if (ImGui::CollapsingHeader("Wall avoidance parameters")) {
    ImGui::SliderFloat("Wall margin", &Config::getInstance().WALL_MARGIN, 0.f,
                       0.4f);
    ImGui::SliderFloat("Wall turn", &Config::getInstance().WALL_TURN_FACTOR,
                       0.f, 0.002f);
  }

  if (ImGui::CollapsingHeader("Debug")) {
    ImGui::Checkbox("Show visual ranges",
                    &Config::getInstance().SHOW_VISUAL_RANGES);
    ImGui::Checkbox("Show movement vector",
                    &Config::getInstance().SHOW_MOVEMENT_VECTOR);
  }

  if (ImGui::CollapsingHeader("Colors")) {
    static bool alpha_preview = true;
    static bool alpha_half_preview = false;
    static bool drag_and_drop = true;
    static bool options_menu = true;
    static bool hdr = false;
    ImGuiColorEditFlags misc_flags =
        (hdr ? ImGuiColorEditFlags_HDR : 0) |
        (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) |
        (alpha_half_preview
             ? ImGuiColorEditFlags_AlphaPreviewHalf
             : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) |
        (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

    ImGui::ColorEdit4("Fish type #1", Config::getInstance().FISH_COLOR_1.data(),
                      misc_flags);

    ImGui::ColorEdit4("Food", Config::getInstance().FOOD_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Food - Fill",
                      Config::getInstance().FOOD_FILL_COLOR.data(), misc_flags);
    ImGui::ColorEdit4("Visual range",
                      Config::getInstance().VISUAL_RANGE_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Visual range - Fill",
                      Config::getInstance().VISUAL_RANGE_FILL_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Movement range",
                      Config::getInstance().MOVEMENT_RANGE_COLOR.data(),
                      misc_flags);
  }
  ImGui::End();

  // Show the official ImGui demo window
  // It is very useful to discover all the widgets available in ImGui
  // ImGui::ShowDemoWindow();
}

#endif
