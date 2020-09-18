#pragma once
#include "Component.h"
#include "Transform.h"
#include "MapConfig.h"
#include <functional>
class ButtonRenderer;
class AnimalCooking;
class ButtonPadNavigation;

class ButtonBehaviourNC : public Component{
public:
	ButtonBehaviourNC(Entity * infoBox, levelInfo* info);
	ButtonBehaviourNC(bool profilechooser, const string& name = "");

	void init() override;
	void update() override; 
	void action();

	void setButtonRenderer(ButtonRenderer* bR) { bRenderer_ = bR; }
	void setLevelInfo(levelInfo* info) { mapInfo_ = info; }
	const bool& getFocusByMouse() { return focusedByMouse_; }
	const bool& getFocusByController() { return focusedByController_; }
	void setFocusByController(bool f);
	inline bool isActive() { return active_; }
	inline void setActive(bool active) { active_ = active; }
	inline const string& getName() const { return name_; }
	void setButtonPadNavigation(ButtonPadNavigation* b) { butPadNav_ = b; }
	levelInfo* getLevelInfo() { return mapInfo_; }

private:
	levelInfo* mapInfo_;
	Entity* infoBox_;	
	Transform* ownerTransform_;
	AnimalCooking* ac_;
	ButtonRenderer* bRenderer_;
	ButtonPadNavigation* butPadNav_;
	string name_;

	bool active_;
	bool focusedByMouse_;
	bool focusedByController_;
	int action_;	
};