#ifndef __IMGUI_FISH__
#define __IMGUI_FISH__

#include "../Config.hpp"
#include "imgui.h"

inline void imguiInit() {
  ImGui::Begin("Parameters");

  if (ImGui::CollapsingHeader("Boid parameters")) {
    ImGui::SliderFloat("Visual range", &Config::get().VISUAL_RANGE, 0.f, 0.4f);
    ImGui::SliderFloat("Speed limit", &Config::get().SPEED_LIMIT, 0.f, 0.01f);
  }

  if (ImGui::CollapsingHeader("Behavior parameters")) {
    ImGui::SliderFloat("Vital space", &Config::get().SEPARATION_MIN_DISTANCE,
                       0.f, 0.1f);
    ImGui::SliderFloat("Separation", &Config::get().SEPARATION_FACTOR, 0.f,
                       0.05f);
    ImGui::SliderFloat("Alignment", &Config::get().ALIGNMENT_FACTOR, 0.f, 0.1f);
    ImGui::SliderFloat("Cohesion", &Config::get().COHESION_FACTOR, 0.f, 0.005f);
    ImGui::SliderFloat("Obstacle avoidance",
                       &Config::get().OBSTACLE_AVOIDANCE_FACTOR, 0.f, 0.08f);
    ImGui::SliderFloat("Obstacle detection",
                       &Config::get().OBSTACLE_DETECTION_RADIUS, 0.f, 0.6f);
  }

  if (ImGui::CollapsingHeader("Wall avoidance parameters")) {
    ImGui::SliderFloat("Wall margin", &Config::get().WALL_MARGIN, 0.f, 0.4f);
    ImGui::SliderFloat("Wall turn", &Config::get().WALL_TURN_FACTOR, 0.f,
                       0.002f);
  }

  if (ImGui::CollapsingHeader("Debug")) {
    ImGui::Checkbox("Show visual ranges", &Config::get().SHOW_VISUAL_RANGES);
    ImGui::Checkbox("Show movement vector",
                    &Config::get().SHOW_MOVEMENT_VECTOR);
    ImGui::Checkbox("Show position history",
                    &Config::get().SHOW_POSITION_HISTORY);
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

    ImGui::ColorEdit4("Fish type #1", Config::get().FISH_1_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Fish type #1 - Fill",
                      Config::get().FISH_1_FILL_COLOR.data(), misc_flags);

    ImGui::ColorEdit4("Food", Config::get().FOOD_COLOR.data(), misc_flags);
    ImGui::ColorEdit4("Food - Fill", Config::get().FOOD_FILL_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Obstacle", Config::get().OBSTACLE_STROKE_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Obstacle - Fill",
                      Config::get().OBSTACLE_FILL_COLOR.data(), misc_flags);
    ImGui::ColorEdit4("Visual range", Config::get().VISUAL_RANGE_COLOR.data(),
                      misc_flags);
    ImGui::ColorEdit4("Visual range - Fill",
                      Config::get().VISUAL_RANGE_FILL_COLOR.data(), misc_flags);
    ImGui::ColorEdit4("Movement range",
                      Config::get().MOVEMENT_RANGE_COLOR.data(), misc_flags);
    ImGui::ColorEdit4("Movement history",
                      Config::get().MOVEMENT_HISTORY_COLOR.data(), misc_flags);
  }
  ImGui::End();

  // Show the official ImGui demo window
  // It is very useful to discover all the widgets available in ImGui
  // ImGui::ShowDemoWindow();
}

#endif
