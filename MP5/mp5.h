/* 
 * Called when the user enters a string for a game's random seed.  Returns 0
 * if the seed string is invalid, or 1 if the string is a valid number. 
 * When successful, also calls srand with the seed as an argument to 
 * initialize the random number generator.
 */
int set_seed (const char* seed_str);

/*
 * Called before starting the game.  Selects four color values using the
 * algorithm defined in the specification.  Copies those four values into
 * the four integer points passed into the function.  Your code will also
 * need to retain a copy of the 'correct' answer for the game for the 
 * make_guess function (below).  Returns 1 on success, or 0 on error.
 */
int start_game (int* one, int* two, int* three, int* four);

/*
 * Called when the user enters a string t make a guess.  Returns 0 if the
 * guess is invalid, whether because it does not correspond to a sequence
 * of four numbers or because any of the numbers is outside of the range
 * 1 to 8.  Returns 1 on success, copies the guessed values into the
 * integer pointers passed to the function, and prints a message using the
 * format given in the specification to tell the player how many perfect
 * and misplaced matches were found for the guess made.
 */
int make_guess (const char* guess_str, int* one, int* two, 
		    int* three, int* four);

/*
 * Called to check whether the current guess matches the feedback for
 * a previous guess.  Not used by the text version.  The GUI keeps
 * track of previous guesses and provides them to you for this function.
 * The function should return 1 if and only if the new guess (possibly
 * including 0's for unfilled locations) might be the solution, given
 * that the original guess (first four arguments) resulted in the
 * number of perfect and misplaced matches provided as arguments.
 */
int compare_guesses (int orig1, int orig2, int orig3,
			 int orig4, int n_perfect, int n_misplaced,
			 int guess1, int guess2,
			 int guess3, int guess4);

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
int get_hint (int* hint);
