#include "SemanticActions/SemanticActions.h"
#include "SemanticDataStructures/SemanticDataStructures.h"

class Semantics
{
	private:
		SemanticDataStructures* semanticDataStructures;
	public:
		SemanticActions* semanticActions;
		virtual void constructor() = 0;
};
