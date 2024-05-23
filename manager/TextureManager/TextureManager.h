#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include "../../utility/FormatString/FormatString.h"
#include <dxgidebug.h>
#include "../../math/Vector4.h"
#include "../../manager/ImGuiManager/ImGuiManager.h"
#include "../../externals/DirectXTex/DirectXTex.h"
#include <wrl.h>
#include "../../structure/ModelData/ModelData.h"
#include "../../manager/SrvManager/SrvManager.h"
#include "../../base/DirectX12/DirectX12.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

enum TextureName {
	UVCHECKER,
	MONSTERBALL,
	//PLAYER,
	//ENEMY,
	RETICLE,
	PLAYERBULLET,
	ENEMYBULLET,
	SKYDOMETEX,
	CLEAR,
	TITLESPRITE,
	BLACK,
	CIRCLE,

	TEXTURENUM
};

struct TextureData
{
	std::string filePath;
	DirectX::TexMetadata metaData;
	Microsoft::WRL::ComPtr<ID3D12Resource> resource;
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU;
};

class TextureManager
{
public:
	static TextureManager* GetInstance();

	// Textureを読む
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// DirectX12のTextureResourceを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	// 中間リソースの生成
	void UploadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& texture, const DirectX::ScratchImage& mipImages);

	// textureを読んで転送する
	void LoadAndTransferTexture();

	// スプライトの初期化
	void Initialize();

	void CreateResouce();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE* GetTextureSrvHandleGPU() { return textureSrvHandleGPU_; }

private:
	//テクスチャデータ
	std::vector<TextureData> textureDatas_;

	SrvManager* srvManager_;

	static const uint32_t kMaxImages = TEXTURENUM;

	DirectX::ScratchImage mipImages_[kMaxImages]{};

	DirectX::TexMetadata metadata_[kMaxImages]{};

	uint32_t descriptorSizeSRV_[kMaxImages]{};

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_[kMaxImages]{};
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_[kMaxImages]{};

	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource_[kMaxImages]{};
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource_[kMaxImages]{};

	// objデータ
	static const int32_t kMaxObjModelData = 1;
	ModelData* modelData_{};
};

