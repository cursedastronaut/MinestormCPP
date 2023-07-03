#include "app.hpp"

App::App()
{
	players.resize(1);
	players[0].Init();
}

App::~App()
{
}

void App::Update()
{
	dl = ImGui::GetBackgroundDrawList();
	io = &ImGui::GetIO();
	
	GPT::Math::Vector newBullet =
	players[0].Update(io);
	players[0].Draw(*dl, res);
	
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].Update(io);
		bullets[i].Draw(*dl);
	}

	if (newBullet[3] == 1.f)
	{
		Bullet bullet;
		bullet.Init(newBullet);
		bullets.push_back(bullet);
	}
#ifdef _DEBUG
	ImGui::Begin("test");
	ImGui::Text("deltatime %f", io->DeltaTime);
	ImGui::End();
#endif
}
