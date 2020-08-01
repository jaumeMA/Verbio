#include "TextFormatter.h"
#include <iostream>
#include "StreamTokenizer.h"
#include "TokenScanner.h"
#include "FreeTextRuleAcceptor.h"
#include "FreeTextRuleTransformer.h"
#include "TextToNumberRuleAcceptor.h"
#include "TextToNumberRuleTransformer.h"
#include <memory>

namespace vtf
{

TextFormatter::TextFormatter()
{

}
void TextFormatter::init(IInputHandler& i_inputHandler)
{
	i_inputHandler.call_onNewStream = std::bind(&TextFormatter::onNewStream,this,std::placeholders::_1);

	i_inputHandler.start();
}
void TextFormatter::onNewStream(std::istream& i_stream)
{
	StreamTokenizer streamTokenizer;
	TokenScanner tokenScanner(streamTokenizer);
	ScannerRule FreeTextRule(std::make_unique<TextToNumberRuleAcceptor>(),std::make_unique<TextToNumberRuleTransformer>());

	tokenScanner.register_rule(std::move(FreeTextRule));

	streamTokenizer.processStream(i_stream);

	const std::string resolvedStream = tokenScanner.acquire_resolved_tokens();

	call_onNewTextFormatted(resolvedStream);
}
void TextFormatter::onQuit()
{

}

}