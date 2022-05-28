#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include<cmath>
#include"menu.h"  
using namespace sf;

int main()
{
    srand(time(NULL));
    const int screenwidth = 800;
    const int screenheight = 500;
    const Vector2f paddlesize(25, 100);
    const float ballradius = 10.f;
    const float pi = 3.14159f;

    RenderWindow app(VideoMode(screenwidth, screenheight), "pong!", Style::Titlebar | Style::Close);
    Menu menu(app.getSize().x, app.getSize().y);
    Texture t1,t2;
    t1.loadFromFile("images/background.jpg");
    t2.loadFromFile("images/background1.jpg");
    Sprite sBackground(t1);
    Sprite aBackground(t2);

    RectangleShape  leftpaddle;
    leftpaddle.setSize(paddlesize);
    leftpaddle.setFillColor(Color::Blue);
    leftpaddle.setOutlineThickness(3);
    leftpaddle.setOutlineColor(Color(0, 0, 0));
    leftpaddle.setPosition(0, screenheight / 2);
    leftpaddle.setOrigin(paddlesize / 2.f);

    RectangleShape rightpaddle;
    rightpaddle.setSize(paddlesize);
    rightpaddle.setFillColor(Color::Red);
    rightpaddle.setOutlineThickness(3);
    rightpaddle.setOutlineColor(Color(0, 0, 0));
    rightpaddle.setPosition(screenwidth, screenheight / 2);
    rightpaddle.setOrigin(paddlesize / 2.f);

    CircleShape ball;
    ball.setRadius(ballradius);
    ball.setFillColor(Color::Yellow);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(Color::Black);
    ball.setPosition(screenwidth / 2, screenheight / 2);

    float paddlespeed = 200.f;
    const float ballspeed = 200.f;
    float angleball = -90.f;
    Font font;
    if (!font.loadFromFile("../Data/ARCADE.TTF")) return EXIT_FAILURE;
    Text text;
    text.setFont(font);
    text.setPosition(screenwidth / 7, screenheight / 7);
    text.setFillColor(Color::Red);
    text.setCharacterSize(50);

    int Score1 = 0;
    Text textScore1;
    std::string strScore1 = std::to_string(Score1);
    textScore1.setString(strScore1);
    textScore1.setFont(font);
    textScore1.setCharacterSize(45);
    textScore1.setPosition(sf::Vector2f(screenwidth / 5.f, 0.f));
    textScore1.setFillColor(Color::Green);

    int Score2 = 0;
    Text textScore2;
    std::string strScore2 = std::to_string(Score2);
    textScore2.setString(strScore2);
    textScore2.setFont(font);
    textScore2.setCharacterSize(45);
    textScore2.setPosition(sf::Vector2f(650.f, 0.f));
    textScore2.setFillColor(Color::Green);

    Clock clock;
    float deltatime = 0.f;

    bool isplaying = false;
    SoundBuffer ballSFX;
    ballSFX.loadFromFile("../Data/collidewithbrick.ogg");
    Sound sfx;
    sfx.setBuffer(ballSFX);

    while (app.isOpen()) {
        deltatime = clock.restart().asSeconds();
        if (isplaying == false && Keyboard::isKeyPressed(Keyboard::Enter)) {
            ball.setPosition(screenwidth / 2, screenheight / 2);
            rightpaddle.setPosition(screenwidth, screenheight / 2);
            leftpaddle.setPosition(0, screenheight / 2);
            do {
                angleball = rand() % 360;
            } while (angleball < 45 || (angleball > 135 && angleball < 225) || angleball > 335);
            isplaying = true;
        }
        if (isplaying) {
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                Vector2f pos = leftpaddle.getPosition();
                if (pos.y + paddlesize.y / 2 + paddlespeed * deltatime > screenheight) {
                    leftpaddle.setPosition(pos.x, screenheight - paddlesize.y / 2);
                }
                else leftpaddle.move(0, paddlespeed * deltatime);
            }
            else if (Keyboard::isKeyPressed(Keyboard::W)) {
                Vector2f pos = leftpaddle.getPosition();
                if (pos.y - paddlesize.y / 2 - paddlespeed * deltatime < 0) {
                    leftpaddle.setPosition(pos.x, paddlesize.y / 2);
                }
                else leftpaddle.move(0, -paddlespeed * deltatime);
            }


            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                Vector2f pos = rightpaddle.getPosition();
                if (pos.y + paddlesize.y / 2 + paddlespeed * deltatime > screenheight) {
                    rightpaddle.setPosition(pos.x, screenheight - paddlesize.y / 2);
                }
                else rightpaddle.move(0, paddlespeed * deltatime);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                Vector2f pos = rightpaddle.getPosition();
                if (pos.y - paddlesize.y / 2 - paddlespeed * deltatime < 0) {
                    rightpaddle.setPosition(pos.x, paddlesize.y / 2);
                }
                else rightpaddle.move(0, -paddlespeed * deltatime);
            }

            float factor = ballspeed * deltatime;
            ball.move(sin(angleball * pi / 180) * factor, -cos(angleball * pi / 180) * factor);
            if (ball.getPosition().y <= 0 || ball.getPosition().y >= screenheight) {
                angleball = 180.f - angleball;
                sfx.play();
            }
            if (ball.getPosition().x - ballradius <= leftpaddle.getPosition().x + paddlesize.x / 2
                && ball.getPosition().y >= leftpaddle.getPosition().y - paddlesize.y / 2
                && ball.getPosition().y <= leftpaddle.getPosition().y + paddlesize.y / 2
                && ball.getPosition().x > leftpaddle.getPosition().x)
            {
                Score1++;
                strScore1 = std::to_string(Score1);
                textScore1.setString(strScore1);
                if (ball.getPosition().y > leftpaddle.getPosition().y) {
                    angleball = 360.f - angleball + rand() % 10;
                }
                else {
                    angleball = 360.f - angleball - rand() % 10;
                }
                sfx.play();
            }
            if (ball.getPosition().x + ballradius >= rightpaddle.getPosition().x - paddlesize.x / 2
                && ball.getPosition().y >= rightpaddle.getPosition().y - paddlesize.y / 2
                && ball.getPosition().y <= rightpaddle.getPosition().y + paddlesize.y / 2
                && ball.getPosition().x < rightpaddle.getPosition().x)
            {
                Score2++;
                strScore2 = std::to_string(Score2);
                textScore2.setString(strScore2);
                if (ball.getPosition().y > rightpaddle.getPosition().y) {
                    angleball = 360.f - angleball - rand() % 10;
                }
                else {
                    angleball = 360.f - angleball + rand() % 10;
                }
                sfx.play();
            }
            if (ball.getPosition().x <= 0) {
                text.setString("Red is winner ");
                isplaying = false;
            }
            else if (ball.getPosition().x >= screenwidth) {
                text.setString("Blue is winner ");
                isplaying = false;
            }

        }

        app.clear(Color::White);
        if (isplaying) {
            app.draw(sBackground);
            app.draw(leftpaddle);
            app.draw(rightpaddle);
            app.draw(ball);
            app.draw(textScore1);
            app.draw(textScore2);
        }
        else {
            app.draw(aBackground);
            app.draw(text);
            menu.draw(app);
        }
        app.display();
        Event event;
        while (app.pollEvent(event))
        {

            //"close requested" event: we close the window

            switch (event.type)
            {
            case Event::Closed:
                app.close();

            case Event::KeyPressed:
                switch (event.key.code)
            case Keyboard::Escape:
                isplaying = false;
                break;

            case Event::KeyReleased:  //menu controls
                switch (event.key.code)
                {
                case Keyboard::Up:
                case Keyboard::W:
                    menu.MoveUp();
                    break;
                case Keyboard::Down:
                case Keyboard::S:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        isplaying = true;
                        break;
                    case 1:
                        app.close();
                        break;
                    }
                    break;
                }
                break;
            }

        }
    }

}

    
