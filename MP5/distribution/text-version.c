#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

int32_t kill_printf (const char* fmt, ...);

/* 
 * Your code is included as part of this file.  Notice that
 * any calls to printf are rerouted to a routine that prints
 * a message designed to get your attention.  Such calls will
 * not reach the GUI versions, but will appear identical in the
 * text version output, so it's important that you not use
 * printf.
 */
#define printf kill_printf
#include "jni/prog5.c"
#undef printf

int32_t 
kill_printf (const char* fmt, ...)
{
    puts ("DO NOT USE PRINTF IN YOUR CODE.  USE prog5_printf INSTEAD.");
    return 0;
}

int32_t 
prog5_printf (const char* fmt, ...)
{
    va_list args;
    int ret_val;

    va_start (args, fmt);
    ret_val = vprintf (fmt, args);
    va_end (args);

    return ret_val;
}

int
main ()
{
    char buf[200];
    int32_t turn;
    int32_t peg[4];
    int32_t guess[4];

    do {
	printf ("Please enter a seed: ");
	if (NULL == fgets (buf, 200, stdin)) {
	    printf ("\nProgram terminated.\n");
	    return 3;
	}
    } while (!set_seed (buf));

    if (!start_game (&peg[0], &peg[1], &peg[2], &peg[3])) {
        printf ("\nGame start failed.\n");
	return 3;
    }

    for (turn = 1; 12 >= turn; turn++) {
	printf ("Guess %d\n", turn);
	do {
	    printf ("Enter your guess (#1 #2 #3 #4): ");
	    if (NULL == fgets (buf, 200, stdin)) {
		printf ("\nProgram terminated.\n");
		return 3;
	    }
	} while (!make_guess (buf, &guess[0], &guess[1], &guess[2], &guess[3]));
	if (guess[0] == peg[0] && guess[1] == peg[1] && guess[2] == peg[2] &&
	    guess[3] == peg[3]) {
	    printf ("You guessed correctly in %d guesses.\n", turn);
	    return 0;
	}
    }
    puts ("You failed to guess correctly in 12 guesses.\n");
    printf ("The solution was %d %d %d %d.\n", peg[0], peg[1], peg[2], peg[3]);

    return 0;
}

