#include "PantaReiLanguage.h"
#include "../../../lib/CommandInterpreter/CommandInterpreter.h"

int main()
{
	CommandInterpreter<PantaReiLanguage> c("Welcome");
	c.prompt();
}
