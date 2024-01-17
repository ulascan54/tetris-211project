#pragma once

#define MAIN_MENU_FONT_FAMMILY "./font/PixelifySans-VariableFont_wght.ttf"
#define CONTROLLER_FONT_FAMMILY "./font/controls.otf"

#define GAME_TITLE "TETRIS GAME"
#define GAME_TITLE_POSITION_X 100
#define GAME_TITLE_POSITION_Y 20
#define GAME_TITLE_SIZE 50

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define FPS 60.0f

#define SQUARES 4
#define SHAPES 7

#define MENU_ITEM_1 "Play"
#define MENU_ITEM_2 "Options"
#define MENU_ITEM_3 "High Scores"
#define MENU_ITEM_4 "Exit"

#define OPTIONS_ITEM_1 "Generete Custom Shape"
#define OPTIONS_ITEM_2 "Change Color Theme"
#define OPTIONS_ITEM_3 "Controls"
#define OPTIONS_ITEM_4 "Back"

#define CONTROLLERS_ITEM_1 "Back"
#define LEN_CONTROLLERS_ITEMS 8
#define GAMEINFO "GAME RULES"
#define CONTROLLER_GAME_INFO_1 ": Move Left"
#define CONTROLLER_GAME_INFO_2 ": Move Right"
#define CONTROLLER_GAME_INFO_3 ": Move Down"
#define CONTROLLER_GAME_INFO_4 ": Fall Down"
#define CONTROLLER_GAME_INFO_5 ": Rotate"
#define CONTROLLER_GAME_INFO_6 ": Mute"
#define CONTROLLER_GAME_INFO_7 ": Pause"
#define CONTROLLER_GAME_INFO_8 ": Exit"
#define CONTROLLER_KEY_LEFT "s A"
#define CONTROLLER_KEY_RIGHT "t D"
#define CONTROLLER_KEY_DOWN "r S"
#define CONTROLLER_KEY_FALL "L Z"
#define CONTROLLER_KEY_ROTATE "q W"
#define CONTROLLER_KEY_MUTE "M"
#define CONTROLLER_KEY_PAUSE "P"
#define CONTROLLER_KEY_EXIT "m"
#define CONTROLLER_TITLE_SIZE 50

#define MUSIC_ON_PNG "./images/music-on.png"
#define MUSIC_OFF_PNG "./images/music-off.png"
#define IS_MUSIC_OPEN true
#define SOUND_SCALE_WIDTH 0.12
#define SOUND_SCALE_HEIGHT 0.12
#define SOUND_VOLUME 20

#define SOUND_MENU_ITEM_MP3 "./sounds/menu-item-sound.mp3"
#define SOUND_MENU_RETURN_MP3 "./sounds/menu-return-sound.mp3"
#define SOUND_MENU_MAIN_MP3 "./sounds/main-music.mp3"
#define ERROR_SOUND_MP3 "./sounds/error-sound.mp3"

#define TETRIS_ICON_PNG "./images/tetris-icon.png"
#define NUMBER_ONE_ICON_PNG "./images/number-one.png"
#define TETRIS_ICON_WIDTH 0.1
#define TETRIS_ICON_HEIGHT 0.1
#define TETRIS_ICON_POSITION_X 20
#define TETRIS_ICON_POSITION_Y 30

#define PLAY_MENU_ITEM_1 "Solo"
#define PLAY_MENU_ITEM_2 "Battle"
#define PLAY_MENU_ITEM_3 "Difficulty"
#define PLAY_MENU_ITEM_4 "Back"

#define BOARD_WIDTH 200
#define BOARD_HEIGHT 800

#define DELETE_KEY 8
#define ENTER_KEY 10
#define ESCAPE_KEY 36

#define TEXTBOX_LABEL "Enter your name: "
#define TEXTBOX_INFO "Press Enter to continue"

#define SOLOGAMEMODE_POSITION_X 600 - (360 / 2)
#define SOLOGAMEMODE_POSITION_Y 400 - (720 / 2)
#define CELL_SIZE 36
#define ROW_NUM 20
#define COL_NUM 10

#define GAME_MUSIC_DROP_MP3 "./sounds/game-falldown.mp3"
#define GAME_MUSIC_GAMEOVER_MP3 "./sounds/game-over.mp3"
#define GAME_MUSIC_ROTATE_MP3 "./sounds/game-rotate.mp3"
#define GAME_MUSIC_LEVELUP_MP3 "./sounds/game-lvl-up.mp3"
#define GAME_MUSIC_LINECLEAR_MP3 "./sounds/game-clear.mp3"
#define GAME_MUSIC_HOLD_MP3 "./sounds/game-hold-sound.mp3"
#define GAME_MUSIC_FLASHBANG_MP3 "./sounds/game-flashbang.mp3"
#define GAME_MUSIC_MP3 "./sounds/game-music.mp3"
#define GAME_MUSIC_HARD_MP3 "./sounds/game-hard-mode.mp3"

#define PAUSE_MENU_TITLE "PAUSE"
#define PAUSE_MENU_ITEM_1 "RESUME"
#define PAUSE_MENU_ITEM_2 "RESTART"
#define PAUSE_MENU_ITEM_3 "BACK TO MENU"
#define PAUSE_MENU_ITEM_4 "EXIT"

#define TXT_GAME_NEXT "NEXT SHAPE"
#define TXT_GAME_HOLD "HOLDED SHAPE"
#define TXT_GAMEOVER "WASTED"

#define HISTORY_FILENAME "high_scores.txt"

#include <vector>
using namespace std;
