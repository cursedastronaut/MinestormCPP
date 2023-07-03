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
}

void Bullet::Draw(ImDrawList& dlA)
{
	//dlA.AddImage(resa.player.id, ImGuiUtils::toImVec2(pos.toVec2()), ImGuiUtils::toImVec2((pos + 128).toVec2()), { 0, 0 }, { 1,1 });
	dlA.AddCircleFilled(ImGuiUtils::toImVec2(pos.toVec2()), 8, IM_COL32_WHITE);
}

void Bullet::Update(ImGuiIO* io)
{
	//Movement
	for (uint8_t i = 0; i < 2; i++)
		pos[i] += momentum[i] * io->DeltaTime;
	Borders();
}

void Bullet::Borders()
{
	if (pos[0] < -200)
		pos[0] = 1280 + 200;
	if (pos[1] < -200)
		pos[1] = 720 + 200;
	if (pos[0] > 1480)
		pos[0] = -200;
	if (pos[1] > 920)
		pos[1] = -200;
}