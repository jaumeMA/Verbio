
#include "TextFormatter.h"
#include "KeyboardInputHandler.h"
#include <iostream>

void dumpFormattedTextIntoScreen(const std::string& i_formattedText)
{
	std::cout << "Formatted text: " << i_formattedText << std::endl;
}

int main(int argc, char* argv[])
{
	vtf::TextFormatter txtFormatter;
	vtf::KeyboardInputHandler keyboardInputHandler;

	txtFormatter.call_onNewTextFormatted = dumpFormattedTextIntoScreen;

	std::cout << "Introduce the text you want to format and press intro. Type quit for shuting down" << std::endl;

	txtFormatter.init(keyboardInputHandler);

	return 0;
}
