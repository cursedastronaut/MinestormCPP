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
};
