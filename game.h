#include "stdafx.h"
#pragma once

class game { //класс самой игры
	bool getstarted;
public: game();
		int run();
		bool returnGetStarted() { return getstarted; }
};