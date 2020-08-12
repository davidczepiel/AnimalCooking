#pragma once
#include "Component.h"
#include "Tool.h"

class BucketMotion : public Component
{
public:
	BucketMotion(Bucket* bucketEntity) : Component(ecs::BucketMotion), bucket_(bucketEntity) {}
	~BucketMotion() {}

	void update() override;
private:
	Bucket* bucket_;
};

