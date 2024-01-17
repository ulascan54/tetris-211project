#include "CustomShapeEditor.h"

CustomShapeEditor::CustomShapeEditor(Player *p) : window(sf::VideoMode(400, 400), "Custom Shape Editor")
{
    id = 7;
    istextShown = false;
    player = p;

    if (!font.loadFromFile(MAIN_MENU_FONT_FAMMILY))
    {
        std::cout << "Error loading font\n";
    }
    successText.setFont(font);
    successText.setString("Successfully saved!");
    successText.setCharacterSize(30);
    successText.setFillColor(sf::Color::Magenta);
    successText.setOutlineThickness(2);

    sf::FloatRect textRect = successText.getLocalBounds();
    successText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    successText.setPosition(sf::Vector2f(400 / 2.0f, 400 / 2.0f));
}

void CustomShapeEditor::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
        if (istextShown)
        {
            sf::sleep(sf::seconds(1.5));
            window.close();
        }
    }
}

void CustomShapeEditor::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                if (isWithinGrid(worldPosition))
                {
                    customShapeCells.push_back(Position(static_cast<int>(worldPosition.x / 100), static_cast<int>(worldPosition.y / 100)));
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {

                CustomShape customShape(++id, customShapeCells);

                pieces.push_back(customShape);

                customShapeCells.clear();
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {

                player->saveCustomPieces(pieces);
                istextShown = true;
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
    }
}

bool CustomShapeEditor::isWithinGrid(sf::Vector2f &position)
{
    return position.x >= 0 && position.x < 400 && position.y >= 0 && position.y < 400;
}

void CustomShapeEditor::render()
{
    window.clear();

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            sf::RectangleShape cellShape(sf::Vector2f(100, 100));
            cellShape.setPosition(static_cast<float>(j * 100), static_cast<float>(i * 100));
            cellShape.setFillColor(sf::Color::White);
            cellShape.setOutlineThickness(2.0f);
            cellShape.setOutlineColor(sf::Color::Black);
            window.draw(cellShape);
        }
    }

    for (auto &cell : customShapeCells)
    {
        sf::RectangleShape cellShape(sf::Vector2f(100, 100));
        cellShape.setPosition(static_cast<float>(cell.row * 100), static_cast<float>(cell.column * 100));
        cellShape.setFillColor(sf::Color::Green);

        window.draw(cellShape);
    }
    if (istextShown)
    {
        window.draw(successText);
    }

    window.display();
}
