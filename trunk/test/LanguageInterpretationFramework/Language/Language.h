#include "Syntax/Syntax.h"
#include "Semantics/Semantics.h"

class Language
{
	private:
		Semantics* semantics;
	public:
		Syntax* syntax;
		virtual void constructor() = 0;
};
