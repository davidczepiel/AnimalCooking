#pragma once
#include "Component.h"
#include "Interactive.h"
#include "Transport.h"
#include "Entity.h"
#include "SDLGame.h"
#include "Vector2D.h"
#include "Dish.h"
#include "Manager.h"
#include "OrderServiceViewer.h"
#include "OrderManager.h"
#include "OrderViewer.h"
#include "AIClient.h"
#include "DishPool.h"

class OrderService : public Entity, public Interactive
{
public:
	OrderService(Transport* p1, Transport* p2, EntityManager* mng, DishPool* dp);
	virtual void action1(int id);
	virtual void feedback(int player);
	OrderManager* setOrderMngr(OrderManager* om) { orderMngr = om; return orderMngr; }

private:
	OrderManager* orderMngr;
	DishPool* dp;
	bool canService(int id);

};

