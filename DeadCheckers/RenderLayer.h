#pragma once

enum class RenderLayer : int {
	background = 0,
	above_background,
	under_middle,
	middle,
	above_middle,
	very_top,

	LAYERS_COUNT
};