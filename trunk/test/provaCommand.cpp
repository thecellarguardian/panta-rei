#include "../src/Controller/PantaReiLanguage/PantaReiLanguage.h"
#include "../lib/CommandInterpreter/CommandInterpreter.h"
#include <iostream>

int main()
{
	CommandInterpreter<PantaReiLanguage> c("Welcome", &std::cin);
	c.run();
}
