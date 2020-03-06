#pragma once
class Food 
{
private:
	bool inUse_;
public:
	bool getInUse() { return inUse_; }
	void update();
	void draw();
};