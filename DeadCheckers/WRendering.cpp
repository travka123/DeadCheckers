#include "WRendering.h"

#include "WPainter.h"

void WRendering::Render(HWND hWnd) {
	PAINTSTRUCT ps;

	BeginPaint(hWnd, &ps);

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	WPainter canvas(ps.hdc, clientRect, _textures);

	for (int i = 0; i < renderLayersCount; i++) {
		for (IRenderable* entity : _entities[i]) {
			entity->Render(&canvas);
		}
	}

	EndPaint(hWnd, &ps);
}

void WRendering::SetTextures(std::wstring path) {
	_textures = WTextureSet::LoadFrom(path);
}
