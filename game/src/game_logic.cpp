#include "game_logic.h"


using namespace std;

void Renderable::parseSpriteSize(string metrics)
{
	string firstNumStr = metrics.substr(0, metrics.find('x'));
	string secondNumStr = metrics.substr(metrics.find('x') + 1);

	spriteSize.x = stof(firstNumStr);
	spriteSize.y = stof(secondNumStr);
}

void Renderable::parseFrameInfo(string imageFilePath)
{
	size_t pu = imageFilePath.find_last_of('_');
	size_t pd = imageFilePath.find_last_of('.');

	string lastPart = imageFilePath.substr(pu + 1, pd + 1 - pu);
	if (lastPart.find('x') != string::npos) {
		//size data, there are only one frame
		parseSpriteSize(lastPart);
	}
	else if (lastPart.find('f') != string::npos) {
		//frame data, there must be a size data before
		string frameNumStr = lastPart.substr(lastPart.find('f') + 1);
		frameCount = stoi(frameNumStr);

		string subImagePath = imageFilePath.substr(0, pu);
		size_t ppu = subImagePath.find_last_of('_');
		string subLastPart = subImagePath.substr(ppu + 1);
		parseSpriteSize(subLastPart);
	}
}

void Renderable::render()
{
	if(!visible)
		return;

	DrawTexturePro(
		tx,
		Rectangle{ currentFrame * spriteSize.x, 0, spriteSize.x, spriteSize.y },
		Rectangle{ pos.x, pos.y, spriteSize.x*scale.x, spriteSize.y*scale.y },
		Vector2{ 0, 0},
		rotation,
		tint
	);

	if (animate) {
		if (currentFrame < frameCount) {
			currentFrame += 1;
			if (looping && currentFrame == frameCount) {
				currentFrame = 0;
			}
		}
	}
}

void Button::init(string imageFilePath)
{
	filePath = imageFilePath;
	parseFrameInfo(imageFilePath);

	Image img = LoadImage(imageFilePath.c_str());
	tx = LoadTextureFromImage(img);
	UnloadImage(img);
}

void Button::unload()
{
	UnloadTexture(tx);
}
