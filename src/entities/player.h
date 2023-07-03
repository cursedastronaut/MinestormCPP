#pragma once
#include "../imgui_utils.hpp"
#include "../resources.h"


class Player : GPT::phy::Physics
{
private:
	ImGuiIO* io;
	float	speed = 15.f;
public:
	Player();
	void	Init();
	GPT::Math::Vector	Update(ImGuiIO* io);
	void	Draw(ImDrawList& dl, Resources& res);
	float	GetAngle();
	void	Borders();
};