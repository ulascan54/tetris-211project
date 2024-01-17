#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Player.h"
#include "constants.h"
#include "colortheme.h"
#include "GetColorTheme.h"
#include "Logic.h"
#include "highscoretype.h"
#include "highscores.h"
#include "Board.h"
#include "Portal.h"
#include "Pieces.h"

#include <iostream>

class Game
{
  Portal portal;
  Board board;
  vector<Piece> shapes;

  Piece currentBlock;
  Piece nextBlock;
  Piece holdBlock;

  color_theme theme;
  Player *player;

  std::shared_ptr<sf::RenderWindow> window;
  sf::RenderWindow *pause_window;

  sf::RectangleShape *window_background;
  sf::RectangleShape *game_background;
  sf::RectangleShape *flasbang_background;
  sf::RectangleShape pause_background;

  std::shared_ptr<sf::Sprite> sprite;
  std::shared_ptr<sf::Sprite> background;

  sf::Clock clock;
  sf::Clock lvlClock;
  sf::Clock flashbangClock;
  sf::Clock portalClock;

  sf::Time flashbangDuration;
  sf::Time flashbangElapsed;
  sf::Time portalDuration;
  sf::Time portalElapsed;
  sf::Time lvlDuration;
  sf::Time lvlElapsed;

  sf::Text txtScore;
  sf::Text txtGameOver;
  sf::Text txtPlayerName;
  sf::Text txtTitle;
  sf::Text txtCombo;
  sf::Text txtLevel;
  sf::Text txtRotateCount;
  sf::Text pause_title;
  sf::Text pause_resume;
  sf::Text pause_restart;
  sf::Text pause_back_to_menu;
  sf::Text pause_exit;
  sf::Text txtNextItem;
  sf::Text txtHoldItem;
  sf::Text txtDifficulty;

  sf::Font font;

  sf::Sound *mainSound;
  sf::Sound gameSound;
  sf::Sound otherSound;

  sf::SoundBuffer game_music_gameover;
  sf::SoundBuffer game_music_rotate;
  sf::SoundBuffer game_music_drop;
  sf::SoundBuffer game_music_pause_menu;
  sf::SoundBuffer game_music_pause_menu_return;
  sf::SoundBuffer game_music_levelup;
  sf::SoundBuffer game_music_lineclear;
  sf::SoundBuffer game_flash;
  sf::SoundBuffer game_music_hold;
  sf::SoundBuffer error_sound;
  sf::SoundBuffer game_music;

  sf::Image *img_sound_on;
  sf::Image *img_sound_off;
  sf::Image tetris_icon;

  sf::Sprite *sound_sprite;
  sf::Sprite tetris_sprite;

  sf::Texture *sound_texture;
  sf::Texture tetris_texture;

  sf::Texture tiles;
  sf::Texture bg;

  int dirx, color, score, combo, level, rotateCount;
  bool rotate, gameover, *menu_music, flashbang, isPortalExsist;
  bool isKeepBlock = false;
  float time, timercount, delay, speed;

protected:
  void events();
  void draw();
  void resetValues();
  void jumpToDown();
  void getPauseMenu();
  void pauseMenuEventsHandler(int &selectedOption, sf::Event &event);
  void drawPauseMenu(int &selectedOption);

  void MoveBlockLeft();
  void MoveBlockDown();
  void MoveBlockRight();
  bool IsBlockOutside();
  void RotateBlock();
  void LockBlock();
  bool BlockFits();
  Piece GetRandomPiece();
  vector<Piece> GetAllPieces();
  void levelManager();
  void keepBlock();
  void showFlashbang();
  void randomPortal();

public:
  Game(Player *player, color_theme theme, bool *menu_music, sf::Sound *mainSound, sf::Image *img_sound_on, sf::Image *img_sound_off, sf::Texture *sound_texture, sf::Sprite *sound_sprite);
  void run();
};
