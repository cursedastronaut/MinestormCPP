#include "player.h"

Player::Player() {  };
void Player::Init()
{
	Initialisation(2, false, 0);
	pos[0] = 128;
	pos[1] = 128;
	size[0] = 128;
	size[1] = 128;
}

void Player::Draw(ImDrawList& dlA, Resources& res)
{
	//dlA.AddImage(resa.player.id, ImGuiUtils::toImVec2(pos.toVec2()), ImGuiUtils::toImVec2((pos + 128).toVec2()), { 0, 0 }, { 1,1 });
	dlA.AddImageQuad(
		res.player.id,
		ImGuiUtils::toImVec2(GPT::Math::rotatePoint({ pos[0] - size[0] / 2		,	pos[1] - size[1] / 2 }, pos.toVec2(), angle[0])),
		ImGuiUtils::toImVec2(GPT::Math::rotatePoint({ pos[0] + size[0] / 2		,	pos[1] - size[1] / 2 }, pos.toVec2(), angle[0])),
		ImGuiUtils::toImVec2(GPT::Math::rotatePoint({ pos[0] + size[0] / 2		,	pos[1] + size[1] / 2 }, pos.toVec2(), angle[0])),
		ImGuiUtils::toImVec2(GPT::Math::rotatePoint({ pos[0] - size[0] / 2		,	pos[1] + size[1] / 2 }, pos.toVec2(), angle[0]))
	);
}

GPT::Math::Vector Player::Update(ImGuiIO* io)
{
	//Movement
	for (uint8_t i = 0; i < 2; i++)
		pos[i] += momentum[i] * io->DeltaTime;

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Q))
		angle[0] -= (480.0f * PI_F / 360.0f) * io->DeltaTime;
	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_D))
		angle[0] += (480.0f * PI_F / 360.0f) * io->DeltaTime;

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Z))
	{
		momentum[0] -= (sin(-angle[0])) * speed;
		momentum[1] -= (cos(-angle[0])) * speed;
	}

	GPT::Math::Vector output;
	output.set_dimension(6);
	if (bulletCooldown > 0.0f)
		bulletCooldown -= io->DeltaTime;
	
	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_E) && bulletCooldown <= 0.0f)
	{
		output[0] = pos[0];
		output[1] = pos[1];
		output[2] = angle[0];
		output[3] = 1.0f;
		output[4] = (cos(angle[0] - PI_F / 2.f)) * 800;
		output[5] = (sin(angle[0] - PI_F / 2.f)) * 800;
		bulletCooldown = bulletCooldownDef;
	}
	
	//Frictions
	momentum[0] *= 0.996f;
	momentum[1] *= 0.996f;

	Borders();
	return output;
}

float Player::GetAngle()
{
	return angle[0];
}

void Player::Borders()
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

GPT::phy::Physics* Player::GetPhysicsP()
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

GPT::Math::Vector	Player::GetPos()
{
	return pos;
}

GPT::Math::Vector	Player::GetSize()
{
	return size;
}