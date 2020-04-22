#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
	{Basic, ARIAL12, "../AnimalCooking/resources/fonts/ARIAL.ttf", 12 }
};

	
	

vector<Resources::ImageInfo> Resources::images_{
	//
	{Basic, Button,"../AnimalCooking/resources/images/button.jpg"},

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

vector<Resources::TextMsgInfo> Resources::messages_{


};


vector<Resources::MusicInfo> Resources::musics_{
	//

};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{Basic, KnifeAttack,"../AnimalCooking/resources/sounds/Cuchillo 1.wav"},
{Basic,DropDish,"../AnimalCooking/resources/sounds/Dejar Plato 1.wav"}, //
{Basic,CompleteDish,"../AnimalCooking/resources/sounds/Elaborar Plato 1.wav"},//
{Basic,Wash,"../AnimalCooking/resources/sounds/Fregar 1.wav"},
{Basic,FrySound,"../AnimalCooking/resources/sounds/Freir corto.wav"},
{Basic,MaceAttack,"../AnimalCooking/resources/sounds/Golpe Mazo 1.wav"},
{Basic,MicroWave,"../AnimalCooking/resources/sounds/Microondas Beep.wav"},
{Basic,Door,"../AnimalCooking/resources/sounds/Puerta 1.wav"},
{Basic,FrySoundBurned,"../AnimalCooking/resources/sounds/Freir Quemar.wav" },
{Basic,Bin,"../AnimalCooking/resources/sounds/Basura 2.wav" },
{Basic,PickUp,"../AnimalCooking/resources/sounds/Bop nuevo 4.wav" },
{Basic,AttackMiss,"../AnimalCooking/resources/sounds/Golpe fallido 3.wav" },
{Basic,BurnedBeep,"../AnimalCooking/resources/sounds/Microondas Temporizador.wav" },
{Basic,CookedFood,"../AnimalCooking/resources/sounds/Microondas Beep.wav" },
{Basic,Drop,"../AnimalCooking/resources/sounds/Dejar Caer 4.wav" }

};

