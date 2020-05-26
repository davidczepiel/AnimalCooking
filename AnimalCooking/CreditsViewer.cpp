#include "CreditsViewer.h"

void CreditsViewer::init()
{
	initializeNames();
	tenByTenLogo = game_->getTextureMngr()->getTexture(Resources::LogoTenByTen);
	logoPos = Vector2D(game_->getWindowWidth() / 2 - tenByTenLogo->getWidth() / 2,
		game_->getWindowHeight());
}

void CreditsViewer::update()
{
	if (names[9].pos.getY() > -names[9].name->getHeight()) {

		for (int i = 0; i < names.size(); i++)
		{
			names[i].pos.setY(names[i].pos.getY() - config::PIXELS_TO_MOVE);
		}
	}
	if (names[2].pos.getY() <= 0 &&
		logoPos.getY() > game_->getWindowHeight() / 2 - tenByTenLogo->getHeight() / 2) {
		logoPos.setY(logoPos.getY() - config::PIXELS_TO_MOVE);

	}
}

void CreditsViewer::draw()
{
	for (VisualNames N : names) {
		N.name->render(RECT(N.pos.getX(), N.pos.getY(), N.name->getWidth(), N.name->getHeight()));
	}
	tenByTenLogo->render(RECT(logoPos.getX(), logoPos.getY(), tenByTenLogo->getWidth(), tenByTenLogo->getHeight()));
}

void CreditsViewer::initializeNames()
{
	double casillaY = game_->getCasillaY();
	Texture* AntonioJesus = game_->getTextureMngr()->getTexture(Resources::AntonioJesus);
	names[0] = {
		AntonioJesus,
		Vector2D(game_->getWindowWidth() / 2 - AntonioJesus->getWidth() / 2 ,
			game_->getWindowHeight()) };

	Texture* Daniel = game_->getTextureMngr()->getTexture(Resources::Daniel);

	names[1] = {
		Daniel,
		Vector2D(game_->getWindowWidth() / 2 - Daniel->getWidth() / 2,
			game_->getWindowHeight() + casillaY) };

	Texture* David = game_->getTextureMngr()->getTexture(Resources::David);
	names[2] = {
		David,
		Vector2D(game_->getWindowWidth() / 2 - David->getWidth() / 2,
			game_->getWindowHeight() + 2 * casillaY) };
	Texture* Felipe = game_->getTextureMngr()->getTexture(Resources::Felipe);
	names[3] = {
		Felipe,
		Vector2D(game_->getWindowWidth() / 2 - Felipe->getWidth() / 2,
			game_->getWindowHeight() + 3 * casillaY) };
	Texture* Javier = game_->getTextureMngr()->getTexture(Resources::Javier);
	names[4] = {
		Javier,
		Vector2D(game_->getWindowWidth() / 2 - Javier->getWidth() / 2,
			game_->getWindowHeight() + 4 * casillaY) };
	Texture* Marco = game_->getTextureMngr()->getTexture(Resources::Marco);
	names[5] = {
		Marco,
		Vector2D(game_->getWindowWidth() / 2 - Marco->getWidth() / 2,
			game_->getWindowHeight() + 5 * casillaY) };
	Texture* Nico = game_->getTextureMngr()->getTexture(Resources::Nicolas);
	names[6] = {
		Nico,
		Vector2D(game_->getWindowWidth() / 2 - Nico->getWidth() / 2,
			game_->getWindowHeight() + 6 * casillaY) };
	Texture* Pablo = game_->getTextureMngr()->getTexture(Resources::Pablo);
	names[7] = {
		Pablo,
		Vector2D(game_->getWindowWidth() / 2 - Pablo->getWidth() / 2,
			game_->getWindowHeight() + 7 * casillaY) };
	Texture* Sandra = game_->getTextureMngr()->getTexture(Resources::Sandra);
	names[8] = {
		Sandra,
		Vector2D(game_->getWindowWidth() / 2 - Sandra->getWidth() / 2,
			game_->getWindowHeight() + 8 * casillaY) };
	Texture* Tatiana = game_->getTextureMngr()->getTexture(Resources::Tatiana);
	names[9] = {
		Tatiana,
		Vector2D(game_->getWindowWidth() / 2 - Tatiana->getWidth() / 2,
			game_->getWindowHeight() + 9 * casillaY) };

}
