#ifndef    __setup__
#define    __setup__

#include<string>

struct setup {
    int language;                                        // 0: french, 1 : english, 2: spanish, 3: german
    int pieceGraphic;                                    // graphics types : 0 to x
    int gameType;                                        // 0 : marathon  1: sprint  2 limited time  ...
	bool enhanced;                                       // 11 or 7 pieces game
	bool sevenBag;                                       // randow method : 7-bag or random
	bool superRotationSystem;                            // system de ration avancee ON/OFF
	bool shadow;                                         // display shadow piece ON/OFF
	bool hold;                                           // hold piece ON/OFF
	bool lockout;                                        // lockout ON/OFF
	bool nextPiece;                                      // viewing the next piece ON/OFF
	int nextPiecesNumber;                                // number of next pieces viewable 0 up to 5
	bool music;                                          // play music ON/OFF
	int musicVolume;                                     // music volume 0-100
	bool sound;                                          // game sound ON/OFF
	int soundVolume;                                     // game sound 0-100
	std::string pseudo;                                  // player's name
};

#endif
