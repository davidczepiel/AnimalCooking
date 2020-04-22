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

	{Basic, IngredienteMalo,"../AnimalCooking/resources/images/caca.png"},
	{Basic, Cooker,"../AnimalCooking/resources/images/sarten.png"},
	{Basic, CookerCooking,"../AnimalCooking/resources/images/sartencocinando.png"},
	{Basic, CookerCooked,"../AnimalCooking/resources/images/sartencooked.png"},
	{Basic, CookerBurned,"../AnimalCooking/resources/images/sartenburned.png"},
	{Basic, Platera,"../AnimalCooking/resources/images/platera.png"},
	{Basic, ComidaCocinada,"../AnimalCooking/resources/images/comidaCocinada.jpg"},
	{Basic, Tomato,"../AnimalCooking/resources/images/tomateCortado.png"},
	{Basic, Onion,"../AnimalCooking/resources/images/onion.png"},
	{Basic, Cuchillo,"../AnimalCooking/resources/images/cuchillo.png"},
	{Basic, CuchilloSucio,"../AnimalCooking/resources/images/cuchilloSucio.jpg"},
	{Basic, Fregadero,"../AnimalCooking/resources/images/fregadero.jpg"},
	{Basic, Hierba,"../AnimalCooking/resources/images/hierba.jpg"},
	{Basic, Ingrediente,"../AnimalCooking/resources/images/ingrediente.png"},
	{Basic, Panera,"../AnimalCooking/resources/images/panera.png"},
	{Basic, Papelera,"../AnimalCooking/resources/images/papelera.png"},
	{Basic, Pedido,"../AnimalCooking/resources/images/pedido.png"},
	{Basic, Cerdo,"../AnimalCooking/resources/images/personaje.png"},
	{Basic, Pollo,"../AnimalCooking/resources/images/personaje2.png"},
	{Basic, Plato,"../AnimalCooking/resources/images/plato.png"},
	{Basic, Repisa,"../AnimalCooking/resources/images/repisa.png"},
	{Basic, Suelo,"../AnimalCooking/resources/images/suelo.png"},
	{Basic, CuadradoAux,"../AnimalCooking/resources/images/cuadrado.png"},
	{Basic,level0Menu,"../AnimalCooking/resources/images/level0Menu.png"},
	{Basic,level1Menu,"../AnimalCooking/resources/images/level1Menu.png"},
	{Basic,level2Menu,"../AnimalCooking/resources/images/level2Menu.png"},
	{Basic,level3Menu,"../AnimalCooking/resources/images/level3Menu.png"},
	{Basic,level4Menu,"../AnimalCooking/resources/images/level4Menu.png"},

	{Basic, Pan,"../AnimalCooking/resources/images/pan.png"},
	{Basic, Aceite,"../AnimalCooking/resources/images/aceite.png"},
	{Basic, Arroz,"../AnimalCooking/resources/images/arroz.png"},

	//FeedBack
	{Basic, TomatoFeedBack,"../AnimalCooking/resources/images/feedbackTomate.png"},
	{Basic, OnionFeedBack,"../AnimalCooking/resources/images/onionFeedBack.png"},
	{Basic, CuchilloFeedBack,"../AnimalCooking/resources/images/cuchilloFeedBack.png"},
	{Basic, PapelertaFeedBack,"../AnimalCooking/resources/images/papeleraFeedBack.png"},
	{Basic, PlatoFeedBack,"../AnimalCooking/resources/images/platoFeedBack.png"},
	{Basic, Panel,"../AnimalCooking/resources/images/panel.png"},
	{Basic, Coger,"../AnimalCooking/resources/images/coger.png"},
	{Basic, Dejar,"../AnimalCooking/resources/images/dejar.png"}
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

