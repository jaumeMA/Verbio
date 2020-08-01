#pragma once

#include "IInputHandler.h"
#include <thread>

namespace vtf
{

class KeyboardInputHandler : public IInputHandler
{
public:
	KeyboardInputHandler() = default;

private:
	void start() override;
	void stop() override;

	void update();

	std::thread m_updateThread;
	bool m_stop = false;
};

}