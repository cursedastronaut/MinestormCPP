#pragma once
#include "../imgui_utils.hpp"
#include "../resources.h"


class Bullet : GPT::phy::Physics
{
private:
	ImGuiIO* io;
	float	speed = 15.f;
	float	lifetime = 10.f;
public:
	Bullet();
	bool	isActive = true;

	void	Init(GPT::Math::Vector posA);
	void	Update(ImGuiIO* io);
	void	Draw(ImDrawList& dl);
	void	Borders();
	Physics GetPhysics();
	Physics* GetPhysicsP();
	GPT::Math::Vector	GetPos();
	GPT::Math::Vector	GetSize();
};