#pragma once

#include <SDL.h>
#include "Resources.h"
#include "TexturesManager.h"
#include "AudioManager.h"
#include "FontsManager.h"
#include "RandomNumberGenerator.h"

#include <string>
#include <memory>
#include <assert.h>

#include "InputHandler.h"
#include "jute.h"
#include "GameConfig.h"

using namespace std;
class FSM;
class Entity;

class SDLGame {
public:
	virtual ~SDLGame();

	SDLGame(SDLGame&) = delete;
	SDLGame& operator=(SDLGame&) = delete;

	inline static SDLGame* init(string windowTitle, int width, int height) {
		assert(instance_.get() == nullptr);
		instance_.reset(new SDLGame(windowTitle, width, height));
		return instance_.get();
	}

	inline static SDLGame* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	inline SDL_Window* getWindow() const {
		return window_;
	}

	inline SDL_Renderer* getRenderer() const {
		return renderer_;
	}

	inline int getWindowWidth() const {
		return width_;
	}

	inline int getWindowHeight() const {
		return height_;
	}

	inline FontsManager* getFontMngr() const {
		return fonts_;
	}

	inline TexturesManager* getTextureMngr() const {
		return textures_;
	}

	inline AudioManager* getAudioMngr() const {
		return audio_;
	}

	inline RandomNumberGenerator* getRandGen() const {
		return random_;
	}

	inline InputHandler* getInputHandler() const {
		return InputHandler::instance();
	}

	inline int getCurrentLevel()const {
		return currentLevel;
	}

	inline int getCurrenUnlockLevel() const {
		return unlockedLevels;
	}

	inline void setCurrentUnlockLevel(int a) {
		unlockedLevels = a;
	}

	inline void addCurrentUnlockLevel() {
		unlockedLevels++;
	}

	inline int getMaxLevels() {
		return maxLevels;
	}

	inline void setMaxLevels(int a) {
		maxLevels = a;
	}

	inline void toggleFullScreen() {
		int flags = SDL_GetWindowFlags(window_);
		if (flags & SDL_WINDOW_FULLSCREEN) {
			SDL_SetWindowSize(window_, width_, height_ - 60);
			SDL_SetWindowFullscreen(window_, 0);
			SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);	
			imFullscreen = false;
		}
		else {
			SDL_SetWindowSize(window_, width_, height_);
			SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
			imFullscreen = true;
		}
	}

	inline FSM* getFSM() { return fsm_; }

	inline Uint32 getTime() {
		return SDL_GetTicks();
	}
	inline int getScore() { return score; }

	inline int getMaxScore() { return maxScore; }
	inline jute::jValue& getJsonGeneral() { return json_general; }

	void setTimersViewer(Entity* timersViewer) { timersViewer_ = timersViewer; }
	inline Entity* getTimersViewer() { return timersViewer_; }

	inline void setCasillaY(const double& CasillaLength) { casillaY = CasillaLength; }
	inline const double& getCasillaY() const { return casillaY; }

	inline void setCasillaX(const double& CasillaLength) { casillaX = CasillaLength; }
	inline const double& getCasillaX() const { return casillaX; }


	void setCurrentLevel(int level) { currentLevel = level; }
	void setScore(int nScore) { if(nScore>=0)score = nScore; }
	void setMaxScore(int nMaxScore) { if (nMaxScore >= 0)maxScore = nMaxScore; }

	void changeWindowSize(int w, int h) {
		SDL_SetWindowSize(window_, w, h);
	}

	config::Options& getOptions() { return options_; }

	void renderFeedBack(const Vector2D& pos, const string& msg, const string& key);
	inline const bool& getIfFullscreen() const { return imFullscreen; }

private:
	SDLGame(string windowTitle_, int width, int height);

	void initSDL(); // initialize SDL
	void closeSDL(); // close SDL
	void initResources(); // initialize the SDLResources object with the data at the top of this file
	void closeResources(); // close the SDLResources object (frees all memory)

protected:

	FontsManager *fonts_;
	TexturesManager *textures_;
	AudioManager *audio_;
	RandomNumberGenerator *random_;
	FSM* fsm_;
	jute::jValue json_general;
	SDL_Window *window_; // the window
	SDL_Renderer *renderer_;  // the renderer

	string windowTitle_; // window title
	int width_; // window width
	int height_; // window height
	int currentLevel;
	int unlockedLevels;
	int maxLevels;
	int score;
	int maxScore;
	double casillaX;
	double casillaY;
	Entity* timersViewer_;

	config::Options options_;
	bool imFullscreen;
	static unique_ptr<SDLGame> instance_;

};

