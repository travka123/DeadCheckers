#include "WRendering.h"
#include "WPainter.h"
#include "RenderLayer.h"

WRendering::WRendering(RECT clientRect, float margin, float menuWidth) {
	_textures.LoadFrom(_styles[0]);
	_currentStyle = 0;

	_clientRect = clientRect;
	_layout = Layout::GetLayout(clientRect, margin, menuWidth);
	_invalidateCache = true;
	memset(_layerNeedRedraw, true, sizeof(_layerNeedRedraw));
	memset(_layersCache, 0, sizeof(_layersCache));
	_totalCache = 0;
}

void WRendering::Render(HDC hDC) {

	HBRUSH transparentBrush = CreateSolidBrush(_textures.GetTransparentColor());

	HDC cacheDC = CreateCompatibleDC(hDC);

	if (_invalidateCache) {
		ReinitCache(hDC);
		memset(_layerNeedRedraw, true, sizeof(_layerNeedRedraw));
	}
	
	bool canUseTotalCache = true;
	WPainter painter(hDC, _clientRect, _textures, _layout);
	for (int i = 0; i < RENDER_LAYERS_COUNT; i++) {

		if (!_layerNeedRedraw[i]) {
			for (Renderable* entity : _layers[i]) {
				_layerNeedRedraw[i] = entity->NeedRedraw();
				if (_layerNeedRedraw[i]) {
					break;
				}
			}
		}

		if (_layerNeedRedraw[i]) {
			canUseTotalCache = false;

			HGDIOBJ old = SelectObject(cacheDC, _layersCache[i]);
			FillRect(cacheDC, &_clientRect, transparentBrush);
			painter.SetDC(cacheDC);

			for (Renderable* entity : _layers[i]) {
				entity->Render(painter);
			}

			painter.SetDC(hDC);
			SelectObject(cacheDC, old);
		}
	}
	
	HDC totalCacheDC = CreateCompatibleDC(hDC);
	HGDIOBJ totalOld = SelectObject(totalCacheDC, _totalCache);

	if (!canUseTotalCache) {
		painter.SetDC(totalCacheDC);
		for (int i = 0; i < RENDER_LAYERS_COUNT; i++) {
			HGDIOBJ old = SelectObject(cacheDC, _layersCache[i]);
			painter.PaintFullScreen(cacheDC, _clientRect.right, _clientRect.bottom);
			SelectObject(cacheDC, old);
		}
		painter.SetDC(hDC);
	}
	
	painter.PaintFullScreen(totalCacheDC, _clientRect.right, _clientRect.bottom);
	
	SelectObject(totalCacheDC, totalOld);
	DeleteDC(totalCacheDC);
	DeleteDC(cacheDC);

	DeleteObject(transparentBrush);

	_invalidateCache = false;
	memset(_layerNeedRedraw, false, sizeof(_layerNeedRedraw));
}

void WRendering::SetTextures(std::wstring path) {
	_textures.LoadFrom(path);
	memset(_layerNeedRedraw, true, sizeof(_layerNeedRedraw));
}

void WRendering::SetCleintRect(RECT clientRect)
{
	_clientRect = clientRect;
	_layout = Layout::GetLayout(clientRect, _layout.margin, _layout.menuWidth);
	_invalidateCache = true;
}

void WRendering::SetNextStyle()
{
	_currentStyle = (_currentStyle + 1) % _styles.size();
	_textures.LoadFrom(_styles[_currentStyle]);
	_invalidateCache = true;
}

WTextureSet& WRendering::GetTextureSet()
{
	return _textures;
}

void WRendering::ReinitCache(HDC compDC)
{
	int x = _clientRect.right - _clientRect.left;
	int y = _clientRect.bottom - _clientRect.top;
	for (int i = 0; i < RENDER_LAYERS_COUNT; i++) {
		if (_layersCache[i] != 0) {
			DeleteObject(_layersCache[i]);
		}
		_layersCache[i] = CreateCompatibleBitmap(compDC, x, y);
	}
	if (_totalCache != 0) {
		DeleteObject(_totalCache);
	}
	_totalCache = CreateCompatibleBitmap(compDC, x, y);
}
