#include "KeyboardInputHandler.h"
#include <iostream>
#include <sstream>

namespace vtf
{

void KeyboardInputHandler::start()
{
	m_stop = false;

	update();
}
void KeyboardInputHandler::stop()
{
	m_stop = true;
}
void KeyboardInputHandler::update()
{
	std::string newSentence;

	while (m_stop == false)
	{
		std::cout << "Write a sentence:" << std::endl;

		std::getline(std::cin,newSentence);

		if (newSentence == "quit")
		{
			break;
		}
		else
		{
			call_onNewStream(std::stringstream(newSentence));
		}
	}
}

}