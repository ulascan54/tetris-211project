#include "Logic.h"

Logic::Logic(bool m, color_theme t) : menu_music(m), theme(t)
{
    if (theme == DEADLY)
    {
        theme = DARK;
    }

    topScores = nullptr;

    player = new Player("USER");
    diff = 1;
    isMainMenuOpen = true;
    isPlayMenuOpen = false;
    isOptionOpen = false;
    isControllersOpen = false;
    isSoloModeOpen = false;
    isSoloGameManager = false;
    isSoloGameRunning = false;
    isHighScoresMenuOpen = false;

    menu_items.push_back(MENU_ITEM_1);
    menu_items.push_back(MENU_ITEM_2);
    menu_items.push_back(MENU_ITEM_3);
    menu_items.push_back(MENU_ITEM_4);

    options_items.push_back(OPTIONS_ITEM_1);
    options_items.push_back(OPTIONS_ITEM_2);
    options_items.push_back(OPTIONS_ITEM_3);
    options_items.push_back(OPTIONS_ITEM_4);

    controllers_items.push_back(CONTROLLERS_ITEM_1);

    play_menu_items.push_back(PLAY_MENU_ITEM_1);
    play_menu_items.push_back(PLAY_MENU_ITEM_2);
    play_menu_items.push_back(PLAY_MENU_ITEM_3);
    play_menu_items.push_back(PLAY_MENU_ITEM_4);

    play_diff.setFont(font);
    play_diff.setCharacterSize(30);
    play_diff.setPosition(200, WINDOW_HEIGHT - 300);

    color_theme_txt.setFont(font);
    color_theme_txt.setCharacterSize(30);
    color_theme_txt.setPosition(350, 340);

    MENUW = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, sf::Style::Default);

    if (!font.loadFromFile(MAIN_MENU_FONT_FAMMILY))
    {
        throw std::invalid_argument("Logic::Logic() -> Invalid font path");
    }

    setMusic();
    setImage();
    setBanner();
    setControllerContent();

    textbox_x = WINDOW_WIDTH / 2 - 180;
    textbox_y = WINDOW_HEIGHT / 2 - 100;
    textbox_charsize = 30;

    textbox = new Textbox(textbox_charsize, getColor(theme, FONT), true);
    textbox->setFont(font);
    textbox->setPosition(sf::Vector2f(textbox_x, textbox_y));
    textbox->setLimit(true, 15);
}

void Logic::menuRouterHandler(MainMenu &MMenu, MainMenu &OMenu, MainMenu &CMenu, MainMenu &PMenu, sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        MENUW->close();
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            MENUW->close();
        }
        if (isSoloGameManager)
        {
            MENUW->close();
        }
        else if (isSoloModeOpen)
        {
            if (textbox->getText().size() == 0)
            {
                sound.setBuffer(error_sound);
                sound.play();
            }
            else
            {

                if (event.key.code == sf::Keyboard::Return)
                {
                    playMusic(MENURETURN);
                    getPlayMenu(PMenu);
                    player->set_name(textbox->getText());
                    textbox->clear();
                    textbox->setSelected(false);
                    isSoloModeOpen = false;
                    isSoloGameManager = true;
                }
            }
        }
        else if (isPlayMenuOpen)
        {
            keyboardEventHandler(PMenu, event);
            if (event.key.code == sf::Keyboard::Return)
            {
                playMusic(MENURETURN);
                getPlayMenu(PMenu);
            }
        }
        else if (isHighScoresMenuOpen)
        {
            keyboardEventHandler(CMenu, event);
            if (event.key.code == sf::Keyboard::Return)
            {
                playMusic(MENURETURN);
                int choice = CMenu.GetPressedItem();
                if (choice == 0)
                {
                    playMusic(MENURETURN);
                    isHighScoresMenuOpen = false;
                    isMainMenuOpen = true;
                }
            }
        }
        else if (isOptionOpen)
        {
            keyboardEventHandler(OMenu, event);
            if (event.key.code == sf::Keyboard::Return)
            {
                playMusic(MENURETURN);
                getOptionMenu(OMenu);
            }
        }
        else if (isControllersOpen)
        {
            keyboardEventHandler(CMenu, event);
            if (event.key.code == sf::Keyboard::Return)
            {
                playMusic(MENURETURN);
                getControllerMenu(CMenu);
            }
        }
        else if (isMainMenuOpen)
        {
            keyboardEventHandler(MMenu, event);
            if (event.key.code == sf::Keyboard::Return)
            {
                playMusic(MENURETURN);
                getMainMenu(MMenu);
            }
        }
    }
    if (isSoloModeOpen)
    {
        if (event.type == sf::Event::TextEntered)
        {
            textbox->typedOn(event);
        }
    }
}

void Logic::start_game()
{

    MainMenu MMenu(MENUW->getSize().x, MENUW->getSize().y, menu_items, getColor(theme, FONT), getColor(theme, MENUHOVER));

    MainMenu OMenu(MENUW->getSize().x, MENUW->getSize().y, options_items, getColor(theme, FONT), getColor(theme, MENUHOVER));

    MainMenu CMenu(MENUW->getSize().x, MENUW->getSize().y, controllers_items, getColor(theme, FONT), getColor(theme, MENUHOVER));

    MainMenu PMenu(MENUW->getSize().x, MENUW->getSize().y, play_menu_items, getColor(theme, FONT), getColor(theme, MENUHOVER));

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(getColor(theme, BACKGROUND));

    float drawTime = 1 / FPS;
    while (MENUW->isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();

        sf::Event event;
        while (MENUW->pollEvent(event))
        {
            menuRouterHandler(MMenu, OMenu, CMenu, PMenu, event);
        }
        if (time > drawTime)
        {
            MENUW->clear();
            MENUW->draw(background);

            if (isSoloGameManager)
            {
                getsoloGameManager();
            }
            else if (isSoloModeOpen)
            {
                getSoloMode();
            }
            else if (isPlayMenuOpen)
            {
                PMenu.draw(*MENUW);
                if (diff == 1)
                {
                    play_diff.setFillColor(sf::Color::Green);
                    play_diff.setString("Medium");
                }
                else if (diff == 2)
                {
                    play_diff.setFillColor(sf::Color::Blue);
                    play_diff.setString("Hard");
                }
                else if (diff == 3)
                {
                    play_diff.setFillColor(sf::Color::Red);
                    play_diff.setString("Deadly");
                }
                MENUW->draw(play_diff);
                PMenu.setFontColor(getColor(theme, FONT), getColor(theme, MENUHOVER));
            }
            else if (isOptionOpen)
            {
                OMenu.draw(*MENUW);
                OMenu.setFontColor(getColor(theme, FONT), getColor(theme, MENUHOVER));
                color_theme_txt.setString(theme == LIGHT ? "Light" : theme == DARK ? "Dark"
                                                                                   : "Retro");
                color_theme_txt.setFillColor(getColor(theme, FONT));
                MENUW->draw(color_theme_txt);
            }
            else if (isHighScoresMenuOpen)
            {
                CMenu.draw(*MENUW);
                CMenu.setFontColor(getColor(theme, FONT), getColor(theme, MENUHOVER));
                drawHighScoreContent();
            }
            else if (isControllersOpen)
            {
                CMenu.draw(*MENUW);
                CMenu.setFontColor(getColor(theme, FONT), getColor(theme, MENUHOVER));
                setControllerContent();
                drawControllerMenu();
            }
            else if (isMainMenuOpen)
            {
                MMenu.draw(*MENUW);
                MMenu.setFontColor(getColor(theme, FONT), getColor(theme, MENUHOVER));
            }

            background.setFillColor(getColor(theme, BACKGROUND));

            setBanner();
            MENUW->draw(title);
            MENUW->draw(sprite);
            drawMusicImage();

            MENUW->display();
            int fps = 1.0f / time;
            MENUW->setTitle("FPS: " + std::to_string(fps));
            clock.restart();
        }
        else
        {
            sf::sleep(sf::seconds(drawTime - time));
        }
    }
    MENUW->close();
}

void Logic::getsoloGameManager()
{
    MENUW->close();
    std::srand(std::time(0));
    if (diff == 3)
    {
        theme = DEADLY;
    }

    auto tetris = std::make_shared<Game>(player, theme, &menu_music, &mainSound, &img_sound_on, &img_sound_off, &sound_texture, &sound_sprite);

    tetris->run();
    isOptionOpen = false;
    isSoloGameManager = false;
    isSoloGameRunning = false;
    Logic::~Logic();
}

void Logic::keyboardEventHandler(MainMenu &m, sf::Event &e)
{
    if (e.key.code == sf::Keyboard::Up)
    {
        m.MoveUp();
        playMusic(MENU);
    }
    if (e.key.code == sf::Keyboard::Down)
    {
        m.MoveDown();
        playMusic(MENU);
    }
    handleMuteButton(e);
}

void Logic::drawControllerMenu()
{
    MENUW->draw(controller_title);
    for (size_t i = 0; i < LEN_CONTROLLERS_ITEMS; i++)
    {
        MENUW->draw(controller_info[i]);
        MENUW->draw(controller_keys[i]);
    }
}

void Logic::drawHighScoreContent()
{
    MENUW->draw(score_title);
    for (size_t i = 0; i < final_points.size(); i++)
    {
        MENUW->draw(final_points[i]);
        MENUW->draw(final_scores[i]);
    }

    MENUW->draw(number_one_icon_sprite);
}

void Logic::getMainMenu(MainMenu &MMenu)
{
    int choice = MMenu.GetPressedItem();
    if (choice == 0)
    {
        isPlayMenuOpen = true;
        isMainMenuOpen = false;
    }
    if (choice == 1)
    {
        isOptionOpen = true;
        isMainMenuOpen = false;
    }
    if (choice == 2)
    {
        isHighScoresMenuOpen = true;
        setHighScoreContent();

        isMainMenuOpen = false;
    }
    if (choice == 3)
    {
        MENUW->close();
    }
}

void Logic::getPlayMenu(MainMenu &PMenu)
{
    int choice = PMenu.GetPressedItem();
    if (choice == 0)
    {
        isSoloModeOpen = true;
        isPlayMenuOpen = false;
        player->set_diff(diff);
    }
    if (choice == 1)
    {
        std::cout << "Multi Player Logic" << std::endl;
    }
    if (choice == 2)
    {
        diff = diff == 1   ? 2
               : diff == 2 ? 3
                           : 1;
    }
    if (choice == 3)
    {

        playMusic(MENURETURN);
        isPlayMenuOpen = false;
        isMainMenuOpen = true;
        PMenu.setPressedItem(0);
    }
}

void Logic::getSoloMode()
{
    sf::Text textbox_label;
    textbox_label.setFont(font);
    textbox_label.setFillColor(getColor(theme, TITLE));
    textbox_label.setCharacterSize(30);
    textbox_label.setString(TEXTBOX_LABEL);
    textbox_label.setPosition(textbox_x, textbox_y - 50);
    MENUW->draw(textbox_label);

    sf::Text textbox_info;
    textbox_info.setFont(font);
    textbox_info.setFillColor(getColor(theme, FONT));
    textbox_info.setCharacterSize(20);
    textbox_info.setString(TEXTBOX_INFO);
    textbox_info.setPosition(textbox_x, textbox_y + 30);
    MENUW->draw(textbox_info);

    textbox->setTextColor(getColor(theme, FONT));
    textbox->drawTo(*MENUW);
}

void Logic::getOptionMenu(MainMenu &OMenu)
{
    int choice = OMenu.GetPressedItem();
    if (choice == 0)
    {
        std::cout << "Generete Custom Shape button paressed" << std::endl;

        CustomShapeEditor editor(player);
        editor.run();
    }
    if (choice == 1)
    {
        if (theme == LIGHT)
        {
            theme = DARK;
        }
        else if (theme == DARK)
        {
            theme = RETRO;
        }
        else if (theme == RETRO)
        {
            theme = LIGHT;
        }
    }
    if (choice == 2)
    {
        isOptionOpen = false;
        isMainMenuOpen = false;
        isControllersOpen = true;
        playMusic(MENURETURN);
    }
    if (choice == 3)
    {
        playMusic(MENURETURN);
        isOptionOpen = false;
        isMainMenuOpen = true;
        OMenu.setPressedItem(0);
    }
}

void Logic::getControllerMenu(MainMenu &CMenu)
{
    int choice = CMenu.GetPressedItem();
    if (choice == 0)
    {
        playMusic(MENURETURN);
        isControllersOpen = false;
        isOptionOpen = true;
    }
}

void Logic::handleMuteButton(sf::Event event)
{
    if (event.key.code == sf::Keyboard::M)
    {
        setMenuMusic(!menu_music);
        if (menu_music)
            mainSound.play();
        else
            mainSound.pause();
    }
}

void Logic::setControllerContent()
{
    if (!controller_font.loadFromFile(CONTROLLER_FONT_FAMMILY))
    {
        throw std::invalid_argument("Logic::setControllerContent() -> Invalid font path");
    }
    int x = WINDOW_WIDTH / 2 - 200;
    int y = WINDOW_HEIGHT / 2 - 300;
    controller_title.setFont(font);
    controller_title.setFillColor(getColor(theme, TITLE));
    controller_title.setCharacterSize(CONTROLLER_TITLE_SIZE);
    controller_title.setString(GAMEINFO);
    controller_title.setPosition(x, y);

    vector<std::string> infos;
    infos.push_back(CONTROLLER_GAME_INFO_1);
    infos.push_back(CONTROLLER_GAME_INFO_2);
    infos.push_back(CONTROLLER_GAME_INFO_3);
    infos.push_back(CONTROLLER_GAME_INFO_4);
    infos.push_back(CONTROLLER_GAME_INFO_5);
    infos.push_back(CONTROLLER_GAME_INFO_6);
    infos.push_back(CONTROLLER_GAME_INFO_7);
    infos.push_back(CONTROLLER_GAME_INFO_8);

    vector<std::string> keys;
    keys.push_back(CONTROLLER_KEY_LEFT);
    keys.push_back(CONTROLLER_KEY_RIGHT);
    keys.push_back(CONTROLLER_KEY_DOWN);
    keys.push_back(CONTROLLER_KEY_FALL);
    keys.push_back(CONTROLLER_KEY_ROTATE);
    keys.push_back(CONTROLLER_KEY_MUTE);
    keys.push_back(CONTROLLER_KEY_PAUSE);
    keys.push_back(CONTROLLER_KEY_EXIT);

    controller_keys = new sf::Text[LEN_CONTROLLERS_ITEMS];
    controller_info = new sf::Text[LEN_CONTROLLERS_ITEMS];
    for (size_t i = 0; i < LEN_CONTROLLERS_ITEMS; i++)
    {
        controller_info[i].setFont(font);
        controller_info[i].setFillColor(getColor(theme, FONT));
        controller_info[i].setCharacterSize(CONTROLLER_TITLE_SIZE - 10);
        controller_info[i].setString(infos[i]);
        controller_info[i].setPosition(x + 150, y + 80 * (i + 1));

        controller_keys[i].setFont(controller_font);
        controller_keys[i].setFillColor(getColor(theme, FONT));
        controller_keys[i].setCharacterSize(CONTROLLER_TITLE_SIZE + 30);
        controller_keys[i].setString(keys[i]);
        controller_keys[i].setPosition(x - 50, y + 74 * (i + 1));
    }
}

void Logic::setHighScoreContent()
{
    if (topScores == nullptr)
    {
        topScores = new vector<scoreEntry>();
        *topScores = GetHistoryScoreSorted();
    }
    else
    {
        delete topScores;
        topScores = new vector<scoreEntry>();
        *topScores = GetHistoryScoreSorted();
    }

    score_title.setFont(font);
    score_title.setFillColor(getColor(theme, TITLE));
    score_title.setCharacterSize(CONTROLLER_TITLE_SIZE);
    score_title.setString("TOP 10 PLAYERS");
    score_title.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 250);

    final_points.clear();
    final_scores.clear();
    int x = WINDOW_WIDTH / 2 - 200;
    int y = WINDOW_HEIGHT / 2 - 200;
    int count = topScores->size() > 10 ? 10 : topScores->size();

    for (int i = 0; i < count; i++)
    {
        sf::RectangleShape point;
        point.setSize(sf::Vector2f(340, 40));
        point.setPosition(x, y + 50 * (i + 1));
        point.setOutlineColor(sf::Color(128, 128, 128));
        point.setOutlineThickness(2);
        point.setFillColor(getColor(theme, FONT));
        final_points.push_back(point);

        sf::Text score;
        score.setFont(font);
        score.setFillColor(getColor(theme, BACKGROUND));
        score.setCharacterSize(CONTROLLER_TITLE_SIZE - 15);
        score.setString((*topScores)[i].playerName + " : " + std::to_string((*topScores)[i].playerScore));
        score.setPosition(x + 10, y + 50 * (i + 1));
        final_scores.push_back(score);
    }

    number_one_icon_sprite.setPosition(x + 300, y + 50);
    number_one_icon_sprite.setScale(0.08, 0.08);
}

void Logic::setMusic()
{
    if (!menu_item_buffer.loadFromFile(SOUND_MENU_ITEM_MP3))
    {
        throw std::invalid_argument("Logic::setMusic() -> Invalid music path");
    }
    if (!menu_return_buffer.loadFromFile(SOUND_MENU_RETURN_MP3))
    {
        throw std::invalid_argument("Logic::setMusic() -> Invalid music path");
    }
    if (!main_music_buffer.loadFromFile(SOUND_MENU_MAIN_MP3))
    {
        throw std::invalid_argument("Logic::setMusic() -> Invalid music path");
    }
    playMusic(MAIN);

    if (!error_sound.loadFromFile(ERROR_SOUND_MP3))
    {
        throw std::invalid_argument("Logic::setMusic() -> Invalid music path");
    }
}

void Logic::playMusic(music_type type)
{
    if (type == MAIN)
    {
        mainSound.setBuffer(main_music_buffer);
        mainSound.setVolume(SOUND_VOLUME);
        mainSound.setLoop(true);
        if (menu_music)
        {
            mainSound.play();
        }
        return;
    }
    else if (type == MENU)
        sound.setBuffer(menu_item_buffer);
    else if (type == MENURETURN)
        sound.setBuffer(menu_return_buffer);
    if (menu_music)
    {
        sound.play();
    }
}

void Logic::setImage()
{
    if (!img_sound_on.loadFromFile(MUSIC_ON_PNG))
    {
        throw std::invalid_argument("Logic::setImage() -> Invalid image path");
    }
    if (!img_sound_off.loadFromFile(MUSIC_OFF_PNG))
    {
        throw std::invalid_argument("Logic::setImage() -> Invalid image path");
    }
    if (!number_one_icon_img.loadFromFile(NUMBER_ONE_ICON_PNG))
    {
        throw std::invalid_argument("Logic::setImage() -> Invalid image path");
    }

    number_one_icon_texture.loadFromImage(number_one_icon_img);
    number_one_icon_sprite.setTexture(number_one_icon_texture);
}

void Logic::drawMusicImage()
{
    if (menu_music)
        sound_texture.loadFromImage(img_sound_on);
    else
        sound_texture.loadFromImage(img_sound_off);
    sound_sprite.setTexture(sound_texture);
    sound_sprite.setPosition(WINDOW_WIDTH - 70, 10);
    sound_sprite.setScale(SOUND_SCALE_WIDTH, SOUND_SCALE_HEIGHT);
    MENUW->draw(sound_sprite);
}

void Logic::setBanner()
{
    if (!tetris_icon.loadFromFile(TETRIS_ICON_PNG))
    {
        throw std::invalid_argument("Invalid image path");
    }
    texture.loadFromImage(tetris_icon);
    sprite.setTexture(texture);
    sprite.setPosition(TETRIS_ICON_POSITION_X, TETRIS_ICON_POSITION_Y);
    sprite.setScale(TETRIS_ICON_WIDTH, TETRIS_ICON_HEIGHT);

    title.setFont(font);
    title.setFillColor(getColor(theme, TITLE));
    title.setCharacterSize(GAME_TITLE_SIZE);
    title.setString(GAME_TITLE);
    title.setPosition(GAME_TITLE_POSITION_X, GAME_TITLE_POSITION_Y);
}

Logic::~Logic()
{
    delete MENUW;
    delete textbox;
    delete[] controller_keys;
    delete[] controller_info;
    delete player;
    delete topScores;

    MENUW = nullptr;
    textbox = nullptr;
    controller_keys = nullptr;
    controller_info = nullptr;
    player = nullptr;
    topScores = nullptr;
}