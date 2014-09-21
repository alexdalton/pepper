//									tab:8
//
// SeedScreen.cpp - source file for UIUC ECE198KL Spring 2013 Program 5
//                  random seed entry screen
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
// Filename:	    SeedScreen.cpp
// History:
//	SL	1.00	8 February 2013
//		First written.
//	SL	1.01	9 February 2013
//		Tweaked keyboard display issues for Android.
//

#include "WALY/WALY.h"

#include <math.h>

#include "SeedScreen.h"
#include "prog5.h"

using namespace WALY;

int32_t SeedScreen::numInstances = 0;
Font**  SeedScreen::font         = NULL;

void
SeedScreen::init ()
{
    font = new Font*[2];
    font[0] = new Font (WALY_FONT_SANS_REGULAR, 40);
}

void
SeedScreen::cleanUp ()
{
    for (int32_t i = 0; 1 > i; i++) {
	delete font[i];
    }
    delete[] font;
    font = NULL;
}

void
SeedScreen::enterSeed (EntryBox* eb)
{
    SeedScreen* ss = (SeedScreen*)eb->getParent ();

    if (set_seed (eb->getText ())) {
        ss->status->setText ("");
	ss->haveSeedAction ();
    }
}

SeedScreen::SeedScreen (Frame* par, void (*haveSeedFunc) (void)) : 
	Frame (par), haveSeedAction (haveSeedFunc)
{
    Rect r;

    if (0 == numInstances++) { init (); }

    useSolidBackground (0x107010);
    r.x = r.y = 0;
    r.w = 500;
    r.h = 800;
    setScrollRect (r);

    Label* lbl = new Label (this, 250, 40, "Enter random seed", 
    			    0xFFFF00, font[0]);
    lbl->setAlign (ALIGN_N);

    display = new EntryBox (this, 250, 100, 225, "", 0x00FF00, 
    			    0x000000, 0x308030, font[0]);
    display->setAlign (ALIGN_N);
    display->setActionFunc (enterSeed);
    display->setMaxChars (10);

    status = new Label (this, 250, 180, "", 0xFFFF00, font[0]);
    status->setAlign (ALIGN_N);

    setCallbackFunc (KEY_DOWN, keystroke);

    deactivate ();
}
	
void 
SeedScreen::keystroke (Frame* f, const Event* e)
{
    if (PDLK_GESTURE_BACK == (int32_t)e->key.keysym.sym) {
        Platform::minimize ();
    } else if ('\r' != e->key.keysym.sym) {
        ((SeedScreen*)f)->status->setText ("");
    }
}

void
SeedScreen::activate ()
{
    setActive (true);
    setVisible (true);
// Android keyboard gunk is being finicky...this variant at least
// works...should probably add a default seed and a 'play' button, though.
//    display->setFocus (true);
}

void
SeedScreen::deactivate ()
{
    display->setFocus (false);
    setVisible (false);
    setActive (false);
}

