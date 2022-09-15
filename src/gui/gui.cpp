#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION
#include <string>
#include <vector>

namespace fur::gui {

enum TorrentState { STOP, DOWNLOAD, COMPLETED, ERROR };

struct TorrentGui {
  std::string filename{};
  TorrentState status = STOP;
  int progress{};
};

struct GuiSettingsDialogState {
  bool show = false;
};

struct GuiTorrentDialogState {
  bool play = false;
  bool show_settings = false;
  bool remove = false;
  TorrentGui torrent{};
};

struct GuiScrollTorrentState {
  Vector2 scroll{};
  std::vector<TorrentGui> torrents{};
  GuiTorrentDialogState torrent_dialog_state{};
};

void set_config(int width, int height) {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  InitWindow(width, height, "Furrent");
  // Set larger text size
  GuiSetStyle(DEFAULT, TEXT_SIZE, 15);

  SetWindowPosition(0, 0);

  SetTargetFPS(60);
}

void draw_torrent_item(const fur::gui::TorrentGui& torrent, float pos,
                       fur::gui::GuiTorrentDialogState* state) {
  // Drawing text
  auto name = "Name: " + torrent.filename;
  // Cut the name if it is too long
  if (name.size() > 20) {
    name = name.substr(0, 20) + "...";
  }
  GuiDrawText(name.c_str(), {20, 112 + pos, 0, 20}, TEXT_ALIGN_LEFT, GRAY);
  // Adding progress bar
  GuiProgressBar({275, 110 + pos, 300, 20},
                 (std::to_string(torrent.progress) + "% ").c_str(), NULL,
                 torrent.progress, 0, 100);
  // Adding buttons actions
  auto play = GuiButton({700, 110 + pos, 20, 20}, "#131#");
  auto show_settings = GuiButton({730, 110 + pos, 20, 20}, "#140#");
  auto remove = GuiButton({760, 110 + pos, 20, 20}, "#143#");
  // If one of the buttons is pressed, we update the state
  if (play || show_settings || remove) {
    state->play = play;
    state->show_settings = show_settings;
    state->remove = remove;
    state->torrent = torrent;
  }

  GuiLine({5, 145 + pos, 800 - 10, 1}, NULL);
}

// Show the furrent settings dialog and update the state
void settings_dialog(fur::gui::GuiSettingsDialogState* settings) {
  if (!settings->show) return;
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                Fade(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)), 0.85f));
  settings->show = !GuiWindowBox({200, 50, 400, 400}, "#198# Settings dialog");
  // TODO: Add furrent settings
}

// Show torrent dialog and update the state
void torrent_dialog(fur::gui::GuiTorrentDialogState* torrent) {
  if (!torrent->show_settings) return;
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                Fade(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)), 0.85f));
  torrent->show_settings =
      !GuiWindowBox({200, 50, 400, 400}, "#198# Torrent dialog");
  // TODO: Add torrent settings
}

// Function to draw all the torrents
void draw_torrents(fur::gui::GuiScrollTorrentState* state) {
  float pos = 5;
  for (const auto& torr : state->torrents) {
    // If window has been scrolled down some elements are not drawn
    if (pos + 50 < abs(state->scroll.y)) {
      pos += 50;
      continue;
    }
    draw_torrent_item(torr, pos + state->scroll.y,
                      &state->torrent_dialog_state);
    pos += 50;
  }
}
}  // namespace fur::gui
