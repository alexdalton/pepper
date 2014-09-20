/*									tab:8
 *
 * prog5.c - source file for UIUC ECE198KL Spring 2013 Program 5
 *           student code -- GOLD VERSION
 *
 * "Copyright (c) 2013 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    1.01
 * Creation Date:   7 February 2013
 * Filename:	    prog5.c
 * History:
 *	SL	1.00	7 February 2013
 *		First created.
 *	SL	1.01	9 February 2013
 *		Gold version and challenges ready completed.
 */

#include "prog5.h"


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables.  You may need others for solving the challenges.  A
 * sample for one variable of the code is shown below for you.
 */

static int32_t turn_number;
static int32_t peg1;
static int32_t peg2;
static int32_t peg3;
static int32_t peg4;
static int32_t guesses[12][4];
static int32_t result_p[12];
static int32_t result_m[12];


/*
 * set_seed -- uses sscanf to find the random seed value, then initializes
 *             the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation
 */
int32_t 
set_seed (const char* seed_str)
{
    int seed;
    char post[2];

    if (1 == sscanf (seed_str, "%d%1s", &seed, post)) {
        srand (seed);
	return 1;
    }
    prog5_printf ("set_seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- creates the solution combination using the approach
 *               described in the assignment specification (using rand)
 * INPUTS: none
 * OUTPUTS: *one -- the first color value in the code (between 1 and 8)
 *          *two -- the second color value in the code (between 1 and 8)
 *          *three -- the third color value in the code (between 1 and 8)
 *          *four -- the fourth color value in the code (between 1 and 8)
 * RETURN VALUE: 1 on success, or 0 on failure (should never fail, though)
 * SIDE EFFECTS: records the solution code for use by make_guess
 */
int32_t
start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four)
{
    peg1 = (rand () % 8) + 1;
#if 1
    peg2 = (rand () % 8) + 1;
    peg3 = (rand () % 8) + 1;
    peg4 = (rand () % 8) + 1;
#else
    /* scheme for pegs with distinct colors */
    do {
	peg2 = (rand () % 8) + 1;
    } while (peg1 == peg2);
    do {
	peg3 = (rand () % 8) + 1;
    } while (peg1 == peg3 || peg2 == peg3);
    do {
	peg4 = (rand () % 8) + 1;
    } while (peg1 == peg4 || peg2 == peg4 || peg3 == peg4);
#endif
    *one   = peg1;
    *two   = peg2;
    *three = peg3;
    *four  = peg4;
    turn_number = 1;
    return 1;
}


/*
 * internal_compare -- gold version function for comparing two codes
 * INPUTS: p1-p4 -- solution/original code
 *         g1-g4 -- guess code
 * OUTPUTS: *perfect -- number of perfect matches
 *          *misplaced -- number of matches out of position in code
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
static void
internal_compare (int32_t p1, int32_t p2, int32_t p3, int32_t p4, int32_t g1,
		  int32_t g2, int32_t g3, int32_t g4, int32_t* perfect, 
		  int32_t* misplaced)
{
    int32_t n_perfect = 0;
    int32_t n_misplaced = 0;

    if (g1 == p1) {
	g1 = p1 = 0;
	n_perfect++;
    }
    if (g2 == p2) {
        g2 = p2 = 0;
	n_perfect++;
    }
    if (g3 == p3) {
        g3 = p3 = 0;
	n_perfect++;
    }
    if (g4 == p4) {
        g4 = p4 = 0;
	n_perfect++;
    }
    if (g1) {
        if (g1 == p2) {
	    p2 = 0;
	    n_misplaced++;
	} else if (g1 == p3) {
	    p3 = 0;
	    n_misplaced++;
	} else if (g1 == p4) {
	    p4 = 0;
	    n_misplaced++;
	}
    }
    if (g2) {
        if (g2 == p1) {
	    p1 = 0;
	    n_misplaced++;
	} else if (g2 == p3) {
	    p3 = 0;
	    n_misplaced++;
	} else if (g2 == p4) {
	    p4 = 0;
	    n_misplaced++;
	}
    }
    if (g3) {
        if (g3 == p1) {
	    p1 = 0;
	    n_misplaced++;
	} else if (g3 == p2) {
	    p2 = 0;
	    n_misplaced++;
	} else if (g3 == p4) {
	    p4 = 0;
	    n_misplaced++;
	}
    }
    if (g4) {
        if (g4 == p1) {
	    n_misplaced++;
	} else if (g4 == p2) {
	    n_misplaced++;
	} else if (g4 == p3) {
	    n_misplaced++;
	}
    }
    *perfect = n_perfect;
    *misplaced = n_misplaced;
}


/*
 * make_guess -- calculates the number of perfect and misplaced matches
 *               for a given guess, relative to the solution code recorded
 *               earlier by start_game
 * INPUTS: guess_str -- a string consisting of four numbers for the guess
 * OUTPUTS: the following are only valid if the function returns 1
 *          *one -- the first color value in the guessed code (between 1 and 8)
 *          *two -- the second color value in the guessed code (between 1 and 8)
 *          *three -- the third color value in the guessed code
 *                    (between 1 and 8)
 *          *four -- the fourth color value in the guessed code
 *                    (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (represents exactly four
 *               numbers between 1 and 8), or if it is not
 * SIDE EFFECTS: prints the number of matches found using prog5_printf
 *               (NOTE: the output format MUST MATCH EXACTLY)
 */
int32_t
make_guess (const char* guess_str, int32_t* one, int32_t* two, 
	    int32_t* three, int32_t* four)
{
    char    post[2];
    int32_t n_perfect;
    int32_t n_misplaced;

    if (4 != sscanf (guess_str, "%d%d%d%d%1s", one, two, three, four, post) ||
        1 > *one || 8 < *one || 1 > *two || 8 < *two || 
	1 > *three || 8 < *three || 1 > *four || 8 < *four) {
	prog5_printf ("make_guess: invalid guess\n");
	return 0;
    }
    guesses[turn_number - 1][0] = *one;
    guesses[turn_number - 1][1] = *two;
    guesses[turn_number - 1][2] = *three;
    guesses[turn_number - 1][3] = *four;
    internal_compare (peg1, peg2, peg3, peg4, *one, *two, *three, *four, 
    		      &n_perfect, &n_misplaced); 
    result_p[turn_number - 1] = n_perfect;
    result_m[turn_number - 1] = n_misplaced;
    prog5_printf ("With guess %d, you got %d perfect matches and %d "
    		  "misplaced matches.\n", turn_number++, n_perfect, 
		  n_misplaced);

    return 1;
}


/*
 * compare_guesses -- compares two guesses to check whether a new guess
 *                    might be the solution, given the feedback on a previous
 *                    guess in terms of perfect and misplaced matches
 * INPUTS: orig1-orig4 -- the original code (an earlier guess)
 *         n_perfect -- the number of perfect matches for original code
 *         n_misplaced -- the number of perfect matches for original code
 *                        (your printed response to make_guess is stored for
 *                         this purpose)
 *         guess1-guess4 -- the new guess
 * OUTPUTS: none
 * RETURN VALUE: 1 if the guess code *could* be the solution, as determined
 *               by the original code and the feedback given on it
 * SIDE EFFECTS: none
 */
int32_t 
compare_guesses (int32_t orig1, int32_t orig2, int32_t orig3, int32_t orig4, 
		 int32_t n_perfect, int32_t n_misplaced, int32_t guess1, 
		 int32_t guess2, int32_t guess3, int32_t guess4)
{
    int32_t perf, misp;

    internal_compare (orig1, orig2, orig3, orig4, guess1, guess2, guess3, 
		      guess4, &perf, &misp);
    return (perf == n_perfect && misp == n_misplaced);
}


/*
 * get_hint -- obtains a hint code (four values from 1 to 8) that matches
 *             the feedback on all previous guesses
 *                    might be the solution, given the feedback on a previous
 * INPUTS: hint -- pointer to an array of four integers for storing the hint
 * OUTPUTS: hint[0]-hint[3] -- the hint given (if 1 is returned)
 * RETURN VALUE: 1 if a hint has been offered, or 0 otherwise
 * SIDE EFFECTS: none
 *
 * NOTE: You will have to track previous guesses and feedback yourself.  
 * NO CREDIT will be given for a hint function that always returns the 
 * solution as a hint.
 */
int32_t
get_hint (int32_t* hint)
{
    int32_t p1, p2, p3, p4;
    int32_t which;
    int32_t match;

    for (p1 = 1; 8 >= p1; p1++) {
	for (p2 = 1; 8 >= p2; p2++) {
	    for (p3 = 1; 8 >= p3; p3++) {
		for (p4 = 1; 8 >= p4; p4++) {
		    match = 1;
		    for (which = 1; turn_number > which; which++) {
			int32_t num_p, num_m;

		        internal_compare 
				(guesses[which - 1][0], guesses[which - 1][1],
				 guesses[which - 1][2], guesses[which - 1][3],
				 p1, p2, p3, p4, &num_p, &num_m);
			if (num_p != result_p[which - 1] ||
			    num_m != result_m[which - 1]) {
			    match = 0;
			    break;
			}
		    }
		    if (match) {
			hint[0] = p1;
			hint[1] = p2;
			hint[2] = p3;
			hint[3] = p4;
			return 1;
		    }
		}
	    }
	}
    }
    /* should not happen! */
    return 0;
}

