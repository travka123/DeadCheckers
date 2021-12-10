#include "WRendering.h"

#include "WPainter.h"

WRendering::WRendering(std::wstring path)
{
	_textures = WTextureSet::LoadFrom(path);
}

void WRendering::Render(HWND hWnd) {
	PAINTSTRUCT ps;

	BeginPaint(hWnd, &ps);

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	WPainter painter(ps.hdc, clientRect, _textures);

	for (int i = 0; i < renderLayersCount; i++) {
		for (IRenderable* entity : _entities[i]) {
			entity->Render(painter);
		}
	}

	EndPaint(hWnd, &ps);
}

void WRendering::SetTextures(std::wstring path) {
	_textures = WTextureSet::LoadFrom(path);
}
