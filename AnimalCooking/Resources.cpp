#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
	{Basic, ARIAL12, "../AnimalCooking/resources/fonts/ARIAL.ttf", 12 },
	{Basic, QuarkCheese100, "../AnimalCooking/resources/fonts/QuarkCheese.otf", 100 },
	{Basic, QuarkCheese70, "../AnimalCooking/resources/fonts/QuarkCheese.otf", 70 },
	{Basic, QuarkCheese50, "../AnimalCooking/resources/fonts/QuarkCheese.otf", 50 }
};




vector<Resources::ImageInfo> Resources::images_{
	//	
	{Basic, LevelTimerBackground,"../AnimalCooking/resources/images/barraSinCargar.png"},
	{Basic, LevelTimerForeground,"../AnimalCooking/resources/images/cargaBarra.png"},
	{Basic, ScoreBackground,"../AnimalCooking/resources/images/ScoreBackground.png"},
	{Basic, RectangleOutline,"../AnimalCooking/resources/images/rectOutline.png"},
	{Basic, SliderBackground,"../AnimalCooking/resources/images/sliderBackground.png"},
	{Basic, SliderMovPoint,"../AnimalCooking/resources/images/sliderMovepoint.png"},
	{Basic, MainMenuBackground,"../AnimalCooking/resources/images/Menu/mainmenu.png"},
	{Basic, MainMenuRuedecilla,"../AnimalCooking/resources/images/Menu/Boton/boton.png"},
	{Basic, MainMenuRuedecillaShadow,"../AnimalCooking/resources/images/Menu/Boton/sombraboton.png"},
	{Basic, MainMenuArrow,"../AnimalCooking/resources/images/Menu/Boton/flecha.png"},
	{Basic, MainMenuArrowR,"../AnimalCooking/resources/images/Menu/Boton/flechar.png"},
	{Basic, MainMenuPlayButton,"../AnimalCooking/resources/images/Menu/Boton/playButton.png"},
	{Basic, MainMenuConfigButton,"../AnimalCooking/resources/images/Menu/Boton/configButton.png"},
	{Basic, MainMenuExitButton,"../AnimalCooking/resources/images/Menu/Boton/exitButton.png"},
	{Basic, MainMenuCreditsButton,"../AnimalCooking/resources/images/Menu/Boton/creditsButton.png"},
	{Basic, HomeIcon,"../AnimalCooking/resources/images/HomeProvisional.png"},
	{Basic, MapIcon,"../AnimalCooking/resources/images/MapProvisional.png"},
	{Basic, ReplayIcon,"../AnimalCooking/resources/images/ReplayProvisional.png"},
	{Basic, NextLevelIcon,"../AnimalCooking/resources/images/PlayProvisional.png"},
	{Basic, Star,"../AnimalCooking/resources/images/star.png"},
	{Basic, YellowStar,"../AnimalCooking/resources/images/YellowStar.png"},
	{Basic, LimitSign,"../AnimalCooking/resources/images/Indicador.png"},

	//MapState
	{ Basic, MapStateBackground, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStateHousesBackground, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStateHouseButton, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStateHouseButtonOver, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStatePlayButton, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStateReturnButton, "../AnimalCooking/resources/images/Adversities/plane.png" },
	{ Basic, MapStateInfoBox, "../AnimalCooking/resources/images/Adversities/plane.png" },

	{AllLevels, Repisa,"../AnimalCooking/resources/images/repisa.png"},
	{AllLevels, Plato,"../AnimalCooking/resources/images/Cocina/pickable/plato.png"},
	{AllLevels, Suelo,"../AnimalCooking/resources/images/Cocina/sueloCocina.png"},
	{AllLevels, Hierba,"../AnimalCooking/resources/images/Cocina/sueloHierba.png"},
	{AllLevels, OvenOFF,"../AnimalCooking/resources/images/Cocina/cookers/hornoOff.png"},
	{AllLevels, SkilletOFF,"../AnimalCooking/resources/images/Cocina/cookers/sartenOff.png"},
	{AllLevels, CookerCooking,"../AnimalCooking/resources/images/sartencocinando.png"},
	{AllLevels, CookerBurned,"../AnimalCooking/resources/images/sartenburned.png"},
	{AllLevels, CookerCooked,"../AnimalCooking/resources/images/sartencooked.png"},
	{AllLevels, CookerOverHeated,"../AnimalCooking/resources/images/sartenoverheated.png" },
	{AllLevels, Platera,"../AnimalCooking/resources/images/Cocina/platos.png"},
	{AllLevels, Muro,"../AnimalCooking/resources/images/Cocina/muro.png"},
	{AllLevels, Valla,"../AnimalCooking/resources/images/Cocina/valla.png"},
	{AllLevels, VallaFinal,"../AnimalCooking/resources/images/Cocina/vallaFinal.png"},
	{AllLevels, VallaInicio,"../AnimalCooking/resources/images/Cocina/vallainicio.png"},
	{AllLevels, Collider,"../AnimalCooking/resources/images/Cocina/vacio.png"},
	{AllLevels, VallaAbajo,"../AnimalCooking/resources/images/Cocina/vallaAbajo.png"},
	//Utensilios
	{AllLevels, Cuchillo,"../AnimalCooking/resources/images/Cocina/pickable/cuchillo.png"},
	{AllLevels, CuchilloSucio,"../AnimalCooking/resources/images/Cocina/pickable/cuchilloSucio.png"},
	{AllLevels, Maza,"../AnimalCooking/resources/images/Cocina/pickable/maza.png"},
	{AllLevels, MazaSucia,"../AnimalCooking/resources/images/Cocina/pickable/mazaSucia.png"},
	{AllLevels, Rallador,"../AnimalCooking/resources/images/Cocina/pickable/rallador.png"},
	{AllLevels, RalladorSucio,"../AnimalCooking/resources/images/Cocina/pickable/ralladorSucio.png"},
	{AllLevels, Red,"../AnimalCooking/resources/images/Cocina/pickable/red.png"},
	{AllLevels, RedSucia,"../AnimalCooking/resources/images/Cocina/pickable/redSucia.png"},

	{AllLevels, Fregadero,"../AnimalCooking/resources/images/Cocina/fregadero.png"},
	{AllLevels, FregaderoON,"../AnimalCooking/resources/images/Cocina/fregaderoOn.png"},
	{AllLevels, Ingrediente,"../AnimalCooking/resources/images/ingrediente.png"},
	{AllLevels, Panera,"../AnimalCooking/resources/images/Cocina/foodgivers/panera.png"},
	{AllLevels, Pedido,"../AnimalCooking/resources/images/pedido.png"},
	{AllLevels, Papelera,"../AnimalCooking/resources/images/Cocina/basura.png"},
	//Personajes
	{AllLevels, Cerdo,"../AnimalCooking/resources/images/personaje.png"},
	{AllLevels, Pollo,"../AnimalCooking/resources/images/personaje2.png"},
	{AllLevels, CuadradoAux,"../AnimalCooking/resources/images/cuadrado.png"},
	//Barra entregas
	{AllLevels, BarraDcha,"../AnimalCooking/resources/images/Cocina/barra/barraDcha.png"},
	{AllLevels, BarraIzda,"../AnimalCooking/resources/images/Cocina/barra/barraIzq.png"},
	{AllLevels, BarraCentro,"../AnimalCooking/resources/images/Cocina/barra/barraCentro.png"},
	{AllLevels, BarraConTimbre,"../AnimalCooking/resources/images/Cocina/barra/barraCocinaCon.png"},
	{AllLevels, BarraSinTimbre,"../AnimalCooking/resources/images/Cocina/barra/barraCocinaSin.png"},
	//Menu
	{Basic,level0Menu,"../AnimalCooking/resources/images/level0Menu.png"},
	{Basic,level1Menu,"../AnimalCooking/resources/images/level1Menu.png"},
	{Basic,level2Menu,"../AnimalCooking/resources/images/level2Menu.png"},
	{Basic,level3Menu,"../AnimalCooking/resources/images/level3Menu.png"},
	{Basic,level4Menu,"../AnimalCooking/resources/images/level4Menu.png"},
	//Encimera
	{AllLevels,EncimeraAbajoConMantel,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoCon.png"},
	{AllLevels,EncimeraAbajoConMantelDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoConDcha.png"},
	{AllLevels,EncimeraAbajoConMantelIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoConIzq.png"},
	{AllLevels,EncimeraAbajoSinMantel,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoSin.png"},
	{AllLevels,EncimeraAbajoSinMantelDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoSinDcha.png"},
	{AllLevels,EncimeraAbajoSinMantelIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraAbajoSinIzq.png"},
	{AllLevels,EncimeraHorizConMantel,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraHorizCon.png"},
	{AllLevels,EncimeraHorizSinMantel,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraHorizSin.png"},
	{AllLevels,EncimeraVertConMantelDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVertCon.png"},
	{AllLevels,EncimeraVertConMantelIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVertCon.png"},
	{AllLevels,EncimeraVertSinMantelDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVertSin.png"},
	{AllLevels,EncimeraVertSinMantelIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVertSin.png"},
	{AllLevels,EncimeraVEsquinaInferiorIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVEsquinaInferior2.png"},
	{AllLevels,EncimeraVEsquinaInferiorDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVEsquinaInferior.png"},
	{AllLevels,EncimeraVEsquinaSuperiorDcha,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVEsquinaSuperior.png"},
	{AllLevels,EncimeraVEsquinaSuperiorIzda,"../AnimalCooking/resources/images/Cocina/encimeras/encimeraVEsquinaSuperior.png"},
	//Esquinas
	{AllLevels,EsquinaSupDchaCopas,"../AnimalCooking/resources/images/Cocina/esquinas/esquina1-1.png"},
	{AllLevels,EsquinaSupIzdaCopas,"../AnimalCooking/resources/images/Cocina/esquinas/esquina1-2.png"},
	{AllLevels,EsquinaSupDchaVino,"../AnimalCooking/resources/images/Cocina/esquinas/esquina2-1.png"},
	{AllLevels,EsquinaSupIzdaVino,"../AnimalCooking/resources/images/Cocina/esquinas/esquina2-2.png"},
	{AllLevels,EsquinaSupDchaAgua,"../AnimalCooking/resources/images/Cocina/esquinas/esquina3-1.png"},
	{AllLevels,EsquinaSupIzdaAgua,"../AnimalCooking/resources/images/Cocina/esquinas/esquina3-2.png"},
	{AllLevels,EsquinaSupDchaVacia,"../AnimalCooking/resources/images/Cocina/esquinas/esquina4-1.png"},
	{AllLevels,EsquinaSupIzdaVacia,"../AnimalCooking/resources/images/Cocina/esquinas/esquina4-2.png"},

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
	{AllLevels, MazoFeedBack,"../AnimalCooking/resources/images/FeedBack/Utensil/mazaFeedBack.png"},
	{AllLevels, RedFeedBack,"../AnimalCooking/resources/images/FeedBack/Utensil/redFeedBack.png"},
	{AllLevels, RalladorFeedBack,"../AnimalCooking/resources/images/FeedBack/Utensil/ralladorFeedBack.png"},
	//General
	{AllLevels, PapeleraFeedBack,"../AnimalCooking/resources/images/FeedBack/General/papeleraFeedBack.png"},
	{AllLevels, PlatoFeedBack,"../AnimalCooking/resources/images/FeedBack/General/platoFeedBack.png"},
	{AllLevels, VerContenidoPlato,"../AnimalCooking/resources/images/FeedBack/General/verPlato.png"},
	{AllLevels, EntregarPedido,"../AnimalCooking/resources/images/FeedBack/General/entregarPedido.png"},
	{AllLevels, Panel,"../AnimalCooking/resources/images/FeedBack/General/panel.png"},
	{AllLevels, Coger,"../AnimalCooking/resources/images/FeedBack/General/coger.png"},
	{AllLevels, Dejar,"../AnimalCooking/resources/images/FeedBack/General/dejar.png"},

	// images level specific
	{AllLevels, Aceite,"../AnimalCooking/resources/images/Cocina/foodgivers/alino.png"},
	{AllLevels, Arroz,"../AnimalCooking/resources/images/Cocina/foodgivers/arrocera.png"},
	{AllLevels, EncimeraMasa,"../AnimalCooking/resources/images/Cocina/foodgivers/encimeraMasa.png"},

	// Adversities
	{AllLevels, WarningAdversity, "../AnimalCooking/resources/images/Adversities/WarningAdversity.png"},
	{AllLevels, PlaneShadow, "../AnimalCooking/resources/images/Adversities/plane.png"}	
};

vector<Resources::SpritesheetInfo> Resources::spritesheets_{
	//
	{Basic, Button,"../AnimalCooking/resources/images/Menu/botones.png", 1, 3},
	{AllLevels, CircularTimer,"../AnimalCooking/resources/images/circleTimer.png", 1, 8},
	{AllLevels, BurnedTimer,"../AnimalCooking/resources/images/burningTimer.png", 1, 8},
	{AllLevels, OvenON,"../AnimalCooking/resources/images/Cocina/cookers/hornoOn.png", 3, 1},
	{AllLevels, SkilletON,"../AnimalCooking/resources/images/Cocina/cookers/sartenOn.png", 3, 1},
    {AllLevels, PigIdle, "../AnimalCooking/resources/images/Animaciones/Cerdo/idle.png",12,8},
	{AllLevels, PigWalk, "../AnimalCooking/resources/images/Animaciones/Cerdo/andar.png",12,4},
	{AllLevels, PigAttack, "../AnimalCooking/resources/images/Animaciones/Cerdo/ataque.png",8,2},
	{AllLevels, ChickenIdle, "../AnimalCooking/resources/images/Animaciones/Gallina/idle.png",12,8},
	{AllLevels, ChickenWalk, "../AnimalCooking/resources/images/Animaciones/Gallina/andar.png",12,4},
	{AllLevels, ChickenAttack, "../AnimalCooking/resources/images/Animaciones/Gallina/ataque.png",8,2},
    {AllLevels, Tomato,"../AnimalCooking/resources/images/Ingredientes/tomate.png",3,2},
	{AllLevels, Potato,"../AnimalCooking/resources/images/Ingredientes/patata.png",3,2},
	{AllLevels, Clam,"../AnimalCooking/resources/images/Ingredientes/vieira.png",3,2},
	{AllLevels, Cheese,"../AnimalCooking/resources/images/Ingredientes/queso.png",3,2},
	{AllLevels, Meat,"../AnimalCooking/resources/images/Ingredientes/carne.png",3,2},
	{AllLevels, Lettuce,"../AnimalCooking/resources/images/Ingredientes/lechuga.png",3,2},
	{AllLevels, Mushroom,"../AnimalCooking/resources/images/Ingredientes/champi.png",3,2},
	{AllLevels, Onion,"../AnimalCooking/resources/images/Ingredientes/cebolla.png",3,2},
	{AllLevels, Fish,"../AnimalCooking/resources/images/Ingredientes/pescado.png",3,2},
	{AllLevels, Chicken,"../AnimalCooking/resources/images/Ingredientes/pollo.png",3,2},
	{AllLevels, Carrot,"../AnimalCooking/resources/images/Ingredientes/zanahoria.png",3,2},
	{AllLevels, Sausage,"../AnimalCooking/resources/images/Ingredientes/salchicha.png",3,2},
	{AllLevels, Puerta,"../AnimalCooking/resources/images/Cocina/puerta2.png",1,4}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	{Basic, TextureId::Back, "Return", COLOR(0x8811ffff), FontId::QuarkCheese100},
	{Basic, TextureId::ToggleFullscreen, "Toggle fullscreen", COLOR(0x8811ffff), FontId::QuarkCheese100},
	{Basic, TextureId::MusicVolume, "Music Volume", COLOR(0x8811ffff), FontId::QuarkCheese100},
	{Basic, TextureId::SoundVolume, "Sound Effects Volume", COLOR(0x8811ffff), FontId::QuarkCheese100}
};


vector<Resources::MusicInfo> Resources::musics_{
	//
	{Basic, MenuInicio, "../AnimalCooking/resources/sounds/Menu_inicio.ogg"},
	{AllLevels, Level1, "../AnimalCooking/resources/sounds/Ingame piano.ogg"}
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{AllLevels, KnifeAttack,"../AnimalCooking/resources/sounds/Cuchillo 1.wav"},
	{AllLevels, DropDish,"../AnimalCooking/resources/sounds/Dejar Plato 1.wav"}, //
	{AllLevels, CompleteDish,"../AnimalCooking/resources/sounds/Elaborar Plato 1.wav"},//
	{AllLevels, Wash,"../AnimalCooking/resources/sounds/Fregar 1.wav"},
	{AllLevels, FrySound,"../AnimalCooking/resources/sounds/Freir Loop 2.wav"},
	{AllLevels, MaceAttack,"../AnimalCooking/resources/sounds/Golpe Mazo 1.wav"},
	{AllLevels, MicroWave,"../AnimalCooking/resources/sounds/Microondas Beep.wav"},
	{AllLevels, Door,"../AnimalCooking/resources/sounds/Puerta 1.wav"},
	{AllLevels, FrySoundBurned,"../AnimalCooking/resources/sounds/Freir Quemar.wav" },
	{AllLevels, Bin,"../AnimalCooking/resources/sounds/Basura 2.wav" },
	{AllLevels, PickUp,"../AnimalCooking/resources/sounds/Bop nuevo 4.wav" },
	{AllLevels, Drop,"../AnimalCooking/resources/sounds/Dejar Caer 4.wav" },
	{AllLevels, AttackMiss,"../AnimalCooking/resources/sounds/Golpe fallido 3.wav" },
	{AllLevels, BurnedBeep,"../AnimalCooking/resources/sounds/Microondas Temporizador.wav" },
	{AllLevels, CookedFood,"../AnimalCooking/resources/sounds/Microondas Beep.wav" },
	{AllLevels, IngredientSpawned,"../AnimalCooking/resources/sounds/Aparece Ingrediente 2-Poly.wav" },
	{AllLevels, OrderRecieved,"../AnimalCooking/resources/sounds/Timbre 2.wav" },
	{Basic, PlaneSound,"../AnimalCooking/resources/sounds/planeSound.wav"},

	{Basic, Tecla1,"../AnimalCooking/resources/sounds/tecla1.ogg" },
	{Basic, Tecla2,"../AnimalCooking/resources/sounds/tecla2.ogg" },
	{Basic, Tecla3,"../AnimalCooking/resources/sounds/tecla3.ogg" },
	{Basic, Tecla4,"../AnimalCooking/resources/sounds/tecla4.ogg" },
	{Basic, Tecla5,"../AnimalCooking/resources/sounds/tecla5.ogg" },
	{Basic, Tecla6,"../AnimalCooking/resources/sounds/tecla6.ogg" },

	{AllLevels, End_Win,"../AnimalCooking/resources/sounds/END_WIN.ogg" },
	{AllLevels, End_Lost,"../AnimalCooking/resources/sounds/END_LOST.ogg" }
};

