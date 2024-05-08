#include "TestScene.h"
#include "../base/GraphicsRenderer/GraphicsRenderer.h"

void TestScene::Initialize() {
	// 入力
	input_ = Input::GetInstance();

	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	
	model_ = std::make_unique<Model>();
	model_ = Model::CreateModelFromObjPtr("AnimatedCube.gltf");

	object_ = std::make_unique<Object3d>();
	object_->Init(model_.get(),camera_.get());

	domeModel_ = std::make_unique<Model>();
	domeModel_ = Model::CreateModelFromObjPtr("skydome.obj");

	dome_ = std::make_unique<Object3d>();
	dome_->Init(domeModel_.get(),camera_.get());
}

void TestScene::Update() {
	camera_->Update();
}

void TestScene::Draw() {
	GraphicsRenderer::GetInstance()->SetRootSignatureAndPSO(0);
	dome_->Draw();
	object_->Draw();
	
}

void TestScene::Finalize() {
	//primitiveManager_.Finalize();
}