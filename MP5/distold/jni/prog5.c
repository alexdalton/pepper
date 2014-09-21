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
 * Version:	    1.02
 * Creation Date:   7 February 2013
 * Filename:	    prog5.c
 * History:
 *	SL	1.00	7 February 2013
 *		First created.
 *	SL	1.01	9 February 2013
 *		Gold version and challenges ready completed.
 *	SL	1.02	9 February 2013
 *		Assignment version created.
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
static int32_t soln1;


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
    srand (12345);
    return 1;
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
    *one = 1;
    *two = 1;
    *three = 1;
    *four = 1;
    return 1;
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
    return 0;
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
    return 0;
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
    return 0;
}

