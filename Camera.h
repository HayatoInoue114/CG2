#pragma once
#include "MT.h"

class Camera
{
public:
	void Initialize();

	Matrix4x4 MakeWVPMatrix(Transform &transform);

private:
	Transform cameraTransform_;
};

