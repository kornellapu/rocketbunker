#pragma once

#include "raylib.h"
#include <string>

using namespace std;

class Renderable {
protected:
	int frameCount;
	string filePath;
	bool animate = false;
	bool looping = false;
	Vector2 spriteSize;

	void parseSpriteSize(string metrics);
	void parseFrameInfo(string imageFilePath);

public:
	Texture tx;
	Vector2 pos;
	Vector2 scale = { 4, 4 };
	float rotation = 0;
	Color tint = WHITE;

	int currentFrame = 0;
	bool visible = true;

	virtual void render();
};

//------------------------------------------------------------
//------------------------------------------------------------

class Button : public Renderable {
public:
	void init(string imageFilePath);
	void unload(); 
};

//------------------------------------------------------------
//------------------------------------------------------------

class Rocket : public Renderable {
public:

};