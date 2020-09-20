#include "GameControlLevelIngredientsChanger.h"
#include "GameControl.h"
#include "Entity.h"

GameControlLevelIngredientsChanger::GameControlLevelIngredientsChanger(const initializer_list<int>& times, TimerViewer* tv) : Component(ecs::GameControlLevelIngredientsChanger),
groups_(), gControl_(nullptr), timer(nullptr), times_(times)
{

	groups_.push({ Resources::IngredientType::tomato, Resources::IngredientType::lettuce, Resources::IngredientType::carrot, Resources::IngredientType::onion, 
		Resources::IngredientType::meat, Resources::IngredientType::mushroom, Resources::IngredientType::potato,Resources::IngredientType::cheese });
	
	groups_.push({ Resources::IngredientType::sausage, Resources::IngredientType::tomato, Resources::IngredientType::fish, Resources::IngredientType::carrot, 
		Resources::IngredientType::onion, Resources::IngredientType::cheese, Resources::IngredientType::mushroom, Resources::IngredientType::potato, 
		Resources::IngredientType::chicken, Resources::IngredientType::clam,Resources::IngredientType::lettuce});

	groups_.push({ Resources::IngredientType::sausage, Resources::IngredientType::tomato, Resources::IngredientType::fish, Resources::IngredientType::carrot,
		Resources::IngredientType::onion, Resources::IngredientType::mushroom, Resources::IngredientType::potato, Resources::IngredientType::chicken, 
		Resources::IngredientType::clam, Resources::IngredientType::snowman, Resources::IngredientType::salmon, Resources::IngredientType::avocado,
		Resources::IngredientType::lettuce });
	
	groups_.push({ Resources::IngredientType::tomato, Resources::IngredientType::cheese, Resources::IngredientType::onion, Resources::IngredientType::chicken,
		Resources::IngredientType::mushroom, Resources::IngredientType::meat, Resources::IngredientType::sausage, Resources::IngredientType::potato});

	timer = new Timer();
	timer->setTime(times_.front() * 1000); times_.pop();
	tv->addTimer(timer);
}


void GameControlLevelIngredientsChanger::update()
{
	timer->update();
	if (timer->isTimerEnd()) {
		if (!groups_.empty()) { gControl_->setIngs(groups_.front()); groups_.pop();  }
		if (!times_.empty()) {
			timer->setTime(times_.front() * 1000); times_.pop();
			timer->timerReset();
			timer->timerStart();
		}
	}
}

void GameControlLevelIngredientsChanger::setGameControl(GameControl* gC)
{
	gControl_ = gC; gControl_->setIngs(groups_.front()); groups_.pop(); 
}
