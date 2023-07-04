#include "bullet.h"

Bullet::Bullet() {  };
void Bullet::Init(GPT::Math::Vector posA)
{
	Initialisation(2, false, 0);
	pos[0] = posA[0];
	pos[1] = posA[1];
	angle[0] = posA[2];
	momentum[0] = posA[4];
	momentum[1] = posA[5];
	size[0] = 8;
	size[1] = 8;
	isActive = true;
	lifetime = 10.0f;
}

void Bullet::Draw(ImDrawList& dlA)
{
	if (!isActive) return;
	//dlA.AddImage(resa.player.id, ImGuiUtils::toImVec2(pos.toVec2()), ImGuiUtils::toImVec2((pos + 128).toVec2()), { 0, 0 }, { 1,1 
	float opacity = 255.f * (lifetime / 10.f);
	if (opacity < 64)
		opacity = 64;
	dlA.AddCircleFilled(ImGuiUtils::toImVec2(pos.toVec2()), 8, IM_COL32(255, 255, 255, opacity));
}

void Bullet::Update(ImGuiIO* io)
{
	if (!isActive) return;
	//Movement
	for (uint8_t i = 0; i < 2; i++)
		pos[i] += momentum[i] * io->DeltaTime;
	Borders();

	lifetime -= io->DeltaTime;
	if (lifetime < 0)
		isActive = false;
}

void Bullet::Borders()
{
	if (!isActive) return;
	if (pos[0] < -200)
		pos[0] = 1280 + 200;
	if (pos[1] < -200)
		pos[1] = 720 + 200;
	if (pos[0] > 1480)
		pos[0] = -200;
	if (pos[1] > 920)
		pos[1] = -200;
}

GPT::phy::Physics* Bullet::GetPhysicsP()
{
	GPT::phy::Physics output;
	output.pos = pos;
	output.angle = angle;
	output.gravityAcceleration = gravityAcceleration;
	output.isAffectedByGravity = isAffectedByGravity;
	output.verticalDimension = verticalDimension;
	output.momentum = momentum;
	output.size = size;
	return &output;
}

GPT::Math::Vector	Bullet::GetPos()
{
	return pos;
}

GPT::Math::Vector	Bullet::GetSize()
{
	return size;
}