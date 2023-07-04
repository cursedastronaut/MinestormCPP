#include "app.hpp"
#ifdef _DEBUG
bool debugShowCollision = false;
#endif
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
		if (!bullets[i].isActive) continue;
		bullets[i].Update(io);
		bullets[i].Draw(*dl);
		CheckCollisions(players[0].GetPos(), bullets[i].GetPos(), players[0].GetAngle(), 0, players[0].GetSize(), bullets[i].GetSize());
	}

	if (newBullet[3] == 1.f)
	{
		Bullet bullet;
		bullet.Init(newBullet);
		bullets.push_back(bullet);
	}

#ifdef _DEBUG
	ImGui::Begin("test");
	ImGui::Text("FPS %f", 1.f/io->DeltaTime);
	ImGui::Checkbox("DebugCollision", &debugShowCollision);
	ImGui::End();
#endif
}

bool App::CheckCollisions(GPT::Math::Vector a, GPT::Math::Vector b, float aAngle, float bAngle, GPT::Math::Vector aSize, GPT::Math::Vector bSize)
{
	size_t temp = 0;
	GPT::Math::Vector2 square1[4];
	square1[  temp] = (GPT::Math::rotatePoint({ a[0] - aSize[0] / 2		,	a[1] - aSize[1] / 2 }, a.toVec2(), aAngle));
	square1[++temp] = (GPT::Math::rotatePoint({ a[0] + aSize[0] / 2		,	a[1] - aSize[1] / 2 }, a.toVec2(), aAngle));
	square1[++temp] = (GPT::Math::rotatePoint({ a[0] + aSize[0] / 2		,	a[1] + aSize[1] / 2 }, a.toVec2(), aAngle));
	square1[++temp] = (GPT::Math::rotatePoint({ a[0] - aSize[0] / 2		,	a[1] + aSize[1] / 2 }, a.toVec2(), aAngle));

	GPT::Math::Vector2 square2[4]; temp = 0;
	square2[  temp] = (GPT::Math::rotatePoint({ b[0] - bSize[0] / 2		,	b[1] - bSize[1] / 2 }, b.toVec2(), bAngle));
	square2[++temp] = (GPT::Math::rotatePoint({ b[0] + bSize[0] / 2		,	b[1] - bSize[1] / 2 }, b.toVec2(), bAngle));
	square2[++temp] = (GPT::Math::rotatePoint({ b[0] + bSize[0] / 2		,	b[1] + bSize[1] / 2 }, b.toVec2(), bAngle));
	square2[++temp] = (GPT::Math::rotatePoint({ b[0] - bSize[0] / 2		,	b[1] + bSize[1] / 2 }, b.toVec2(), bAngle));
	float xMin1, xMax1, xMin2, xMax2, yMin1, yMax1, yMin2, yMax2;
	for (int i = 1; i <= 3; i++)
	{
		//projection des deux carrés du point de vue du 1er carré.
		xMin1 = fminf(square1[i - 2].x, square1[i].x);
		xMax1 = fmaxf(square1[i - 2].x, square1[i].x);
		yMin1 = fminf(square1[i - 2].y, square1[i].y);
		yMax1 = fmaxf(square1[i - 2].y, square1[i].y);

		xMin2 = fminf(square2[i - 2].x, square2[i].x);
		xMax2 = fmaxf(square2[i - 2].x, square2[i].x);
		yMin2 = fminf(square2[i - 2].y, square2[i].y);
		yMax2 = fmaxf(square2[i - 2].y, square2[i].y);
	}

	//Détecte s'il y a une collision et dessine les boite de collisions
	// if (xMax1 <= xMin2 || yMax1 >= yMin2)
	if (xMax1 >= xMin2 && xMin1 <= xMax2 && yMax1 >= yMin2 && yMin1 <= yMax2)
	{
#ifdef _DEBUG
		if (debugShowCollision)
		{
			dl->AddQuad(ImGuiUtils::toImVec2(square1[0]), ImGuiUtils::toImVec2(square1[1]), ImGuiUtils::toImVec2(square1[2]), ImGuiUtils::toImVec2(square1[3]), IM_COL32(255, 255, 0, 255));
			dl->AddQuad(ImGuiUtils::toImVec2(square2[0]), ImGuiUtils::toImVec2(square2[1]), ImGuiUtils::toImVec2(square2[2]), ImGuiUtils::toImVec2(square2[3]), IM_COL32(255, 255, 0, 255));
		}
#endif
		return true;
	}
	else
	{
#ifdef _DEBUG
		if (debugShowCollision)
		{
			dl->AddQuad(ImGuiUtils::toImVec2(square1[0]), ImGuiUtils::toImVec2(square1[1]), ImGuiUtils::toImVec2(square1[2]), ImGuiUtils::toImVec2(square1[3]), IM_COL32(255, 0, 0, 255));
			dl->AddQuad(ImGuiUtils::toImVec2(square2[0]), ImGuiUtils::toImVec2(square2[1]), ImGuiUtils::toImVec2(square2[2]), ImGuiUtils::toImVec2(square2[3]), IM_COL32(255, 0, 0, 255));
		}
#endif
		return false;
	}
}