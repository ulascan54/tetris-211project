#include "Game.h"

Game::Game(Player *player, color_theme theme, bool *menu_music, sf::Sound *mainSound, sf::Image *img_sound_on, sf::Image *img_sound_off, sf::Texture *sound_texture, sf::Sprite *sound_sprite) : portal(SOLOGAMEMODE_POSITION_X, SOLOGAMEMODE_POSITION_Y)
{
  this->player = player;

  isPortalExsist = false;

  board = Board();
  shapes = GetAllPieces();

  for (int i = 0; i < player->getCustomPieces().size(); i++)
  {
    shapes.push_back(player->getCustomPieces()[i]);
  }

  currentBlock = GetRandomPiece();
  nextBlock = GetRandomPiece();
  holdBlock.id = -1;
  isKeepBlock = false;

  this->img_sound_on = img_sound_on;
  this->img_sound_off = img_sound_off;
  this->sound_texture = sound_texture;
  this->sound_sprite = sound_sprite;

  this->menu_music = menu_music;
  this->theme = theme;
  this->mainSound = mainSound;
  mainSound->stop();

  window_background = new sf::RectangleShape();
  window_background->setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
  window_background->setFillColor(getColor(theme, BACKGROUND));

  flasbang_background = new sf::RectangleShape();
  flasbang_background->setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
  flasbang_background->setFillColor(sf::Color::White);
  flashbang = false;

  window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
      GAME_TITLE,
      sf::Style::Titlebar | sf::Style::Close);

  tiles.loadFromFile("images/squares.png");
  sprite = std::make_shared<sf::Sprite>();
  sprite->setTexture(tiles);
  sprite->setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));

  bg.loadFromFile("images/background.png");
  background = std::make_shared<sf::Sprite>();
  background->setTexture(bg);
  background->setPosition(SOLOGAMEMODE_POSITION_X, SOLOGAMEMODE_POSITION_Y);
  background->setColor(sf::Color(255, 255, 255, 100));
  game_background = new sf::RectangleShape();
  game_background->setSize(sf::Vector2f(360, 720));
  game_background->setPosition(SOLOGAMEMODE_POSITION_X, SOLOGAMEMODE_POSITION_Y);
  game_background->setFillColor(sf::Color::Transparent);
  game_background->setOutlineColor(getColor(theme, BORDER));
  game_background->setOutlineThickness(5);

  game_music_drop.loadFromFile(GAME_MUSIC_DROP_MP3);
  game_music_gameover.loadFromFile(GAME_MUSIC_GAMEOVER_MP3);
  game_music_rotate.loadFromFile(GAME_MUSIC_ROTATE_MP3);
  game_music_levelup.loadFromFile(GAME_MUSIC_LEVELUP_MP3);
  game_music_lineclear.loadFromFile(GAME_MUSIC_LINECLEAR_MP3);
  game_flash.loadFromFile(GAME_MUSIC_FLASHBANG_MP3);
  game_music_pause_menu.loadFromFile(SOUND_MENU_ITEM_MP3);
  game_music_hold.loadFromFile(GAME_MUSIC_HOLD_MP3);
  error_sound.loadFromFile(ERROR_SOUND_MP3);
  game_music_pause_menu_return.loadFromFile(SOUND_MENU_RETURN_MP3);
  game_music.loadFromFile(GAME_MUSIC_MP3);
  gameSound.setVolume(100);
  otherSound.setVolume(50);

  if (player->get_diff() == 1)
  {
    rotateCount = 5;
    speed = 0.8f;
    lvlDuration = sf::seconds(60.0f);

    flashbangDuration = sf::seconds(rand() % 90 + 50);
    portalDuration = sf::seconds(rand() % 80 + 40);
  }
  else if (player->get_diff() == 2)
  {
    rotateCount = 3;
    speed = 1.0f;
    lvlDuration = sf::seconds(45.0f);
    flashbangDuration = sf::seconds(rand() % 80 + 30);
    portalDuration = sf::seconds(rand() % 20 + 10);
  }
  else if (player->get_diff() == 3)
  {
    rotateCount = 2;
    speed = 1.8f;
    lvlDuration = sf::seconds(30.0f);
    game_music.loadFromFile(GAME_MUSIC_HARD_MP3);
    flashbangDuration = sf::seconds(rand() % 30 + 15);
    portalDuration = sf::seconds(rand() % 10 + 5);
  }

  mainSound->setBuffer(game_music);
  mainSound->setVolume(SOUND_VOLUME);
  mainSound->setLoop(true);
  mainSound->setVolume(80);
  if (*menu_music)
  {
    mainSound->play();
  }

  dirx = score = combo = {0};
  level = 1;
  rotate = gameover = {false};
  timercount = {0.f};
  delay = {0.3f};
  color = {1};

  font.loadFromFile(MAIN_MENU_FONT_FAMMILY);

  txtPlayerName.setFont(font);
  txtPlayerName.setPosition(20, 100);
  txtPlayerName.setString("PLAYER: " + player->get_name());
  txtPlayerName.setFillColor(getColor(theme, FONT));
  txtPlayerName.setCharacterSize(30);

  txtScore.setFont(font);
  txtScore.setPosition(20, 160);
  txtScore.setString("SCORE: " + std::to_string(score));
  txtScore.setFillColor(getColor(theme, FONT));
  txtScore.setCharacterSize(25);

  txtCombo.setFont(font);
  txtCombo.setPosition(20, 220);
  txtCombo.setString("COMBO: x" + std::to_string(combo));
  txtCombo.setFillColor(getColor(theme, FONT));
  txtCombo.setCharacterSize(25);

  txtLevel.setFont(font);
  txtLevel.setPosition(20, 280);
  txtLevel.setString("LEVEL: " + std::to_string(level));
  txtLevel.setFillColor(getColor(theme, FONT));
  txtLevel.setCharacterSize(25);

  txtRotateCount.setFont(font);
  txtRotateCount.setPosition(20, 340);
  txtRotateCount.setString("ROTATE: " + std::to_string(rotateCount));
  txtRotateCount.setFillColor(getColor(theme, FONT));
  txtRotateCount.setCharacterSize(25);

  txtDifficulty.setFont(font);
  txtDifficulty.setPosition(20, 400);
  if (player->get_diff() == 1)
    txtDifficulty.setString("DIFFICULTY: Medium");
  else if (player->get_diff() == 2)
    txtDifficulty.setString("DIFFICULTY: Hard");
  else if (player->get_diff() == 3)
    txtDifficulty.setString("DIFFICULTY: Deadly");

  txtDifficulty.setFillColor(getColor(theme, FONT));
  txtDifficulty.setCharacterSize(25);

  if (!tetris_icon.loadFromFile(TETRIS_ICON_PNG))
  {
    throw std::invalid_argument("Invalid image path");
  }
  tetris_texture.loadFromImage(tetris_icon);
  tetris_sprite.setTexture(tetris_texture);
  tetris_sprite.setPosition(TETRIS_ICON_POSITION_X, TETRIS_ICON_POSITION_Y);
  tetris_sprite.setScale(TETRIS_ICON_WIDTH, TETRIS_ICON_HEIGHT);

  txtTitle.setFont(font);
  txtTitle.setFillColor(getColor(theme, TITLE));
  txtTitle.setCharacterSize(GAME_TITLE_SIZE);
  txtTitle.setString(GAME_TITLE);
  txtTitle.setPosition(GAME_TITLE_POSITION_X, GAME_TITLE_POSITION_Y);

  txtGameOver.setFont(font);
  txtGameOver.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 40);
  txtGameOver.setString(TXT_GAMEOVER);
  txtGameOver.setFillColor(sf::Color::Red);
  txtGameOver.setStyle(sf::Text::Bold);
  txtGameOver.setOutlineColor(sf::Color::Black);
  txtGameOver.setOutlineThickness(3);
  txtGameOver.setCharacterSize(80);

  sound_sprite->setTexture(*sound_texture);
  sound_sprite->setPosition(WINDOW_WIDTH - 70, 10);
  sound_sprite->setScale(SOUND_SCALE_WIDTH, SOUND_SCALE_HEIGHT);

  pause_background.setSize(sf::Vector2f(360, 500));
  pause_background.setFillColor(getColor(theme, BACKGROUND));
  pause_title.setFont(font);
  pause_title.setFillColor(getColor(theme, TITLE));
  pause_title.setCharacterSize(GAME_TITLE_SIZE);
  pause_title.setString(PAUSE_MENU_TITLE);
  pause_title.setPosition(GAME_TITLE_POSITION_X, GAME_TITLE_POSITION_Y);

  pause_resume.setFont(font);
  pause_resume.setFillColor(getColor(theme, FONT));
  pause_resume.setCharacterSize(30);
  pause_resume.setString(PAUSE_MENU_ITEM_1);
  pause_resume.setPosition(20, 100);

  pause_restart.setFont(font);
  pause_restart.setFillColor(getColor(theme, FONT));
  pause_restart.setCharacterSize(30);
  pause_restart.setString(PAUSE_MENU_ITEM_2);
  pause_restart.setPosition(20, 160);

  pause_back_to_menu.setFont(font);
  pause_back_to_menu.setFillColor(getColor(theme, FONT));
  pause_back_to_menu.setCharacterSize(30);
  pause_back_to_menu.setString(PAUSE_MENU_ITEM_3);
  pause_back_to_menu.setPosition(20, 220);

  pause_exit.setFont(font);
  pause_exit.setFillColor(getColor(theme, FONT));
  pause_exit.setCharacterSize(30);
  pause_exit.setString(PAUSE_MENU_ITEM_4);
  pause_exit.setPosition(20, 280);

  txtNextItem.setFont(font);
  txtNextItem.setFillColor(getColor(theme, FONT));
  txtNextItem.setCharacterSize(30);
  txtNextItem.setString(TXT_GAME_NEXT);
  txtNextItem.setPosition(SOLOGAMEMODE_POSITION_X + 370, SOLOGAMEMODE_POSITION_Y + 10);

  txtHoldItem.setFont(font);
  txtHoldItem.setFillColor(getColor(theme, FONT));
  txtHoldItem.setCharacterSize(30);
  txtHoldItem.setString(TXT_GAME_HOLD);
  txtHoldItem.setPosition(SOLOGAMEMODE_POSITION_X + 370, SOLOGAMEMODE_POSITION_Y + 210);
}

void Game::events()
{

  time = clock.getElapsedTime().asSeconds();
  clock.restart();
  timercount += time * speed;

  auto e = std::make_shared<sf::Event>();
  while (window->pollEvent(*e))
  {
    if (e->type == sf::Event::Closed)
    {
      window->close();
    }

    if (e->type == sf::Event::KeyPressed)
    {
      if (e->key.code == sf::Keyboard::Up || e->key.code == sf::Keyboard::W)
      {
        if (rotateCount > 0)
        {
          rotate = true;
          RotateBlock();
        }
        else
        {
          if (*menu_music)
          {
            gameSound.setBuffer(error_sound);
            gameSound.play();
          }
        }
      }
      else if (e->key.code == sf::Keyboard::Right || e->key.code == sf::Keyboard::D)
      {
        MoveBlockRight();
      }
      else if (e->key.code == sf::Keyboard::Left || e->key.code == sf::Keyboard::A)
      {
        MoveBlockLeft();
      }
      else if (e->key.code == sf::Keyboard::Down || e->key.code == sf::Keyboard::S)
      {
        delay = 0.05f;
        if (player->get_diff() == 3)
        {
          score += 3;
        }
        else if (player->get_diff() == 2)
        {
          score += 2;
        }
        else
        {
          ++score;
        }

        txtScore.setString("SCORE: " + std::to_string(score));
        player->set_score(score);
      }
      else if (e->key.code == sf::Keyboard::Z || e->key.code == sf::Keyboard::L)
      {
        jumpToDown();
      }
      else if (e->key.code == sf::Keyboard::H)
      {
        if (isKeepBlock)
        {
          isKeepBlock = false;
          keepBlock();
        }
      }
      else if (e->key.code == sf::Keyboard::M)
      {
        if (*menu_music)
        {
          *menu_music = false;
          mainSound->pause();
          gameSound.stop();
          otherSound.stop();

          sound_texture->loadFromImage(*img_sound_off);
        }
        else
        {
          *menu_music = true;
          mainSound->play();
          gameSound.play();
          sound_texture->loadFromImage(*img_sound_on);
        }
        sound_sprite->setTexture(*sound_texture);
      }
      else if (e->key.code == sf::Keyboard::Escape)
      {
        window->close();
      }
      else if (e->key.code == sf::Keyboard::P)
      {
        getPauseMenu();
      }
    }
  }
}

void Game::pauseMenuEventsHandler(int &selectedOption, sf::Event &event)
{

  while (pause_window->pollEvent(event))
  {

    if (event.type == sf::Event::Closed)
    {
      pause_window->close();
    }
    if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Escape)
      {
        pause_window->close();
      }
      else if (event.key.code == sf::Keyboard::Up)
      {
        selectedOption = (selectedOption - 1 + 4) % 4;
        if (*menu_music)
        {
          gameSound.setBuffer(game_music_pause_menu);
          gameSound.play();
        }
      }
      else if (event.key.code == sf::Keyboard::Down)
      {
        selectedOption = (selectedOption + 1) % 4;
        if (*menu_music)
        {
          gameSound.setBuffer(game_music_pause_menu);
          gameSound.play();
        }
      }
      else if (event.key.code == sf::Keyboard::P)
      {
        pause_window->close();
        gameSound.setBuffer(game_music_pause_menu_return);
        gameSound.play();
      }
      else if (event.key.code == sf::Keyboard::M)
      {
        if (*menu_music)
        {
          *menu_music = false;
          mainSound->pause();
          gameSound.stop();
          sound_texture->loadFromImage(*img_sound_off);
        }
        else
        {
          *menu_music = true;
          mainSound->play();
          gameSound.play();
          sound_texture->loadFromImage(*img_sound_on);
        }
        sound_sprite->setTexture(*sound_texture);
      }
      else if (event.key.code == sf::Keyboard::Return)
      {
        gameSound.setBuffer(game_music_pause_menu_return);
        gameSound.play();
        if (selectedOption == 0)
        {
          pause_window->close();
        }
        else if (selectedOption == 1)
        {
          pause_window->close();
          window->close();
          Game tetris(player, theme, menu_music, mainSound, img_sound_on, img_sound_off, sound_texture, sound_sprite);
          tetris.run();
        }
        else if (selectedOption == 2)
        {
          pause_window->close();
          window->close();
          mainSound->stop();
          gameSound.stop();
          Logic tetris(*menu_music, theme);
          tetris.start_game();
        }
        else if (selectedOption == 3)
        {
          pause_window->close();
          window->close();
        }
      }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        if (pause_resume.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
          gameSound.setBuffer(game_music_pause_menu_return);
          gameSound.play();
          pause_window->close();
        }
        else if (pause_restart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
          gameSound.setBuffer(game_music_pause_menu_return);
          gameSound.play();
          pause_window->close();
          window->close();
          Game tetris(player, theme, menu_music, mainSound, img_sound_on, img_sound_off, sound_texture, sound_sprite);
          tetris.run();
        }
        else if (pause_back_to_menu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
          gameSound.setBuffer(game_music_pause_menu_return);
          gameSound.play();
          pause_window->close();
          window->close();
          mainSound->stop();
          gameSound.stop();
          Logic tetris(*menu_music, theme);
          tetris.start_game();
        }
        else if (pause_exit.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
          gameSound.setBuffer(game_music_pause_menu_return);
          gameSound.play();
          pause_window->close();
          window->close();
        }
      }
    }
  }
}

void Game::getPauseMenu()
{

  pause_window = new sf::RenderWindow(
      sf::VideoMode(360, 500),
      GAME_TITLE,
      sf::Style::Titlebar | sf::Style::Close);

  int selectedOption = 0;

  while (pause_window->isOpen())
  {
    sf::Event event;
    pauseMenuEventsHandler(selectedOption, event);
    pause_window->clear();
    drawPauseMenu(selectedOption);

    pause_window->display();
  }
}

void Game::drawPauseMenu(int &selectedOption)
{
  sf::Text pauseOptions[] = {pause_resume, pause_restart, pause_back_to_menu, pause_exit};
  pause_window->draw(pause_background);
  pause_window->draw(pause_title);

  for (int i = 0; i < 4; ++i)
  {
    if (selectedOption == i)
    {
      pauseOptions[i].setFillColor(getColor(theme, MENUHOVER));
    }
    else
    {
      pauseOptions[i].setFillColor(getColor(theme, FONT));
    }
    pause_window->draw(pauseOptions[i]);
  }
}

void Game::draw()
{

  txtRotateCount.setString("ROTATE: " + std::to_string(rotateCount));
  window->clear(sf::Color::Black);
  window->setTitle(sf::String("FPS: " + std::to_string((int)(1 / time / 10))));
  window->draw(*window_background);
  window->draw(*background);
  window->draw(*game_background);

  board.Draw(*window, theme, theme == DEADLY ? true : false);
  currentBlock.Draw(SOLOGAMEMODE_POSITION_X, SOLOGAMEMODE_POSITION_Y, *window, false, theme == DEADLY ? true : false);
  window->draw(txtNextItem);
  window->draw(txtHoldItem);
  if (nextBlock.id == 3)
  {
    nextBlock.Draw(SOLOGAMEMODE_POSITION_X + 265, SOLOGAMEMODE_POSITION_Y + 90, *window, false, theme == DEADLY ? true : false);
  }
  else if (nextBlock.id == 4)
  {
    nextBlock.Draw(SOLOGAMEMODE_POSITION_X + 265, SOLOGAMEMODE_POSITION_Y + 80, *window, false, theme == DEADLY ? true : false);
  }
  else
  {
    nextBlock.Draw(SOLOGAMEMODE_POSITION_X + 280, SOLOGAMEMODE_POSITION_Y + 70, *window, false, theme == DEADLY ? true : false);
  }

  if (holdBlock.id == 3)
  {
    holdBlock.Draw(SOLOGAMEMODE_POSITION_X + 265, SOLOGAMEMODE_POSITION_Y + 290, *window, true, theme == DEADLY ? true : false);
  }
  else if (holdBlock.id == 4)
  {
    holdBlock.Draw(SOLOGAMEMODE_POSITION_X + 265, SOLOGAMEMODE_POSITION_Y + 280, *window, true, theme == DEADLY ? true : false);
  }
  else
  {
    holdBlock.Draw(SOLOGAMEMODE_POSITION_X + 280, SOLOGAMEMODE_POSITION_Y + 270, *window, true, theme == DEADLY ? true : false);
  }
  portal.Draw(*window);

  window->draw(*sound_sprite);
  window->draw(txtScore);
  window->draw(txtTitle);
  window->draw(txtCombo);
  window->draw(txtLevel);
  window->draw(tetris_sprite);
  window->draw(txtPlayerName);
  window->draw(txtDifficulty);

  window->draw(txtRotateCount);
  if (level > 1 && player->get_diff() != 1)
  {
    sf::RectangleShape rectangle(sf::Vector2f(360, 36));
    rectangle.setFillColor(sf::Color::Red);
    int line = player->get_diff() == 2 ? level : level * 2;
    for (size_t i = 0; i < line; i++)
    {
      rectangle.setPosition(SOLOGAMEMODE_POSITION_X, SOLOGAMEMODE_POSITION_Y + 720 - 36 - (36 * i));
      window->draw(rectangle);
    }
  }
  if (flashbang)
  {
    window->draw(*flasbang_background);
    flashbangElapsed = flashbangClock.getElapsedTime();

    flashbang = flashbangElapsed <= sf::seconds(1.0) ? true : false;
  }
  if (gameover)
  {
    window->draw(txtGameOver);
  }

  window->display();
}

void Game::run()
{
  while (window->isOpen())
  {
    events();
    if (!gameover)
    {
      if (timercount > delay)
      {
        MoveBlockDown();
        randomPortal();
        timercount = 0;
      }
      levelManager();
      showFlashbang();
      resetValues();
    }
    draw();
  }
}

void Game::MoveBlockLeft()
{
  if (!gameover)
  {
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.Move(0, 1);
    }
  }
}

void Game::jumpToDown()
{
  if (!gameover)
  {
    while (!(IsBlockOutside() || BlockFits() == false))
    {
      currentBlock.Move(1, 0);
      if (player->get_diff() == 3)
      {
        score += 3;
      }
      else if (player->get_diff() == 2)
      {
        score += 2;
      }
      else
      {
        ++score;
      }

      txtScore.setString("SCORE: " + std::to_string(score));
      player->set_score(score);

      if (IsBlockOutside() || BlockFits() == false)
      {
        currentBlock.Move(-1, 0);
        LockBlock();
        break;
      }
    }
    if (*menu_music)
    {
      gameSound.setBuffer(game_music_drop);
      gameSound.play();
    }
  }
}

void Game::levelManager()
{
  lvlElapsed = lvlClock.getElapsedTime();
  if (lvlElapsed > lvlDuration)
  {
    lvlClock.restart();
    lvlDuration -= sf::seconds(0.5f);
    level++;
    txtLevel.setString("LEVEL: " + std::to_string(level));
    score += 10;
    speed += 0.15f;
    if (*menu_music)
    {
      gameSound.setBuffer(game_music_levelup);
      gameSound.play();
    }
  }
}

void Game::MoveBlockRight()
{
  if (!gameover)
  {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.Move(0, -1);
    }
  }
}

void Game::MoveBlockDown()
{
  if (!gameover)
  {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || BlockFits() == false)
    {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

bool Game::IsBlockOutside()
{
  vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (board.IsCellOutside(item.row, item.column))
    {
      return true;
    }
  }
  return false;
}

void Game::RotateBlock()
{
  if (!gameover && rotate)
  {
    rotateCount--;
    if (currentBlock.id <= 7)
    {
      currentBlock.Rotate();
    }
    else
    {
      currentBlock.RotateCustom();
    }

    if (*menu_music)
    {
      gameSound.setBuffer(game_music_rotate);
      gameSound.play();
    }
    if (IsBlockOutside() || BlockFits() == false)
    {
      rotateCount++;
      currentBlock.UndoRotation();
      if (*menu_music)
      {
        gameSound.setBuffer(error_sound);
        gameSound.play();
      }
    }
  }
}

void Game::LockBlock()
{
  vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    board.gameMatrix[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if (BlockFits() == false)
  {
    gameover = true;
    if (player->get_score() > 0)
    {
      gameFinished(player->get_score(), player->get_name());
    }

    if (*menu_music)
    {
      gameSound.setBuffer(game_music_gameover);
      gameSound.play();
      mainSound->stop();
    }
  }
  nextBlock = GetRandomPiece();
  if (player->get_diff() == 1)
    rotateCount = 5;

  else if (player->get_diff() == 2)
    rotateCount = 3;

  else if (player->get_diff() == 3)
    rotateCount = 2;

  isKeepBlock = true;
  int rowsCleared = board.ClearFullRows();
  if (rowsCleared > 0)
  {
    combo++;
    score++;
    txtScore.setString("SCORE: " + std::to_string(score * combo * player->get_diff()));
    txtCombo.setString("COMBO: x" + std::to_string(combo));
    player->set_score(score * combo);
    if (*menu_music)
    {
      otherSound.setBuffer(game_music_lineclear);
      otherSound.play();
    }
  }
  else
  {
    combo = 0;
    txtCombo.setString("COMBO: x" + std::to_string(combo));
  }
}

bool Game::BlockFits()
{
  vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (board.IsCellEmpty(item.row, item.column) == false)
    {
      return false;
    }
  }
  return true;
}

void Game::resetValues()
{
  dirx = 0;
  rotate = false;
  delay = 0.3f;
}

void Game::keepBlock()
{
  if (holdBlock.id == -1)
  {
    holdBlock = currentBlock;
    currentBlock = nextBlock;
    nextBlock = GetRandomPiece();
  }
  else
  {
    Piece temp = currentBlock;
    currentBlock = holdBlock;
    holdBlock = temp;
  }
  if (*menu_music)
  {
    gameSound.setBuffer(game_music_hold);
    gameSound.play();
  }
}

void Game::showFlashbang()
{
  flashbangElapsed = flashbangClock.getElapsedTime();
  if (flashbangElapsed > flashbangDuration)
  {
    flashbangClock.restart();
    flashbang = true;
    if (*menu_music)
    {
      otherSound.setBuffer(game_flash);
      otherSound.play();
    }
  }
}

void Game::randomPortal()
{
  portalElapsed = portalClock.getElapsedTime();
  if (portalElapsed > portalDuration)
  {
    portalClock.restart();
    isPortalExsist = true;
    portal.TeleportPiece(currentBlock, true);
  }

  if (portal.IsPieceTouching(currentBlock))
  {
    if (isPortalExsist)
    {
      isPortalExsist = false;
    }
    portal.TeleportPiece(currentBlock, false);

    jumpToDown();
  }
}

Piece Game::GetRandomPiece()
{
  if (shapes.empty())
  {
    shapes = GetAllPieces();
    for (int i = 0; i < player->getCustomPieces().size(); i++)
    {
      shapes.push_back(player->getCustomPieces()[i]);
    }
  }
  int randomIndex = rand() % shapes.size();
  Piece piece = shapes[randomIndex];
  shapes.erase(shapes.begin() + randomIndex);
  return piece;
}

vector<Piece> Game::GetAllPieces()
{
  return {IPiece(), JPiece(), LPiece(), OPiece(), SPiece(), TPiece(), ZPiece()};
}