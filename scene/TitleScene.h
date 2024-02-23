#pragma once
#include "IScene.h"
#include "../Input/Input.h"
#include "../object/Model/Model.h"
#include "../object/Sprite/Sprite.h"

class GameManager;

class TitleScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;
private:
	Input* input_{};

	std::unique_ptr<Sprite> sprite_{};
	//Sprite* Sprite_{};

	WorldWorldTransform transform_{};

	ViewProjection viewProjection;

	int t_;
	int isT_;
};