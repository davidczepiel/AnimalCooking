#pragma once
#include "OrderManager.h"

class OrderViewer : public Component {
public:
	OrderViewer();
	OrderViewer(size_t width, size_t height, Vector2D margin);

	void init() override;
	void draw() override;
private:
	Texture* backGroundTexture_;
	OrderManager* om_;
	size_t width_, height_;
	Vector2D margin_;
};