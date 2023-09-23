#include "resources.h"

Resources::Resources()
{
	player = ImGuiUtils::LoadTexture("assets/entities/spaceship.png");
	background = ImGuiUtils::LoadTexture("assets/background.png");
}