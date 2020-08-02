
#include "TextFormatter.h"
#include "KeyboardInputHandler.h"
#include <iostream>

void dumpFormattedTextIntoScreen(const std::string& i_formattedText)
{
	std::cout << "Formatted text: " << i_formattedText << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		unsigned int maxMultiplier = atoi(argv[1]);

		vtf::TextFormatter txtFormatter(maxMultiplier);
		vtf::KeyboardInputHandler keyboardInputHandler;

		txtFormatter.call_onNewTextFormatted = dumpFormattedTextIntoScreen;

		std::cout << "Introduce the text you want to format and press intro. Type quit for shuting down" << std::endl;

		txtFormatter.init(keyboardInputHandler);
	}
	else
	{
		std::cout << "You shall pass as input argument maximum multipler (i.e. 3 for up to 1000 number value, 6 for up to 1000000 number value and so on)" << std::endl;
	}


	return 0;
}
