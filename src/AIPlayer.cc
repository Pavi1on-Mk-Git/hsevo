#include "AIPlayer.h"

AIPlayer::AIPlayer(DeckList decklist, std::ranlux24_base& random_engine): deck(decklist, random_engine), hand() {}
