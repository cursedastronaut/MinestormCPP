#pragma once
#include "../imgui_utils.hpp"
#include "../resources.h"


class Bullet : GPT::phy::Physics
{
private:
	ImGuiIO* io;
	float	speed = 15.f;
public:
	Bullet();
	void	Init(GPT::Math::Vector posA);
	void	Update(ImGuiIO* io);
	void	Draw(ImDrawList& dl);
	void	Borders();
};