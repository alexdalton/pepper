//									tab:8
//
// GameScreen.h - header file for UIUC ECE198KL Spring 2013 Program 5
//                game screen
//
// "Copyright (c) 2013 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
// 
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
// DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
// OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta
// Version:	    1.01
// Creation Date:   8 February 2013
// Filename:	    GameScreen.h
// History:
//	SL	1.00	8 February 2013
//		First written.
//	SL	1.01	9 February 2013
//		Added checking and hints.
//

#if !defined(GAME_SCREEN_H)
#define GAME_SCREEN_H

#include "WALY/WALY.h"

using namespace WALY;

class GameScreen : public Frame {

    private:
        enum {
	    IMG_NONE = -1,

	    IMG_MARKER_RED,
	    IMG_MARKER_ORANGE,
	    IMG_MARKER_YELLOW,
	    IMG_MARKER_GREEN,
	    IMG_MARKER_BLUE,
	    IMG_MARKER_PURPLE,
	    IMG_MARKER_WHITE,
	    IMG_MARKER_BLACK,

	    NUM_MARKER_IMGS,

	    IMG_GUESS_BOARD = NUM_MARKER_IMGS,

	    IMG_PERFECT,
	    IMG_MISPLACED,
	    IMG_VALIDATED,
	    IMG_HINT,

	    NUM_IMGS
	};

	enum {
	    SND_PLACEMENT,
	    SND_IGNORED,
	    NUM_SOUNDS
	};

        static int32_t numInstances;
	static Image** image;
	static Font**  font;
	static Sound** sound;
	static void init (void);
	static void cleanUp (void);

	Frame* piece;
	int32_t pieceType;
	int32_t moveNum;
	Frame* boardImg[12][4];
	int32_t board[12][4];
	int32_t numPerf[12];
	int32_t numMisp[12];
	Button* guessButton;
	Frame* reportImg[12][4];
	Frame* guessGoodImg[12];
	Label* winLoseMsg;
	Frame* hintOneImg;
	Frame* hintTwoImg;

	void (*endGameAction) (void);

	void updateGuesses (void);
	void clearHint (void);

	static void makeGuess (Button* b);

	static void getPiece (Frame* f, const Event* e);
	static void movePiece (Frame* f, const Event* e);
	static void placePiece (Frame* f, const Event* e);
	static void keystroke (Frame* f, const Event* e);

    public:
        GameScreen (Frame* par, void (*endGameFunc) (void));
	~GameScreen () {
	    if (0 == --numInstances) { cleanUp (); }
	}
	void reportGuess (int32_t move, int32_t perfect, int32_t misplaced);

	void activate ();
	void deactivate ();
};

#endif /* GAME_SCREEN_H */
