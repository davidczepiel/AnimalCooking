#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
	{Basic, ARIAL12, "../AnimalCooking/resources/fonts/ARIAL.ttf", 12 }
};




vector<Resources::ImageInfo> Resources::images_{
	//
	{Basic, Button,"../AnimalCooking/resources/images/button.jpg"},
	{Basic, RectangleOutline,"../AnimalCooking/resources/images/rectOutline.png"},
	{Basic, SliderBackground,"../AnimalCooking/resources/images/sliderBackground.png"},
	{Basic, SliderMovPoint,"../AnimalCooking/resources/images/sliderMovepoint.png"},


	{AllLevels, Repisa,"../AnimalCooking/resources/images/repisa.png"},
	{AllLevels, Plato,"../AnimalCooking/resources/images/plato.png"},
	{AllLevels, Suelo,"../AnimalCooking/resources/images/suelo.png"},
	{AllLevels, Hierba,"../AnimalCooking/resources/images/hierba.jpg"},
	{AllLevels, Cooker,"../AnimalCooking/resources/images/sarten.png"},
	{AllLevels, CookerCooking,"../AnimalCooking/resources/images/sartencocinando.png"},
	{AllLevels, CookerBurned,"../AnimalCooking/resources/images/sartenburned.png"},
	{AllLevels, CookerCooked,"../AnimalCooking/resources/images/sartencooked.png"},
	{AllLevels, Platera,"../AnimalCooking/resources/images/platera.png"},
	{AllLevels, Cuchillo,"../AnimalCooking/resources/images/cuchillo.png"},
	{AllLevels, CuchilloSucio,"../AnimalCooking/resources/images/cuchilloSucio.jpg"},
	{AllLevels, Fregadero,"../AnimalCooking/resources/images/fregadero.jpg"},
	{AllLevels, Ingrediente,"../AnimalCooking/resources/images/ingrediente.png"},
	{AllLevels, Panera,"../AnimalCooking/resources/images/panera.png"},
	{AllLevels, Pedido,"../AnimalCooking/resources/images/pedido.png"},
	{AllLevels, Papelera,"../AnimalCooking/resources/images/papelera.png"},
	{AllLevels, Cerdo,"../AnimalCooking/resources/images/personaje.png"},
	{AllLevels, Pollo,"../AnimalCooking/resources/images/personaje2.png"},
	{AllLevels, CuadradoAux,"../AnimalCooking/resources/images/cuadrado.png"},

	{Basic,level0Menu,"../AnimalCooking/resources/images/level0Menu.png"},
	{Basic,level1Menu,"../AnimalCooking/resources/images/level1Menu.png"},
	{Basic,level2Menu,"../AnimalCooking/resources/images/level2Menu.png"},
	{Basic,level3Menu,"../AnimalCooking/resources/images/level3Menu.png"},
	{Basic,level4Menu,"../AnimalCooking/resources/images/level4Menu.png"},

	//Pedidos--------------------------------------------------------------
	{Basic,Bocadillo,"../AnimalCooking/resources/images/Pedidos/bocadillo.png"},
	{AllLevels,SaladOrder,"../AnimalCooking/resources/images/Pedidos/ensalada.png"},
	{AllLevels,BurgerOrder,"../AnimalCooking/resources/images/Pedidos/hamburguesa.png"},
	{AllLevels,PizzaOrder,"../AnimalCooking/resources/images/Pedidos/pizza.png"},
	{AllLevels,RoastOrder,"../AnimalCooking/resources/images/Pedidos/asado.png"},
	{AllLevels,RiceDishOrder,"../AnimalCooking/resources/images/Pedidos/arrozCasa.png"},
	{AllLevels,HotDogOrder,"../AnimalCooking/resources/images/Pedidos/hotdog.png"},
	{AllLevels,RisottoOrder,"../AnimalCooking/resources/images/Pedidos/risotto.png"},
	{AllLevels,CookedFishOrder,"../AnimalCooking/resources/images/Pedidos/pescadoAlHorno.png"},
	{AllLevels,FriedVegsOrder,"../AnimalCooking/resources/images/Pedidos/verdurasFritas.png"},
	{AllLevels,BakedChickenOrder,"../AnimalCooking/resources/images/Pedidos/polloAsado.png"},
	{AllLevels,FrenchFriesOrder,"../AnimalCooking/resources/images/Pedidos/patatasFristas.png"},
	{AllLevels,CookedClamsOrder,"../AnimalCooking/resources/images/Pedidos/vieira.png"},
	{AllLevels,RiceAndClamsOrder,"../AnimalCooking/resources/images/Pedidos/mariscoConArroz.png"},

	
	//Foods-----------------------------------------------------------------
	{AllLevels, TextureId::PoopT,"../AnimalCooking/resources/images/Foods/caca.png"},
	{AllLevels, TextureId::SlicedTomatoT,"../AnimalCooking/resources/images/Foods/tomateCortado.png"},
	{AllLevels, TextureId::SlicedLettuceT,"../AnimalCooking/resources/images/Foods/lechugaCortada.png"},
	{AllLevels, TextureId::SlicedOnionT,"../AnimalCooking/resources/images/Foods/cebollaCortado.png"},
	{AllLevels, TextureId::SlicedMeatT,"../AnimalCooking/resources/images/Foods/carneCortado.png"},
	{AllLevels, TextureId::MashedMeatT,"../AnimalCooking/resources/images/Foods/carneAplastada.png"},
	{AllLevels, TextureId::SlicedCheeseT,"../AnimalCooking/resources/images/Foods/quesoCortado.png"},
	{AllLevels, TextureId::GratedCheeseT,"../AnimalCooking/resources/images/Foods/quesoRallado.png"},
	{AllLevels, TextureId::SlicedPotatoT,"../AnimalCooking/resources/images/Foods/patataCortada.png"},
	{AllLevels, TextureId::SlicedSausageT,"../AnimalCooking/resources/images/Foods/salchichaCortada.png"},
	{AllLevels, TextureId::SlicedCarrotT,"../AnimalCooking/resources/images/Foods/zanahoriaCortada.png"},
	{AllLevels, TextureId::CaughtSausageT,"../AnimalCooking/resources/images/Foods/salchichaRed.png"},
	{AllLevels, TextureId::SlicedMushroomT,"../AnimalCooking/resources/images/Foods/champinonCortada.png"},
	{AllLevels, TextureId::CaughtFishT,"../AnimalCooking/resources/images/Foods/rescadoRed.png"},
	{AllLevels, TextureId::SlicedChickenT,"../AnimalCooking/resources/images/Foods/polloCortado.png"},
	{AllLevels, TextureId::CaughtClamT,"../AnimalCooking/resources/images/Foods/vieraRed.png"},
	{AllLevels, TextureId::RiceT,"../AnimalCooking/resources/images/Foods/arroz.png"},
	{AllLevels, TextureId::BreadBurgerT,"../AnimalCooking/resources/images/Foods/panHamburguesa.png"},
	{AllLevels, TextureId::BreadHotDogT,"../AnimalCooking/resources/images/Foods/panPerrito.png"},
	{AllLevels, TextureId::PizzaMassT,"../AnimalCooking/resources/images/Foods/masa.png"},
	{AllLevels, TextureId::SaladT,"../AnimalCooking/resources/images/Foods/ensalada.png"},
	{AllLevels, TextureId::BurgerT,"../AnimalCooking/resources/images/Foods/hamburguesa.png"},
	{AllLevels, TextureId::PizzaT,"../AnimalCooking/resources/images/Foods/pizza.png"},
	{AllLevels, TextureId::RoastT,"../AnimalCooking/resources/images/Foods/asado.png"},
	{AllLevels, TextureId::RiceDishT,"../AnimalCooking/resources/images/Foods/arrozDeLaCasa.png"},
	{AllLevels, TextureId::HotDogT,"../AnimalCooking/resources/images/Foods/perritoCaliente.png"},
	{AllLevels, TextureId::RisottoT,"../AnimalCooking/resources/images/Foods/risotto.png"},
	{AllLevels, TextureId::CookedFishT,"../AnimalCooking/resources/images/Foods/pescadoAlHorno.png"},
	{AllLevels, TextureId::FriedVegsT,"../AnimalCooking/resources/images/Foods/verdurasFritas.png"},
	{AllLevels, TextureId::BakedChickenT,"../AnimalCooking/resources/images/Foods/pollo.png"},
	{AllLevels, TextureId::FrenchFriesT,"../AnimalCooking/resources/images/Foods/patatasFritas.png"},
	{AllLevels, TextureId::CookedClamsT,"../AnimalCooking/resources/images/Foods/vieraGratinada.png"},
	{AllLevels, TextureId::RiceAndClamsT,"../AnimalCooking/resources/images/Foods/mariscoConArroz.png"},
	{AllLevels, TextureId::MashedMeatSkilletT,"../AnimalCooking/resources/images/Foods/carneSarten.png"},
	{AllLevels, TextureId::CaughtSausageSkilletT,"../AnimalCooking/resources/images/Foods/salchichaSarten.png"},
	{AllLevels, TextureId::SlicedPotatoSkilletT,"../AnimalCooking/resources/images/Foods/patatasSarten.png"},
	{AllLevels, TextureId::DressT,"../AnimalCooking/resources/images/Foods/dress.png"},
	{AllLevels, TextureId::MashedTomatoT,"../AnimalCooking/resources/images/Foods/tomateAplastado.png"},
	//FeedBack---------------------------------------------------------------
		//Food
		{AllLevels, PoopFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/caca.png"},
		{AllLevels, SlicedTomatoFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/tomateCortado.png"},
		{AllLevels, SlicedLettuceFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/lechugaCortada.png"},
		{AllLevels, SlicedOnionFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/cebollaCortado.png"},
		{AllLevels, SlicedMeatFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/carneCortado.png"},
		{AllLevels, MashedMeatFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/carneAplastada.png"},
		{AllLevels, SlicedCheeseFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/quesoCortado.png"},
		{AllLevels, GratedCheeseFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/quesoRallado.png"},
		{AllLevels, SlicedPotatoFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/patataCortada.png"},
		{AllLevels, SlicedSausageFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/salchichaCortada.png"},
		{AllLevels, SlicedCarrotFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/zanahoriaCortada.png"},
		{AllLevels, CaughtSausageFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/salchichaRed.png"},
		{AllLevels, SlicedMushroomFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/champinonCortada.png"},
		{AllLevels, CaughtFishFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/rescadoRed.png"},
		{AllLevels, SlicedChickenFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/polloCortado.png"},
		{AllLevels, RiceFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/arroz.png"},
		{AllLevels, BreadBurgerFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/panHamburguesa.png"},
		{AllLevels, BreadHotDogFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/panPerrito.png"},
		{AllLevels, PizzaMassFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/masa.png"},
		{AllLevels, SaladFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/ensalada.png"},
		{AllLevels, BurgerFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/hamburguesa.png"},
		{AllLevels, PizzaFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/pizza.png"},
		{AllLevels, RoastFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/asado.png"},
		{AllLevels, RiceDishFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/arrozDeLaCasa.png"},
		{AllLevels, HotDogFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/perritoCaliente.png"},
		{AllLevels, RisottoFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/risotto.png"},
		{AllLevels, CookedFishFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/pescadoAlHorno.png"},
		{AllLevels, FriedVegsFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/verdurasFritas.png"},
		{AllLevels, BakedChickenFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/pollo.png"},
		{AllLevels, FrenchFriesFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/patatasFritas.png"},
		{AllLevels, CookedClamsFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/vieraGratinada.png"},
		{AllLevels, RiceAndClamsFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/mariscoConArroz.png"},
		{AllLevels, MashedMeatSkilletFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/carneAplastada.png"},
		{AllLevels, CaughtSausageSkilletFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/salchichaSarten.png"},
		{AllLevels, SlicedPotatoSkilletFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/patatasSarten.png"},
		{AllLevels, DressFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/dress.png"},
		{AllLevels, MashedTomatoFeedBack,"../AnimalCooking/resources/images/FeedBack/Food/tomateAplastado.png"},

		//Utensil
		{AllLevels, CuchilloFeedBack,"../AnimalCooking/resources/images/FeedBack/Utensil/cuchilloFeedBack.png"},
		//General
		{AllLevels, PapeleraFeedBack,"../AnimalCooking/resources/images/FeedBack/General/papeleraFeedBack.png"},
		{AllLevels, PlatoFeedBack,"../AnimalCooking/resources/images/FeedBack/General/platoFeedBack.png"},
		{AllLevels, Panel,"../AnimalCooking/resources/images/FeedBack/General/panel.png"},
		{AllLevels, Coger,"../AnimalCooking/resources/images/FeedBack/General/coger.png"},
		{AllLevels, Dejar,"../AnimalCooking/resources/images/FeedBack/General/dejar.png"},

	// images level specific
	{AllLevels, Aceite,"../AnimalCooking/resources/images/aceite.png"},
	{AllLevels, Arroz,"../AnimalCooking/resources/images/arroz.png"}
};

vector<Resources::SpritesheetInfo> Resources::spritesheets_{
	//
	{Basic, CircularTimer,"../AnimalCooking/resources/images/circleTimer.png", 1, 8},
	{Basic, BurnedTimer,"../AnimalCooking/resources/images/burningTimer.png", 1, 8}
	
};

vector<Resources::TextMsgInfo> Resources::messages_{


};


vector<Resources::MusicInfo> Resources::musics_{
	//

};

vector<Resources::SoundInfo> Resources::sounds_{
	//

};

