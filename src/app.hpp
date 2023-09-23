#pragma once
#include <vector>
#include "imgui_utils.hpp"
#include "entities/player.h"
#include "entities/bullet.h"
#include "resources.h"
class App
{
public:
    App();
    ~App();
	ImDrawList* dl;
	ImGuiIO* io;
	std::vector <Player> players;
	std::vector <Bullet> bullets;
	Resources res;
    void Update();
	bool CheckCollisions(GPT::Math::Vector a, GPT::Math::Vector b, float aAngle, float bAngle, GPT::Math::Vector aSize, GPT::Math::Vector bSize);
	void backgroundDraw(ImDrawList& dlA, Resources& res);
};

const GPT::Math::Vector2 SCREEN_SIZE = { 1280, 720 };