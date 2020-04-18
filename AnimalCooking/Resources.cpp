#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
	{Basic, ARIAL12, "../AnimalCooking/resources/fonts/ARIAL.ttf", 12 }
};

	
	

vector<Resources::ImageInfo> Resources::images_{
	//
	{Basic, Button,"../AnimalCooking/resources/images/button.jpg"},

	{AllLevels, IngredienteMalo,"../AnimalCooking/resources/images/caca.png"},
	{AllLevels, Cooker,"../AnimalCooking/resources/images/sarten.png"},
	{AllLevels, CookerCooking,"../AnimalCooking/resources/images/sartencocinando.png"},
	{AllLevels, CookerCooked,"../AnimalCooking/resources/images/sartencooked.png"},
	{AllLevels, CookerBurned,"../AnimalCooking/resources/images/sartenburned.png"},
	{AllLevels, Platera,"../AnimalCooking/resources/images/platera.png"},
	{AllLevels, Cuchillo,"../AnimalCooking/resources/images/cuchillo.png"},
	{AllLevels, CuchilloSucio,"../AnimalCooking/resources/images/cuchilloSucio.jpg"},
	{AllLevels, Fregadero,"../AnimalCooking/resources/images/fregadero.jpg"},
	{AllLevels, Hierba,"../AnimalCooking/resources/images/hierba.jpg"},
	{AllLevels, Ingrediente,"../AnimalCooking/resources/images/ingrediente.png"},
	{AllLevels, Panera,"../AnimalCooking/resources/images/panera.png"},
	{AllLevels, Papelera,"../AnimalCooking/resources/images/papelera.png"},
	{AllLevels, Pedido,"../AnimalCooking/resources/images/pedido.png"},
	{AllLevels, Cerdo,"../AnimalCooking/resources/images/personaje.png"},
	{AllLevels, Pollo,"../AnimalCooking/resources/images/personaje2.png"},
	{AllLevels, Plato,"../AnimalCooking/resources/images/plato.png"},
	{AllLevels, Repisa,"../AnimalCooking/resources/images/repisa.png"},
	{AllLevels, Suelo,"../AnimalCooking/resources/images/suelo.png"},
	{AllLevels, CuadradoAux,"../AnimalCooking/resources/images/cuadrado.png"},
	{AllLevels, Pan,"../AnimalCooking/resources/images/pan.png"},
	{AllLevels, Aceite,"../AnimalCooking/resources/images/aceite.png"},
	{AllLevels, Arroz,"../AnimalCooking/resources/images/arroz.png"},
	
	//Foods-----------------------------------------------------------------
	{AllLevels, TextureId::Poop,"../AnimalCooking/resources/images/Foods/caca.png"},
	{AllLevels, TextureId::SlicedTomato,"../AnimalCooking/resources/images/Foods/tomateCortado.png"},
	{AllLevels, TextureId::SlicedLettuce,"../AnimalCooking/resources/images/Foods/lechugaCortada.png"},
	{AllLevels, TextureId::SlicedOnion,"../AnimalCooking/resources/images/Foods/cebollaCortado.png"},
	{AllLevels, TextureId::SlicedMeat,"../AnimalCooking/resources/images/Foods/carneCortado.png"},
	{AllLevels, TextureId::MashedMeat,"../AnimalCooking/resources/images/Foods/carneAplastada.png"},
	{AllLevels, TextureId::SlicedCheese,"../AnimalCooking/resources/images/Foods/quesoCortado.png"},
	{AllLevels, TextureId::GratedCheese,"../AnimalCooking/resources/images/Foods/quesoRallado.png"},
	{AllLevels, TextureId::SlicedPotato,"../AnimalCooking/resources/images/Foods/patataCortada.png"},
	{AllLevels, TextureId::SlicedSausage,"../AnimalCooking/resources/images/Foods/salchichaCortada.png"},
	{AllLevels, TextureId::SlicedCarrot,"../AnimalCooking/resources/images/Foods/zanahoriaCortada.png"},
	{AllLevels, TextureId::CaughtSausage,"../AnimalCooking/resources/images/Foods/salchichaRed.png"},
	{AllLevels, TextureId::SlicedMushroom,"../AnimalCooking/resources/images/Foods/champinonCortada.png"},
	{AllLevels, TextureId::CaughtFish,"../AnimalCooking/resources/images/Foods/rescadoRed.png"},
	{AllLevels, TextureId::SlicedChicken,"../AnimalCooking/resources/images/Foods/polloCortado.png"},
	{AllLevels, TextureId::CaughtClam,"../AnimalCooking/resources/images/Foods/vieraRed.png"},
	{AllLevels, TextureId::Rice,"../AnimalCooking/resources/images/Foods/arroz.png"},
	{AllLevels, TextureId::BreadBurger,"../AnimalCooking/resources/images/Foods/panHamburguesa.png"},
	{AllLevels, TextureId::BreadHotDog,"../AnimalCooking/resources/images/Foods/panPerrito.png"},
	{AllLevels, TextureId::PizzaMass,"../AnimalCooking/resources/images/Foods/masa.png"},
	{AllLevels, TextureId::Salad,"../AnimalCooking/resources/images/Foods/ensalada.png"},
	{AllLevels, TextureId::Burger,"../AnimalCooking/resources/images/Foods/hamburguesa.png"},
	{AllLevels, TextureId::Pizza,"../AnimalCooking/resources/images/Foods/pizza.png"},
	{AllLevels, TextureId::Roast,"../AnimalCooking/resources/images/Foods/asado.png"},
	{AllLevels, TextureId::RiceDish,"../AnimalCooking/resources/images/Foods/arrozDeLaCasa.png"},
	{AllLevels, TextureId::HotDog,"../AnimalCooking/resources/images/Foods/perritoCaliente.png"},
	{AllLevels, TextureId::Risotto,"../AnimalCooking/resources/images/Foods/risotto.png"},
	{AllLevels, TextureId::CookedFish,"../AnimalCooking/resources/images/Foods/pescadoAlHorno.png"},
	{AllLevels, TextureId::FriedVegs,"../AnimalCooking/resources/images/Foods/verdurasFritas.png"},
	{AllLevels, TextureId::BakedChicken,"../AnimalCooking/resources/images/Foods/pollo.png"},
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

		//Utensil
		{AllLevels, CuchilloFeedBack,"../AnimalCooking/resources/images/cuchilloFeedBack.png"},
		//General
		{AllLevels, PapelertaFeedBack,"../AnimalCooking/resources/images/papeleraFeedBack.png"},
		{AllLevels, PlatoFeedBack,"../AnimalCooking/resources/images/platoFeedBack.png"},
		{AllLevels, Panel,"../AnimalCooking/resources/images/panel.png"},
		{AllLevels, Coger,"../AnimalCooking/resources/images/coger.png"},
		{AllLevels, Dejar,"../AnimalCooking/resources/images/dejar.png"}

};

vector<Resources::TextMsgInfo> Resources::messages_{


};


vector<Resources::MusicInfo> Resources::musics_{
	//

};

vector<Resources::SoundInfo> Resources::sounds_{
	//

};

