#pragma once
#include "Game.cpp"
#include <SFML/Graphics.hpp>

sf::View view;
static short ZoomV = 0;
short viewType = 1;

sf::View setCharacterCordforCam(float x, float y)
{
	if (x < 320) x = 320;
	if (y < 240) y = 240;
	if (y > 810) y = 810;
	view.setCenter(x, y);
	return view;
}

sf::View viewMap(float& const time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
	{
		view.move(-0.1 * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
	{
		view.move(0.1 * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		view.move(0, -0.1 * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		view.move(0, 0.1 * time);
	}
	return view;
}

sf::View ZoomCam()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{	
		view.zoom(1.0100f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		view.setSize(640, 480);
	}
	return view;
}