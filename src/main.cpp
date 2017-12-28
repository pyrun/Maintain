#include "engine/engine.h"

int main() {
    engine *l_engine = new engine();

    // run
	int l_return = l_engine->run();

	// delte engine
	delete l_engine;

	return l_return;
}
