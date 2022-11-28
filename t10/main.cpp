#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "SFML/Graphics.hpp"


using namespace sf;

//dimensions in 2D that are whole numbers
struct Dim2Di
{
	int x, y;
};

//dimensions in 2D that are floating point numbers
struct Dim2Df
{
	float x, y;
};


/*
A box to put Games Constants in.
These are special numbers with important meanings (screen width,
ascii code for the escape key, number of lives a player starts with,
the name of the title screen music track, etc.
*/
namespace GC
{
	//game play related constants to tweak
	const Dim2Di SCREEN_RES{ 1600,900 };

	const char ESCAPE_KEY{ 27 };
}

int randomInt(int min = 0, int max = 7)
{
	int random = ((std::rand() % max) + min);
	return random;
}
float randomFloat(float min = 0.f, float max = 100.f)
{
	float random = (fmodf((float)std::rand(), max)) + min;
	return random;
}

bool loadTexture(sf::String& file, sf::Texture& texture)
{
	if (!texture.loadFromFile(file))
		assert(false);
		return false;
}

class Tree
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String texPath = "data/Trees.png";

	sf::Vector2f position;
	sf::Vector2f scale;
	int index;

	Tree()
	{
		position = { 100, 600 };
		scale = { 2, 2 };

		loadTexture(texPath, texture);
		sprite.setTexture(texture);

		position.x = randomFloat(0.f, 1200.f);
		//position.y = randomFloat(500.f, 850.f);
		index = randomInt(0, 6);
		//index = 2;
		int width = texture.getSize().x / 7;
		int height = texture.getSize().y;
		sf::Rect<int> size = { width * index, 0, width, height};

		sprite.setTextureRect(size);
		sprite.setPosition(position);
		sprite.setScale(scale);
	}
};

int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Trees");

	Tree trees[50];
	//Tree tree1;

	srand((unsigned)time(NULL));
	// Start the game loop 
	while (window.isOpen())
	{

		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();
			}
		} 

		// Clear screen
		window.clear();


		sf::Texture starsTex, planetTex, grassTex;
		sf::String starPath = "data/backgroundLayers/stars.png";
		sf::String planetPath = "data/backgroundLayers/earth.png";
		sf::String grassPath = "data/bg_parallaxFar.png";
		loadTexture(starPath, starsTex);
		loadTexture(planetPath, planetTex);
		loadTexture(grassPath, grassTex);

		sf::Sprite starSprite(starsTex);
		starSprite.setScale((float)GC::SCREEN_RES.x / starsTex.getSize().x, (float)GC::SCREEN_RES.y / starsTex.getSize().y);
		//starSprite.setPosition(0, 0);
		window.draw(starSprite);

		sf::Sprite planetSprite(planetTex);
		planetSprite.setScale(.9f, .9f);
		planetSprite.setPosition(0, 70);
		window.draw(planetSprite);

		sf::Sprite grassSprite(grassTex);
		grassSprite.setScale((float)GC::SCREEN_RES.x / grassTex.getSize().x, (float)GC::SCREEN_RES.y / grassTex.getSize().y);
		//grassSprite.setPosition(0, 0);
		window.draw(grassSprite);


		for (int i = 0; i < 50; i++)
		{
			window.draw(trees[i].sprite);
		}

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
