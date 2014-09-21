//									tab:8
//
// SeedScreen.h - header file for UIUC ECE198KL Spring 2013 Program 5
//                random seed entry screen
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
// Version:	    1.00
// Creation Date:   8 February 2013
// Filename:	    SeedScreen.h
// History:
//	SL	1.00	8 February 2013
//		First written.
//

#if !defined(SEED_SCREEN_H)
#define SEED_SCREEN_H

#include "WALY/WALY.h"

using namespace WALY;

class SeedScreen : public Frame {

    private:
        static int32_t numInstances;
	static Font** font;
	static void init ();
	static void cleanUp ();

	EntryBox* display;
	Label* status;
	void (*haveSeedAction) (void);

	static void enterSeed (EntryBox* eb);

	static void keystroke (Frame* f, const Event* e);

    public:
        SeedScreen (Frame* par, void (*haveSeedFunc) (void));
	~SeedScreen () {
	    if (0 == --numInstances) { cleanUp (); }
	}
	void setMsg (const char* newMsg) { status->setText (newMsg); }

	void activate ();
	void deactivate ();
};

#endif /* SEED_SCREEN_H */
