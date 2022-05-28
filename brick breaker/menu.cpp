#include "menu.h"
Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("../Data/ARCADE.TTF"))
    {
    }


    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setCharacterSize(50);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Red);
    menu[1].setCharacterSize(50);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 2));

    selectecItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectecItemIndex - 1 >= 0)
    {
        menu[selectecItemIndex].setFillColor(sf::Color::Yellow);
        selectecItemIndex--;
        menu[selectecItemIndex].setFillColor(sf::Color::Blue);
    }
}

void Menu::MoveDown()
{
    if (selectecItemIndex + 1 < MAX_NUMBER_ITEMS)
    {
        menu[selectecItemIndex].setFillColor(sf::Color::Yellow);
        selectecItemIndex++;
        menu[selectecItemIndex].setFillColor(sf::Color::Blue);
    }
}