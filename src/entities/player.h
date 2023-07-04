#pragma once
#include "../imgui_utils.hpp"
#include "../resources.h"


class Player : GPT::phy::Physics
{
private:
	ImGuiIO* io;
	float	speed = 5.f;
	const float	bulletCooldownDef = 0.25f;
	float	bulletCooldown = 0.00f;

public:
	Player();
	void	Init();
	GPT::Math::Vector	Update(ImGuiIO* io);
	void	Draw(ImDrawList& dl, Resources& res);
	float	GetAngle();
	GPT::Math::Vector	GetPos();
	GPT::Math::Vector	GetSize();
	void	Borders();
	Physics GetPhysics();
	Physics* GetPhysicsP();

};