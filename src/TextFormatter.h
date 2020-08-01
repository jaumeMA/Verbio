#pragma once

#include <istream>
#include "IInputHandler.h"
#include "ITextFormatter.h"

namespace vtf
{

class TextFormatter : public ITextFormatter
{
public:
	TextFormatter();

	void init(IInputHandler& i_inputHandler);

private:
	void onNewStream(std::istream& i_stream);
	void onQuit();
};

}