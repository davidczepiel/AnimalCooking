#pragma once
#include "Component.h"
#include "Tool.h"

class BucketViewer : public Component
{
public:
	BucketViewer(Bucket* bucketEntity) : Component(ecs::BucketViewer), bucket_(bucketEntity) {}
	~BucketViewer() {}

	void draw() override {
		bucket_->render();
	}
private:
	Bucket* bucket_;
};

