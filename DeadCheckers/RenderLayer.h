#pragma once

const int RENDER_LAYERS_COUNT = 8;
enum class RenderLayer : int {
	background = 0,
	above_background_1,
	above_background_2,
	under_middle,
	middle,
	above_middle_1,
	above_middle_2,
	very_top
};