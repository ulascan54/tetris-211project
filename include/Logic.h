#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <exception>
#include <algorithm>
#include "constants.h"

#include "Textbox.h"
#include "MainMenu.h"
#include "Player.h"
#include "colortheme.h"
#include "GetColorTheme.h"
#include "Game.h"
#include "highscoretype.h"
#include "highscores.h"

#include "CustomShapeEditor.h"

#include <memory>
#include <ctime>
#include <cstdlib>

enum music_type
{
    MENU,
    MENURETURN,
    MAIN
};

class Logic
{
private:
    sf::RenderWindow *MENUW;

    sf::Clock clock;

    sf::Sound sound;
    sf::Sound mainSound;

    sf::SoundBuffer menu_item_buffer;
    sf::SoundBuffer menu_return_buffer;
    sf::SoundBuffer main_music_buffer;
    sf::SoundBuffer error_sound;

    sf::Text score_title;
    sf::Text controller_title;
    sf::Text *controller_info;
    sf::Text *controller_keys;
    sf::Text title;
    sf::Text color_theme_txt;
    sf::Text play_diff;

    sf::Font controller_font;
    sf::Font font;

    sf::Image tetris_icon;
    sf::Image img_sound_on;
    sf::Image img_sound_off;
    sf::Image number_one_icon_img;

    sf::Texture texture;
    sf::Texture number_one_icon_texture;
    sf::Texture sound_texture;

    sf::Sprite sprite;
    sf::Sprite number_one_icon_sprite;
    sf::Sprite sound_sprite;

    Player *player;

    Textbox *textbox;

    vector<std::string> menu_items;
    vector<std::string> controllers_items;
    vector<std::string> play_menu_items;
    vector<std::string> options_items;

    vector<scoreEntry> *topScores;

    vector<sf::RectangleShape> final_points;
    vector<sf::Text> final_scores;

    color_theme theme;

    bool isOptionOpen;
    bool isControllersOpen;
    bool isPlayMenuOpen;
    bool isSoloModeOpen;
    bool isMainMenuOpen;
    bool isSoloGameManager;
    bool isSoloGameRunning;
    bool isHighScoresMenuOpen;
    bool menu_music;
    int diff = 1;

    int textbox_x;
    int textbox_y;
    int textbox_charsize;

    void setMusic();
    void playMusic(music_type type);

    void handleMuteButton(sf::Event event);
    void drawMusicImage();
    void keyboardEventHandler(MainMenu &menu, sf::Event &event);

    void setImage();
    void setBanner();
    void setControllerContent();
    void setMenuMusic(bool m) { menu_music = m; };
    void setHighScoreContent();

    void drawControllerMenu();
    void drawHighScoreContent();

    void menuRouterHandler(MainMenu &MMenu, MainMenu &OMenu, MainMenu &CMenu, MainMenu &PMenu, sf::Event &event);

    void getMainMenu(MainMenu &Menu);
    void getOptionMenu(MainMenu &OMenu);
    void getControllerMenu(MainMenu &CMenu);
    void getPlayMenu(MainMenu &PMenu);
    void getSoloMode();
    void getsoloGameManager();

public:
    Logic(bool menu_music = IS_MUSIC_OPEN, color_theme theme = color_theme::DARK);
    ~Logic();
    void start_game();
};