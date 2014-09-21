/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include "codebreaker.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables.  You may need others for solving the challenges.  A
 * sample for one variable of the code is shown below for you.
 */

static int turn_number;
static int peg1;
static int peg2;
static int peg3;
static int peg4;


/*
 * set_seed -- uses sscanf to find the random seed value, then initializes
 *             the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation
 */
int set_seed (const char* seed_str)
{
    int seed;
    char post[2];

    if (1 == sscanf (seed_str, "%d%1s", &seed, post)) {
        srand (seed);
	return 1;
    }
    printf ("set_seed: invalid seed\n");
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
int start_game (int* one, int* two, int* three, int* four)
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
 *          *high -- number of matches greater than solution
 *          *low -- number of matches less than solution
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
static void internal_compare (int p1, int p2, int p3, int p4, int g1,
		  int g2, int g3, int g4, int* perfect, 
		  int* high, int* low)
{
    int n_perfect = 0;
    int n_high = 0;
    int n_low = 0;

    if (g1 == p1) {
	    n_perfect++;
    }
    else if (g1 < p1) {
        n_low++;
    }
    else {
        n_high++;
    }
    if (g2 == p2) {
	    n_perfect++;
    }
    else if (g2 < p2) {
        n_low++;
    }
    else {
        n_high++;
    }
    if (g3 == p3) {
	    n_perfect++;
    }
    else if (g3 < p3) {
        n_low++;
    }
    else {
        n_high++;
    }
    if (g4 == p4) {
	    n_perfect++;
    }
    else if (g4 < p4) {
        n_low++;
    }
    else {
        n_high++;
    }

    *perfect = n_perfect;
    *high = n_high;
    *low = n_low;
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
 * SIDE EFFECTS: prints the number of matches found using printf
 *               (NOTE: the output format MUST MATCH EXACTLY)
 */
int make_guess (const char* guess_str, int* one, int* two, 
	    int* three, int* four)
{
    char    post[2];
    int n_perfect;
    int n_high;
    int n_low;

    if (4 != sscanf (guess_str, "%d%d%d%d%1s", one, two, three, four, post) ||
        1 > *one || 8 < *one || 1 > *two || 8 < *two || 
	1 > *three || 8 < *three || 1 > *four || 8 < *four) {
	printf ("make_guess: invalid guess\n");
	return 0;
    }
    internal_compare (peg1, peg2, peg3, peg4, *one, *two, *three, *four, 
    		      &n_perfect, &n_high, &n_low); 
    printf ("With guess %d, you got %d perfect matches, %d "
    		  "high, and %d low.\n", turn_number++, n_perfect, 
		  n_high, n_low);

    return 1;
}

