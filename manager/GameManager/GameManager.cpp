//#include "GameManager.h"
//#include "../../base/ResourceLeakCheck/ResourceLeakCheck.h"
//
//void GameManager::Initialize() 
//{
//#pragma region 基盤システムの初期化
//	directX12_ = DirectX12::GetInstance();
//	directX12_->GetInstance()->Init();
//
//	graphicsRenderer_ = GraphicsRenderer::GetInstance();
//	graphicsRenderer_->GetInstance()->Initialize();
//
//	light_ = Light::Getinstance();
//	light_->Getinstance()->Initialize();
//	
//	textureManager_ = TextureManager::GetInstance();
//	textureManager_->GetInstance()->Initialize();
//
//	modelManager_ = ModelManager::GetInstance();
//	modelManager_->GetInstance()->Initialize();
//
//#pragma endregion 基盤システムの初期化
//
//	for (int i = 0; i < 3; i++) {
//		colorVolume_[i] = 1.0f;
//		scale_[i] = 1.0f;
//		rotate_[i] = 0.0f;
//		translate_[i] = 0.0f;
//	}
//
//	for (int i = 0; i < MAXTRIANGLE; i++) {
//		triangle_[i] = new Triangle;
//		triangle_[i]->Initialize(directX12_, triangleData[i]);
//	}
//
//	/*for (int i = 0; i < MAXSPHERE; i++) {
//		sphere_[i] = new Sphere;
//		sphere_[i]->Initialize(directX12_);
//	}*/
//
//	sphere_->Initialize(directX12_,light_);
//
//	/*for (int i = 0; i < MAXSPRITE; i++) {
//		sprite_[i] = new Sprite;
//		sprite_[i]->Initialize(directX12_);
//	}*/
//
//	sprite_->Initialize();
//
//	model_->Initialize();
//
//
//	graphicsRenderer_->Viewport();
//	graphicsRenderer_->ScissorRect();
//}
//
//void GameManager::Update() {
//#pragma region ImGui(もういらないかも)
//	ImGui::ColorEdit3("TriangleColor", colorVolume_);
//	ImGui::SliderFloat3("TriangleColor", colorVolume_, 0.0f, 1.0f);
//	ImGui::SliderFloat3("TriangleScale", scale_, -5, 5);
//	ImGui::SliderFloat3("TriangleRotate", rotate_, -5, 5);
//	ImGui::SliderFloat3("TriangleTranslate", translate_, -1, 1);
//	ImGui::Begin("CommonSettings");
//	if (ImGui::BeginTabBar("CommonTabBar"))
//	{
//		// ライトのImGui
//		if (ImGui::BeginTabItem("Half Lambert")) {
//			light_->AdjustParameter();
//			ImGui::EndTabItem();
//		}
//		ImGui::EndTabBar();
//	}
//	ImGui::End();
//
//	color_ = { colorVolume_[0],colorVolume_[1],colorVolume_[2],1.0f };
//	transform_ = { {scale_[0],scale_[1],scale_[2]},{rotate_[0],rotate_[1],rotate_[2]},{translate_[0],translate_[1],translate_[2]} };
//	rotate_[1] += 0.0f;
//#pragma endregion ImGui
//
//#pragma region Update
//	/*for (int i = 0; i < MAXTRIANGLE; i++) {
//		triangle_[i]->Update(transform_,color_);
//	}*/
//
//	/*for (int i = 0; i < MAXSPHERE; i++) {
//		sphere_[i]->Update(transform_, color_);
//	}*/
//
//	//sphere_->Update(transform_,color_);
//
//	sprite_->Update();
//	/*for (int i = 0; i < MAXSPRITE; i++) {
//		sprite_[i]->Update(transform_);
//	}*/
//	model_->Update(transform_, color_);
//
//#pragma endregion Update
//
//	ImGui::Render();
//}
//
//void GameManager::Release() {
//	
//	graphicsRenderer_->Release();
//}
//
//
//
//void GameManager::BeginFrame() {
//	ImGui_ImplDX12_NewFrame();
//	ImGui_ImplWin32_NewFrame();
//	ImGui::NewFrame();
//	directX12_->PreDraw();
//	graphicsRenderer_->DrawCall();
//}
//
//void GameManager::EndFrame() {
//	directX12_->PostDraw();
//}
//
//void GameManager::Finalize() {
//	directX12_->Finalize();
//	textureManager_->Finalize();
//}
//
/////////////////////////////////////////////////////////////////Draw//////////////////////////////////
//void GameManager::Draw2D() {
//	graphicsRenderer_->SetRootSignatureAndPSO(0);
//	sprite_->Draw();
//}
//
//void GameManager::Draw3D() {
//	graphicsRenderer_->SetRootSignatureAndPSO(1);
//	model_->Draw(1);
//}
//
//void GameManager::Draw() {
//
//	Draw2D();
//
//	Draw3D();
//	/*for (int i = 0; i < MAXTRIANGLE; i++) {
//		triangle_[i]->Draw();
//	}*/
//	/*for (int i = 0; i < MAXSPHERE; i++) {
//		sphere_[i]->Draw();
//	}*/
//	//sphere_->Draw();
//	/*for (int i = 0; i < MAXSPRITE; i++) {
//		sprite_[i]->Draw();
//	}*/
//	
//
//	//model_->Draw(UVCHECKER);
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//void GameManager::VariableInit() {
//	
//	for (int i = 0; i < MAXTRIANGLE; i++) {
//		triangleData[i].Left.position = { -0.5f,-0.5f,0.0f,1.0f };
//		triangleData[i].Left.texcoord = { 0.0f,1.0f };
//
//		triangleData[i].Top.position = { 0.0f,0.5f,0.0f,1.0f };
//		triangleData[i].Top.texcoord = { 0.5f,0.0f };
//
//		triangleData[i].Right.position = { 0.5f,-0.5f,0.0f,1.0f };
//		triangleData[i].Right.texcoord = { 1.0f,1.0f };
//	}
//
//	/*for (int i = 0; i < MAXTRIANGLE; i++) {
//		triangle_[i] = new Triangle;
//		triangle_[i]->Initialize(directX12_,triangleData[i]);
//	}*/
//}
//
//

#include "GameManager.h"

GameManager::GameManager() {
	// 各シーンの配列
	sceneArr_[TITLE_SCENE] = new TitleScene();
	sceneArr_[GAME_SCENE] = new GameScene();
	sceneArr_[GAMECLEAR_SCENE] = new GameClearScene();
}

GameManager::~GameManager() {
	delete titleScene_;
	delete gameScene_;
	delete gameClearScene_;

}

void GameManager::Initialize()
{
#pragma region 基盤システムの初期化
	directX12_ = DirectX12::GetInstance();
	directX12_->GetInstance()->Init();

	graphicsRenderer_ = GraphicsRenderer::GetInstance();
	graphicsRenderer_->GetInstance()->Initialize();

	light_ = Light::Getinstance();
	light_->Getinstance()->Initialize();

	textureManager_ = TextureManager::GetInstance();
	textureManager_->GetInstance()->Initialize();

	modelManager_ = ModelManager::GetInstance();
	modelManager_->GetInstance()->Initialize();

	input_ = Input::GetInstance();
	input_->GetInstance()->Initialize();

#pragma endregion 基盤システムの初期化

	//初期シーンの設定
	sceneNum_ = TITLE_SCENE;
	// シーンごとの初期化
	sceneArr_[sceneNum_]->Initialize();

	//sceneNum_ = TITLESCENE;

	/*titleScene_ = new TitleScene();
	titleScene_->Initialize();
	titleSprite_ = Sprite::Create({ 0,0,0 }, { 1,1 }, { 0,0,0,1 }, TITLE);

	gameScene_ = new GameScene();
	gameScene_->Initialize();

	gameClearScene_ = new GameClearScene();
	gameClearScene_->Initialize();

	clearSprite_ = Sprite::Create({ 0,0,0 }, { 1,1 }, { 0,0,0,1 }, CLEAR);*/

	transform_.Initialize();

	graphicsRenderer_->Viewport();
	graphicsRenderer_->ScissorRect();
}


void GameManager::Update() {
	// 初期化
	Initialize();

	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// 描画前の処理
			BeginFrame();

			// シーンチェック
			preSceneNum_ = sceneNum_;
			sceneNum_ = sceneArr_[sceneNum_]->GetSceneNum();

			//シーン変更チェック
			if (sceneNum_ != preSceneNum_) {
				sceneArr_[preSceneNum_]->Finalize();
				sceneArr_[sceneNum_]->Initialize();
			}

			///
			/// 更新処理
			/// 	
			sceneArr_[sceneNum_]->Update();

			// ImGuiのパラメータを入れている

			///
			/// 描画処理
			/// 
			sceneArr_[sceneNum_]->Draw();
			ImGui::Render();
			// 描画後の処理
			EndFrame();

		}
	}
	// 解放処理
	Finalize();
	//input_->GetInstance()->Update();



#pragma region Update



#pragma endregion Update


}


void GameManager::Release() {

}



void GameManager::BeginFrame() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	directX12_->PreDraw();
	graphicsRenderer_->DrawCall();
}

void GameManager::EndFrame() {
	directX12_->PostDraw();
}

void GameManager::Finalize() {
}

///////////////////////////////////////////////////////////////Draw//////////////////////////////////
void GameManager::Draw2D() {
	graphicsRenderer_->SetRootSignatureAndPSO(0);
	sprite_->Draw();
}

void GameManager::Draw3D() {
	graphicsRenderer_->SetRootSignatureAndPSO(1);
	//model_->Draw(1);
}

void GameManager::Draw() {

	Draw2D();

	Draw3D();
	/*for (int i = 0; i < MAXTRIANGLE; i++) {
		triangle_[i]->Draw();
	}*/
	/*for (int i = 0; i < MAXSPHERE; i++) {
		sphere_[i]->Draw();
	}*/
	//sphere_->Draw();
	/*for (int i = 0; i < MAXSPRITE; i++) {
		sprite_[i]->Draw();
	}*/
	

	//model_->Draw(UVCHECKER);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


void GameManager::VariableInit() {
}
