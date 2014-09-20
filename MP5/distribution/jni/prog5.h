/*									tab:8
 *
 * prog5.h - header file for UIUC ECE198KL Spring 2013 Program 5
 *           student code
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
 * Filename:	    prog7.h
 * History:
 *	SL	1.00	7 February 2013
 *		First created.
 *	SL	1.01	9 February 2013
 *		Gold version and challenges ready completed.
 */

#if !defined(PROG_5_H)
#define PROG_5_H

#include <stdarg.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                  PROGRAM 5 EXTERNALLY DEFINED FUNCTIONS                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/*
 * Use in place of printf when printing all messages from your functions.
 * Syntax and escape values are identical.
 */
extern int32_t prog5_printf (const char* fmt, ...);


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                  PROGRAM 5 EXTERNALLY VISIBLE FUNCTIONS                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Called when the user enters a string for a game's random seed.  Returns 0
 * if the seed string is invalid, or 1 if the string is a valid number. 
 * When successful, also calls srand with the seed as an argument to 
 * initialize the random number generator.
 */
int32_t set_seed (const char* seed_str);

/*
 * Called before starting the game.  Selects four color values using the
 * algorithm defined in the specification.  Copies those four values into
 * the four integer points passed into the function.  Your code will also
 * need to retain a copy of the 'correct' answer for the game for the 
 * make_guess function (below).  Returns 1 on success, or 0 on error.
 */
int32_t start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four);

/*
 * Called when the user enters a string t make a guess.  Returns 0 if the
 * guess is invalid, whether because it does not correspond to a sequence
 * of four numbers or because any of the numbers is outside of the range
 * 1 to 8.  Returns 1 on success, copies the guessed values into the
 * integer pointers passed to the function, and prints a message using the
 * format given in the specification to tell the player how many perfect
 * and misplaced matches were found for the guess made.
 */
int32_t make_guess (const char* guess_str, int32_t* one, int32_t* two, 
		    int32_t* three, int32_t* four);

/*
 * Called to check whether the current guess matches the feedback for
 * a previous guess.  Not used by the text version.  The GUI keeps
 * track of previous guesses and provides them to you for this function.
 * The function should return 1 if and only if the new guess (possibly
 * including 0's for unfilled locations) might be the solution, given
 * that the original guess (first four arguments) resulted in the
 * number of perfect and misplaced matches provided as arguments.
 */
int32_t compare_guesses (int32_t orig1, int32_t orig2, int32_t orig3,
			 int32_t orig4, int32_t n_perfect, int32_t n_misplaced,
			 int32_t guess1, int32_t guess2,
			 int32_t guess3, int32_t guess4);

/*
 * Called to obtain a hint based on previous guesses and feedback.  Note
 * that the argument here is a pointer to an array of four integers that
 * the function fills in with a set of values that match all previous
 * feedback on guesses.  You will have to track previous guesses and 
 * feedback yourself.  If your function selects a set of hint values, it
 * should return 1.  The default implementation returns 0 (which should
 * never technically be necessary) to indicate that no hint is available.
 *
 * NOTE: NO CREDIT will be given for a hint function that always returns 
 * the solution as a hint.
 */
int32_t get_hint (int32_t* hint);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)

#endif /* PROG_5_H */


