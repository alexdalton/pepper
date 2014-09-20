//									tab:8
//
// GameScreen.cpp - source file for UIUC ECE198KL Spring 2013 Program 5
//                  game screen
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
// Filename:	    GameScreen.cpp
// History:
//	SL	1.00	8 February 2013
//		First written.
//	SL	1.01	9 February 2013
//		Added checking and hints.
//

#include "WALY/WALY.h"

#include <math.h>

#include "GameScreen.h"
#include "prog5.h"

using namespace WALY;

int32_t GameScreen::numInstances = 0;
Image** GameScreen::image        = NULL;
Font**  GameScreen::font         = NULL;
Sound** GameScreen::sound        = NULL;

void
GameScreen::init ()
{
    static const char* const names[NUM_IMGS] = {
        "markerRed.png",
        "markerOrange.png",
        "markerYellow.png",
        "markerGreen.png",
        "markerBlue.png",
        "markerPurple.png",
        "markerWhite.png",
        "markerBlack.png",
	"guessBoard.png",
	"perfect.png",
	"misplaced.png",
	"validated.png",
	"hint.png",
    };

    image = new Image*[NUM_IMGS];
    for (int32_t i = 0; NUM_IMGS > i; i++) {
        image[i] = new Image (names[i]);
    }
    font = new Font*[2];
    font[0] = new Font (WALY_FONT_SANS_BOLD, 24);
    font[1] = new Font (WALY_FONT_SANS_BOLD, 60);

    static const char* const soundFile[NUM_SOUNDS] = {
        "placement.wav",
	"ignored.wav"
    };
    sound = new Sound*[NUM_SOUNDS];
    for (int32_t i = 0; NUM_SOUNDS > i; i++) {
        sound[i] = new Sound (soundFile[i]);
    }
}

void
GameScreen::cleanUp ()
{
    for (int32_t i = 0; NUM_IMGS > i; i++) {
	delete image[i];
    }
    delete[] image;
    image = NULL;
    for (int32_t i = 0; 2 > i; i++) {
	delete font[i];
    }
    delete[] font;
    font = NULL;
    for (int32_t i = 0; NUM_SOUNDS > i; i++) {
	delete sound[i];
    }
    delete[] sound;
    sound = NULL;
}

void
GameScreen::makeGuess (Button* b)
{
    GameScreen* gs = (GameScreen*)b->getParent ();
    char buf[200];
    int32_t trash[4];
    int32_t hint[4];
    int32_t pos;

    sprintf (buf, "%d %d %d %d", gs->board[gs->moveNum][0] + 1,
	     gs->board[gs->moveNum][1] + 1, gs->board[gs->moveNum][2] + 1,
	     gs->board[gs->moveNum][3] + 1);
    gs->clearHint ();
    if (make_guess (buf, &trash[0], &trash[1], &trash[2], &trash[3])) {
	if (12 > ++gs->moveNum) {
	    gs->guessButton->setY (65 * gs->moveNum + 42);
	}
    } else {
	gs->sound[SND_IGNORED]->play ();
	if (get_hint (hint)) {
	    for (pos = 0; 4 > pos; pos++) {
	        if (gs->board[gs->moveNum][pos] != hint[pos] - 1) {
		    gs->hintOneImg->setVisible (true);
		    gs->hintOneImg->setX (25);
		    gs->hintOneImg->setY (65 * (hint[pos] - 1) + 172);
		    gs->hintTwoImg->setVisible (true);
		    gs->hintTwoImg->setX (50 * pos + 90);
		    gs->hintTwoImg->setY (65 * gs->moveNum + 42);
		    break;
		}
	    }
	}
    }
    gs->updateGuesses ();
}

void
GameScreen::clearHint ()
{
    hintOneImg->setVisible (false);
    hintTwoImg->setVisible (false);
}

void
GameScreen::updateGuesses ()
{
    int32_t which;

    which = 0;
    if (12 > moveNum) {
	for (which = 0; moveNum > which; which++) {
	    guessGoodImg[which]->setVisible 
		    (0 != compare_guesses 
			    (board[which][0] + 1, board[which][1] + 1,
			     board[which][2] + 1, board[which][3] + 1,
			     numPerf[which], numMisp[which],
			     board[moveNum][0] + 1, board[moveNum][1] + 1,
			     board[moveNum][2] + 1, board[moveNum][3] + 1));
	}
    }
    for (; 12 > which; which++) {
    	guessGoodImg[which]->setVisible (false);
    }
}

GameScreen::GameScreen (Frame* par, void (*endGameFunc) (void)) :
	Frame (par), endGameAction (endGameFunc)
{
    Rect r;

    if (0 == numInstances++) { init (); }

    useSolidBackground (0x101070);
    r.x = r.y = 0;
    r.w = 500;
    r.h = 800;
    setScrollRect (r);

    Frame* sidebar = new Frame (this, 0, 0);
    r.w = 50;
    sidebar->useSolidBackground (0x404040);
    sidebar->setScrollRect (r);

    for (int32_t color = 0; NUM_MARKER_IMGS > color; color++) {
	Frame* f = new Frame (sidebar, 25, 65 * color + 172);
	f->setAlign (ALIGN_C);
	f->attachImage (image[color]);
    }

    for (int32_t i = 0; 12 > i; i++) {
        Frame* f = new Frame (this, 65, 65 * i + 42);
	f->setAlign (ALIGN_W);
	f->attachImage (image[IMG_GUESS_BOARD]);
	for (int32_t j = 0; 4 > j; j++) {
	    boardImg[i][j] = new Frame (this, 50 * j + 90, 65 * i + 42);
	    boardImg[i][j]->setAlign (ALIGN_C);
	    reportImg[i][j] = new Frame (this, 28 * j + 285, 65 * i + 42);
	    reportImg[i][j]->setAlign (ALIGN_C);
	}
	guessGoodImg[i] = new Frame (this, 400, 65 * i + 42);
	guessGoodImg[i]->setAlign (ALIGN_W);
	guessGoodImg[i]->attachImage (image[IMG_VALIDATED]);
    }

    guessButton = new Button (this, 485, 0, "Guess", 0x000000, 
    			      0x3030F0, font[0]);
    guessButton->setAlign (ALIGN_E);
    guessButton->setActionFunc (makeGuess);

    hintOneImg = new Frame (this, 0, 0);
    hintOneImg->setAlign (ALIGN_C);
    hintOneImg->setVisible (false);
    hintOneImg->attachImage (image[IMG_HINT]);
    hintTwoImg = new Frame (this, 0, 0);
    hintTwoImg->setAlign (ALIGN_C);
    hintTwoImg->setVisible (false);
    hintTwoImg->attachImage (image[IMG_HINT]);

    piece = new Frame (this, -100, 0);
    piece->setAlign (ALIGN_C);

    winLoseMsg = new Label (this, 250, 400, "", 0xFFFF00, 0x000000, font[1]);
    winLoseMsg->setAlign (ALIGN_C);
    winLoseMsg->setVisible (false);

    setCallbackFunc (KEY_DOWN, keystroke);

    deactivate ();
}
	
void 
GameScreen::getPiece (Frame* f, const Event* e)
{
    GameScreen* gs = (GameScreen*)f;

    if (0 == e->button.which) {
	if (50 > e->button.x) {
	    int32_t type = (e->button.y + 55) / 65 - 3;

	    if (0 <= type && NUM_MARKER_IMGS > type) {
		gs->piece->attachImage (image[type]);
		gs->piece->setX (e->button.x);
		gs->piece->setY (e->button.y);
		gs->pieceType = type;
	    }
	} else {
	    int32_t x = (e->button.x + 35) / 50 - 2;
	    int32_t y = (e->button.y + 48) / 65 - 1;
	    if (gs->moveNum == y && 0 <= x && 4 > x && -1 != gs->board[y][x]) {
		gs->piece->attachImage (image[gs->board[y][x]]);
		gs->piece->setX (e->button.x);
		gs->piece->setY (e->button.y);
		gs->pieceType = gs->board[y][x];
		gs->board[y][x] = -1;
		gs->boardImg[y][x]->detachImage ();
		gs->updateGuesses ();
	    }
	}
    }
}

void 
GameScreen::movePiece (Frame* f, const Event* e)
{
    GameScreen* gs = (GameScreen*)f;

    if (0 == e->button.which && IMG_NONE != gs->pieceType) {
	gs->piece->setX (e->motion.x);
	gs->piece->setY (e->motion.y);
    }
}

void 
GameScreen::placePiece (Frame* f, const Event* e)
{
    GameScreen* gs = (GameScreen*)f;
    
    if (0 == e->button.which && IMG_NONE != gs->pieceType) {
    	int32_t x = (e->button.x + 35) / 50 - 2;
	int32_t y = (e->button.y + 48) / 65 - 1;
	if (gs->moveNum == y && 0 <= x && 4 > x) {
	    gs->boardImg[y][x]->attachImage (image[gs->pieceType]);
	    gs->board[y][x] = gs->pieceType;
	    gs->sound[SND_PLACEMENT]->play ();
	    gs->updateGuesses ();
	}
	gs->piece->detachImage ();
	gs->pieceType = IMG_NONE;
    }
}

void 
GameScreen::keystroke (Frame* f, const Event* e)
{
    GameScreen* gs = (GameScreen*)f;

    if (PDLK_GESTURE_BACK == (int32_t)e->key.keysym.sym) {
        gs->endGameAction ();
    }
}

void
GameScreen::reportGuess (int32_t move, int32_t perfect, int32_t misplaced)
{
    numPerf[move] = perfect;
    numMisp[move] = misplaced;
    for (int32_t i = 0; perfect > i; i++) {
	reportImg[move][i]->attachImage (image[IMG_PERFECT]);
    }
    for (int32_t i = 0; misplaced > i; i++) {
	reportImg[move][3 - i]->attachImage (image[IMG_MISPLACED]);
    }
    if (4 == perfect || 11 == move) {
	if (4 == perfect) {
	    winLoseMsg->setText ("You win!");
	} else {
	    winLoseMsg->setText ("You lose!");
	}
	winLoseMsg->setVisible (true);
	setCallbackFunc (MOUSE_DOWN, NULL);
	setCallbackFunc (MOUSE_MOTION, NULL);
	setCallbackFunc (MOUSE_UP, NULL);
	guessButton->setVisible (false);
	guessButton->setEnabled (false);
	moveNum = 12;
    }
}

void
GameScreen::activate ()
{
    piece->detachImage ();
    pieceType = IMG_NONE;
    moveNum = 0;
    for (int32_t i = 0; 12 > i; i++) {
	for (int32_t j = 0; 4 > j; j++) {
	    boardImg[i][j]->detachImage ();
	    board[i][j] = -1;
	    reportImg[i][j]->detachImage ();
	}
    }
    guessButton->setY (42);
    guessButton->setVisible (true);
    guessButton->setEnabled (true);
    winLoseMsg->setVisible (false);
    updateGuesses ();
    clearHint ();

    setCallbackFunc (MOUSE_DOWN, getPiece);
    setCallbackFunc (MOUSE_MOTION, movePiece);
    setCallbackFunc (MOUSE_UP, placePiece);

    setActive (true);
    setVisible (true);
}

void
GameScreen::deactivate ()
{
    setVisible (false);
    setActive (false);
}

