#pragma once
#include "Vector2D.h"
#include <SDL_stdinc.h>
#include "Texture.h"
#include "Timer.h"
#include "Interactive.h"
#include "Entity.h"

enum class CookerStates { empty, cooking, cooked, burned, overheated };
class Food;
class InsertExpel;
class Cooker :public Interactive {
public:
	virtual ~Cooker();
	virtual void draw();
	void action1(int player)override;
	void feedback(int player) override;
	void sound();

	void setCookerState(CookerStates s);
	inline CookerStates getCookerState() { return state_; };

	virtual void setEmptyTexture() = 0;
	virtual void setBurnedTexture() = 0;
	virtual void setCookingTexture() = 0;
	virtual void setOverHeatedTexture() = 0;

	Timer* getCookerTimer() { return timer_; };
	Uint32 getCookingTime() { return cookingTime_; }
	vector<Food*>& getFoods() { return foods_; }

	inline int getCookerType() { return (int)cookerType_; };

protected:
	Cooker(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e,string textureState);
	void initTimer();

	Texture* texture_;
	Texture* smokeTexture_;
	Texture* fireTexture_;
	Entity* entity_;
	CookerTimer* timer_;
	vector<Food*> foods_;
	CookerStates state_;
	Uint32 cookingTime_;
	Uint32 lastTimeSound_;
	Resources::Cookers cookerType_;
	string textureState;
};

class Oven : public Cooker {
public:
	Oven(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e, string textureState_);

	virtual void setEmptyTexture() override 
	{ 
		if(textureState == "HornoDer") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenDerOFF);
		else if(textureState == "HornoIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenIzqOFF);
		else if(textureState == "HornoBordes") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFFBordes);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF);
		 
	};

	virtual void setBurnedTexture() override 
	{ 
		if (textureState == "HornoDer") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenDerON);
		else if (textureState == "HornoIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenIzqON);
		else if (textureState == "HornoBordes") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenONBordes);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON); 
	};

	virtual void setCookingTexture() override 
	{ 
		if (textureState == "HornoDer") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenDerON);
		else if (textureState == "HornoIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenIzqON);
		else if (textureState == "HornoBordes") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenONBordes);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenON);
	};

	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};

class Skillet : public Cooker {
public:
	Skillet(Vector2D& pos, Vector2D& size, double rot, Texture* text, Transport* t1, Transport* t2, Entity* e, string textureState_);

	virtual void setEmptyTexture() override 
	{ 
		if(textureState=="corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFEsquina);
		else if(textureState == "borde") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFBorde);
		else if(textureState == "Arriba") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFArriba);
		else if(textureState == "ArribaDecoracion") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFArribaDecoracion);
		else if (textureState == "SartenBordeAmbos") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFBordeAmbos);
		else if(textureState == "SartenEsqIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFFEsquinaIzq);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletOFF);
	};

	virtual void setBurnedTexture() override 
	{ 
		if (textureState == "corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquina);
		else if(textureState == "borde")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONBorde);
		else if (textureState == "Arriba") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONArriba);
		else if (textureState == "ArribaDecoracion") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONArribaDecoracion);
		else if (textureState == "SartenBordeAmbos") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONBordeAmbos);
		else if (textureState == "SartenEsqIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquinaIzq);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); 
	};

	virtual void setCookingTexture() override 
	{ 
		if (textureState == "corner")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquina);
		else if (textureState == "borde")texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONBorde);
		else if (textureState == "Arriba") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONArriba);
		else if (textureState == "ArribaDecoracion") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONArribaDecoracion);
		else if (textureState == "SartenBordeAmbos") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONBordeAmbos);
		else if (textureState == "SartenEsqIzq") texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletONEsquinaIzq);
		else texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SkilletON); 
	};

	virtual void setOverHeatedTexture() override { texture_ = SDLGame::instance()->getTextureMngr()->getTexture(Resources::OvenOFF); };
};