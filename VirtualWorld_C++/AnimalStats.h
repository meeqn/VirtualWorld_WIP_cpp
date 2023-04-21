#pragma once
namespace animalStats {
	const int STANDARD_MOVE_DIST = 1;

	namespace humanStats {
		const int STRENGTH = 5;
		const char SYMBOL = 'H';
		const int MOVE_DIST = STANDARD_MOVE_DIST;
	}
	namespace sheepStats {
		const int INITIATIVE = 4;
		const int STRENGTH = 4;
		const char SYMBOL = 's';
		const int MOVE_DIST = STANDARD_MOVE_DIST;
	}
	namespace wolfStats {
		const int INITIATIVE = 5;
		const int STRENGTH = 9;
		const char SYMBOL = 'w';
		const int MOVE_DIST = STANDARD_MOVE_DIST;
	}
	namespace turtleStats {
		const int INITIATIVE = 1;
		const int STRENGTH = 2;
		const char SYMBOL = 't';
		const int MOVE_DIST = STANDARD_MOVE_DIST;
	}
	namespace antelopeStats {
		const int INITIATIVE = 4;
		const int STRENGTH = 4;
		const char SYMBOL = 'a';
		const int MOVE_DIST = 2;
	}
	namespace foxStats {
		const int INITIATIVE = 7;
		const int STRENGTH = 3;
		const char SYMBOL = 'f';
		const int MOVE_DIST = STANDARD_MOVE_DIST;
	}
}