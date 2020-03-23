#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
	{Basic, ARIAL24, "../AnimalCooking/resources/fonts/ARIAL.ttf", 24 }
};

	
	

vector<Resources::ImageInfo> Resources::images_{
	//
	{Basic, Button,"../AnimalCooking/resources/images/button.jpg"},

	{Basic, IngredienteMalo,"../AnimalCooking/resources/images/caca.png"},
	{Basic, Cooker,"../AnimalCooking/resources/images/cocinador.png"},
	{Basic, ComidaCocinada,"../AnimalCooking/resources/images/comidaCocinada.jpg"},
	{Basic, ComidaMuerta,"../AnimalCooking/resources/images/comidaMuerta.jpg"},
	{Basic, Cuchillo,"../AnimalCooking/resources/images/cuchillo.png"},
	{Basic, CuchilloSucio,"../AnimalCooking/resources/images/cuchilloSucio.jpg"},
	{Basic, Fregadero,"../AnimalCooking/resources/images/fregadero.jpg"},
	{Basic, Hierba,"../AnimalCooking/resources/images/hierba.jpg"},
	{Basic, Ingrediente,"../AnimalCooking/resources/images/ingrediente.jpg"},
	{Basic, Papelera,"../AnimalCooking/resources/images/papelera.png"},
	{Basic, Pedido,"../AnimalCooking/resources/images/pedido.png"},
	{Basic, Cerdo,"../AnimalCooking/resources/images/personaje.png"},
	{Basic, Pollo,"../AnimalCooking/resources/images/personaje2.png"},
	{Basic, Plato,"../AnimalCooking/resources/images/plato.png"},
	{Basic, Repisa,"../AnimalCooking/resources/images/repisa.jpg"},
	{Basic, Suelo,"../AnimalCooking/resources/images/suelo.png"},

	{Basic, Pan,"../AnimalCooking/resources/images/pan.png"},
	{Basic, Aceite,"../AnimalCooking/resources/images/aceite.png"},
	{Basic, Arroz,"../AnimalCooking/resources/images/arroz.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//

};

vector<Resources::MusicInfo> Resources::musics_{
	//

};

vector<Resources::SoundInfo> Resources::sounds_{
	//

};

