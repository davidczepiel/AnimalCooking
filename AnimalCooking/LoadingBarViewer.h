#pragma once
#include "Component.h"
#include "Transform.h"
class LoadingBarViewer : public Component
{
public:
	LoadingBarViewer(Texture* contorno_, Texture* filler_);
	void init() override;
	void draw() override;
	void plusLength(double extra);

private:
	Transform* ownerTransform_;
	Texture* contorno_;
	Texture* filler_;

	double percentage_;
};

