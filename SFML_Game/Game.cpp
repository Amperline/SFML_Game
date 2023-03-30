#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <sstream>

#include "Map.h"
#include "View.h"

class M_Player
{
private:
    short EarnedBlocks = 0;
    int h = 96;
    sf::Keyboard::Key L{ sf::Keyboard::A };
    sf::Keyboard::Key R{ sf::Keyboard::D };
    sf::Keyboard::Key Up{ sf::Keyboard::W };
    sf::Keyboard::Key Down{ sf::Keyboard::S };

    float CurrentFrame = 0.0f;
    float m_x, m_y;
    std::array<sf::IntRect, 4> LeftWalk;
    std::array<sf::IntRect, 4> RightWalk;
    std::array<sf::IntRect, 4> UpWalk;
    std::array<sf::IntRect, 4> DownWalk;
public:
    int dx = 0;
    int dy = 0;
    std::string FileName;
    float m_speed;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    M_Player(std::string Filename, float x, float y, float speed = 0.005)
    {
        LeftWalk[0] = { 0, 96, 96, 96 };
        LeftWalk[1] = { 96, 96, 96, 96 };
        LeftWalk[2] = { 192, 96, 96, 96 };
        LeftWalk[3] = { 96, 96, 96, 96 };

        RightWalk[0] = { 0, 192, 96, 96 };
        RightWalk[1] = { 96, 192, 96, 96 };
        RightWalk[2] = { 192, 192, 96, 96 };
        RightWalk[3] = { 96, 192, 96, 96 };

        UpWalk[0] = { 0, 288, 96, 96 };
        UpWalk[1] = { 96, 288, 96, 96 };
        UpWalk[2] = { 192, 288, 96, 96 };
        UpWalk[3] = { 96, 288, 96, 96 };

        DownWalk[0] = { 0, 0, 96, 96 };
        DownWalk[1] = { 96, 0, 96, 96 };
        DownWalk[2] = { 192, 0, 96, 96 };
        DownWalk[3] = { 96, 0, 96, 96 };

        FileName = { "Images/" + Filename };
        m_speed = speed;
        m_x = x;
        m_y = y;
        image.loadFromFile(FileName);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(RightWalk[1]);
        sprite.setPosition(m_x, m_y);
    }

    void setKeys(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key up, sf::Keyboard::Key down)
    {
        L = l;
        R = r;
        Up = up;
        Down = down;
    }

    void CheckKeyPress(float& time)
    {
        dx = 0;
        dy = 0;
        if (sf::Keyboard::isKeyPressed(L))
        {
            CurrentFrame += 0.005 * time;
            if (CurrentFrame >= 4) { CurrentFrame -= 4; }
            sprite.setTextureRect(sf::IntRect(LeftWalk[int(CurrentFrame)]));
            sprite.move(-0.1 * time, 0);
            setCharacterCordforCam(this->getX() + 48, this->getY());
            dx = -1;
            ResetPositionCord();
        }
        else if ((sprite.getTextureRect() == LeftWalk[0] ||
            sprite.getTextureRect() == LeftWalk[2])
            && !(sf::Keyboard::isKeyPressed(L)))
        {
            sprite.setTextureRect(LeftWalk[1]);
        }
        if (sf::Keyboard::isKeyPressed(R))
        {
            CurrentFrame += 0.005 * time;
            if (CurrentFrame >= 4) { CurrentFrame -= 4; }
            sprite.setTextureRect(sf::IntRect(RightWalk[int(CurrentFrame)]));
            sprite.move(0.1 * time, 0);
            setCharacterCordforCam(this->getX() + 48, this->getY());
            dx = 1;
            ResetPositionCord();
        }
        else if ((sprite.getTextureRect() == RightWalk[0] ||
            sprite.getTextureRect() == RightWalk[2])
            && !(sf::Keyboard::isKeyPressed(R)))
        {
            sprite.setTextureRect(RightWalk[1]);
        }
        if (sf::Keyboard::isKeyPressed(Up))
        {
            CurrentFrame += 0.005 * time;
            if (CurrentFrame >= 4) { CurrentFrame -= 4; }
            sprite.setTextureRect(sf::IntRect(UpWalk[int(CurrentFrame)]));
            sprite.move(0, -0.1 * time);
            setCharacterCordforCam(this->getX() + 48, this->getY());
            dy = -1;
            ResetPositionCord();
        }
        else if ((sprite.getTextureRect() == UpWalk[0] ||
            sprite.getTextureRect() == UpWalk[2])
            && !(sf::Keyboard::isKeyPressed(Up)))
        {
            sprite.setTextureRect(UpWalk[1]);
        }
        if (sf::Keyboard::isKeyPressed(Down))
        {
            CurrentFrame += 0.005 * time;
            if (CurrentFrame >= 4) { CurrentFrame -= 4; }
            sprite.setTextureRect(sf::IntRect(DownWalk[int(CurrentFrame)]));
            sprite.move(0, 0.1 * time);
            setCharacterCordforCam(this->getX() + 48, this->getY());
            dy = 1;
            ResetPositionCord();
        }
        else if ((sprite.getTextureRect() == DownWalk[0] ||
            sprite.getTextureRect() == DownWalk[2])
            && !(sf::Keyboard::isKeyPressed(Down)))
        {
            sprite.setTextureRect(DownWalk[1]);
        }
        InteractionSpikeCheck('s');
        InteractionWithBlockCheck('0');
        InteractionWithBlockCheck('s');
        InteractionGettingCheck('r');
        dx = 0;
        dy = 0;
    }
    void ResetPositionCord()
    {
        m_x = sprite.getPosition().x;
        m_y = sprite.getPosition().y;
    }

    void setPositionCord()
    {
        sprite.setPosition(m_x, m_y);
    }
    float getX()
    {
        return sprite.getPosition().x;
    }
    float getY()
    {
        return sprite.getPosition().y;
    }
    short& getEarnedBloks() { return EarnedBlocks; }

    void InteractionWithBlockCheck(char b)
    {
        for (int y = sprite.getPosition().y / 42; y < ((sprite.getPosition().y + h) / 42); y++)
        {
            for (int x = (sprite.getPosition().x + (h / 4)) / 42; x < ((sprite.getPosition().x + (3 * (h / 4))) / 42); x++)
            {
                if (TileMap[y][x] == b)
                {
                    if (dx == -1)
                    {
                        sprite.setPosition(sprite.getPosition().x + 3, sprite.getPosition().y);
                    }
                    else if (dx == 1)
                    {
                        sprite.setPosition(sprite.getPosition().x - 3, sprite.getPosition().y);
                    }
                    if (dy == 1)
                    {
                        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 3);
                    }
                    else if (dy == -1)
                    {
                        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 3);
                    }
                }
            }
        }
    }
    void InteractionSpikeCheck(char b)
    {
        for (int y = sprite.getPosition().y / 42; y < ((sprite.getPosition().y + h) / 42); y++)
        {
            for (int x = (sprite.getPosition().x + (h / 4)) / 42; x < ((sprite.getPosition().x + (3 * (h / 4))) / 42); x++)
            {
                if (TileMap[y][x] == 's')
                {
                    sprite.setColor(sf::Color::Red);
                    if (dx == -1)
                    {
                        sf::Color a = sprite.getColor();
                        sprite.setColor(sf::Color::Red);
                        sprite.move(20, 0);
                        sprite.setColor(a);
                    }
                    else if (dx == 1)
                    {
                        sf::Color a = sprite.getColor();
                        sprite.setColor(sf::Color::Red);
                        sprite.move(-20, 0);
                        sprite.setColor(a);
                    }
                    if (dy == 1)
                    {
                        sf::Color a = sprite.getColor();
                        sprite.setColor(sf::Color::Red);
                        sprite.move(0, -20);
                        sprite.setColor(a);
                    }
                    else if (dy == -1)
                    {
                        sf::Color a = sprite.getColor();
                        sprite.setColor(sf::Color::Red);
                        sprite.move(0, 20);
                        sprite.setColor(a);
                    }
                }
            }
        }
    }
    void InteractionGettingCheck(char b)
    {
        for (int y = sprite.getPosition().y / 42; y < ((sprite.getPosition().y + h) / 42); y++)
        {
            for (int x = sprite.getPosition().x / 42; x < ((sprite.getPosition().x + h) / 42); x++)
            {
                if (dx == -1)
                {
                    if (TileMap[y][x] == b) { sprite.setPosition(sprite.getPosition().x + 3, sprite.getPosition().y);++EarnedBlocks;TileMap[y][x] = ' ';}
                }
                else if (dx == 1)
                {
                    if (TileMap[y][x] == b) { sprite.setPosition(sprite.getPosition().x - 3, sprite.getPosition().y);++EarnedBlocks; TileMap[y][x] = ' ';}
                }
                if (dy == 1)
                {
                    if (TileMap[y][x] == b) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 3); ++EarnedBlocks ;TileMap[y][x] = ' ';}
                }
                else if (dy == -1)
                {
                    if (TileMap[y][x] == b) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 3); ++EarnedBlocks; TileMap[y][x] = ' ';}
                }
            }
        }
    }
};

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game Window!");
    view.reset(sf::FloatRect(0, 0, 640, 480));

    sf::Font font;
    font.loadFromFile("DeliciousHandrawn-Regular.ttf");
    sf::Text text("", font, 30);
    text.setStyle(sf::Text::Bold); 

    sf::Image MapImg;
    MapImg.loadFromFile("Images/Map2.png");
    MapImg.createMaskFromColor(sf::Color(255, 255, 255));
    sf::Texture MapTxtr;
    MapTxtr.loadFromImage(MapImg);
    sf::Sprite MapSprite;
    MapSprite.setTexture(MapTxtr);

    GameMap a(25, 40);
    a.generateMap();
    TileMap = a.get_TileMap();

    M_Player p("Character.png", 140.0f, 140.0f);
    M_Player p2("Character.png", 150.0f, 150.0f);

    p2.sprite.setColor(sf::Color::Green);
    p2.setKeys(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);

    float CurrentFrame = 0.0f;

    sf::Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        auto NormalTime{ time / 800 };
        auto FastTime{ time / 400 };
        time = NormalTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { time = FastTime; }
        else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))) { time = NormalTime; }
        
        p2.CheckKeyPress(time);
        p.CheckKeyPress(time);
        
        viewMap(FastTime);
        ZoomCam();
        window.setView(view);
        window.clear(sf::Color::Black);
        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for(int j = 0; j < WEIDTH_MAP; j++)
            {
                MapSprite.setPosition(j * 42, i * 42);
                if (a.get_TileMap()[i][j] == '0')
                {
                    MapSprite.setTextureRect(sf::IntRect(30, 539, 110, 110));
                }
                else if (TileMap[i][j] == 's')
                {
                    MapSprite.setTextureRect(sf::IntRect(220, 374, 110, 110));
                    window.draw(MapSprite);
                    MapSprite.setTextureRect(sf::IntRect(871, 213, 110, 110));
                }
                else if (TileMap[i][j] == ' ')
                {
                    MapSprite.setTextureRect(sf::IntRect(220, 374, 110, 110));
                }
                else if (TileMap[i][j] == 'r')
                {
                    MapSprite.setTextureRect(sf::IntRect(220, 374, 110, 110));
                    window.draw(MapSprite);
                    MapSprite.setTextureRect(sf::IntRect(0, 1035, 110, 110));
                }
                MapSprite.setScale(ScaleValue, ScaleValue);
                window.draw(MapSprite);
            }
        }
        
        std::stringstream sstr;
        sstr << p.getEarnedBloks();
        text.setString("Earned rocks: " + sstr.str());
        text.setPosition(view.getCenter().x + 120, view.getCenter().y - 200);

        window.draw(text);
        window.draw(p.sprite);
        window.draw(p2.sprite);
        window.display();
    }
}