#include "CreditsViewer.h"

void CreditsViewer::init()
{
	double casilla = SDLGame::instance()->getCasillaLength();
	Texture* AntonioJesus = SDLGame::instance()->getTextureMngr()->getTexture(Resources::AntonioJesus);
	names[0] = {
		AntonioJesus,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - AntonioJesus->getWidth() / 2 ,
			SDLGame::instance()->getWindowHeight()) };

	Texture* Daniel = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Daniel);

	names[1] = {
		Daniel,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Daniel->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + casilla) };

	Texture* David = SDLGame::instance()->getTextureMngr()->getTexture(Resources::David);
	names[2] = {
		David,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - David->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 2 * casilla) };
	Texture* Felipe = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Felipe);
	names[3] = {
		Felipe,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Felipe->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 3 * casilla) };
	Texture* Javier = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Javier);
	names[4] = {
		Javier,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Javier->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 4 * casilla) };
	Texture* Marco = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Marco);
	names[5] = {
		Marco,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Marco->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 5 * casilla) };
	Texture* Nico = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Nicolas);
	names[6] = {
		Nico,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Nico->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 6 * casilla) };
	Texture* Pablo = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pablo);
	names[7] = {
		Pablo,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Pablo->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 7 * casilla) };
	Texture* Sandra = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Sandra);
	names[8] = {
		Sandra,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Sandra->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 8 * casilla) };
	Texture* Tatiana = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Tatiana);
	names[9] = {
		Tatiana,
		Vector2D(SDLGame::instance()->getWindowWidth() / 2 - Tatiana->getWidth() / 2,
			SDLGame::instance()->getWindowHeight() + 9 * casilla) };
	tenByTenLogo = SDLGame::instance()->getTextureMngr()->getTexture(Resources::LogoTenByTen);
	logoPos = Vector2D(SDLGame::instance()->getWindowWidth() / 2 - tenByTenLogo->getWidth() / 2,
		SDLGame::instance()->getWindowHeight());
	ratio = tenByTenLogo->getWidth() / tenByTenLogo->getHeight();
}

void CreditsViewer::update()
{
	if (names[9].pos.getY() > -names[9].name->getHeight()) {

		for (int i = 0; i < names.size(); i++)
		{
			names[i].pos.setY(names[i].pos.getY() - config::PIXELS_TO_MOVE);
		}
	}
	if (names[5].pos.getY() <= 0 &&
		logoPos.getY() > SDLGame::instance()->getWindowHeight() / 2 - tenByTenLogo->getHeight() / 2) {
		logoPos.setY(logoPos.getY() - config::PIXELS_TO_MOVE);

	}
}

void CreditsViewer::draw()
{
	for (VisualNames N : names) {
		N.name->render(RECT(N.pos.getX(), N.pos.getY(), N.name->getWidth(), N.name->getHeight()));
	}
	tenByTenLogo->render(RECT(logoPos.getX(), logoPos.getY(), tenByTenLogo->getWidth(),tenByTenLogo->getHeight()));
}
