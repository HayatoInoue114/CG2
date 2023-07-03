#pragma once
#include <Windows.h>
#include <cstdint>
#include "ImGuiManager.h"
#include "MT.h"
//#include "DirectX12.h"



//class DirectX12;

class WindowsAPI
{
public:

	void Init();

	void WindowClass();
	void WindowSize();
	void WindowCreate();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


	HWND GetHwnd() const { return hwnd; }

private:
	//ウインドウクラスの設定
	WNDCLASS wc{};
	
	//ウインドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc;

	HWND hwnd = {};
};



