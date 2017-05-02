#include        <stdio.h>
#include	<curses.h>

#include	"panex.h"

#define		CONGRATULATIONS	"CONGRATULATIONS!!!"
#define		TAUNT		"See, wasn't that easy?"

/* Move stack. */
#define	STACK_SIZE	100000

typedef struct {

	int	src;
	int	dest;

} MOVE;

typedef struct {

	int	top;
	int	contents;
	MOVE	moves [STACK_SIZE];

} MOVE_STACK;


static void resetMoveStack ( MOVE_STACK *stack )

{
   stack->top = stack->contents = 0;
}


static void pushMove ( MOVE_STACK *stack, int src, int dest )

{
   stack->moves [stack->top].src = src;
   stack->moves [stack->top].dest = dest;
   if ( ++stack->top == STACK_SIZE ) stack->top = 0;

   if ( stack->contents < STACK_SIZE ) ++stack->contents;
}


static const MOVE *popMove ( MOVE_STACK *stack )

{
   const MOVE	*move = NULL;

   if ( stack->contents ) {

	--stack->contents;

	if ( --stack->top < 0 ) stack->top += STACK_SIZE;

	move = stack->moves + stack->top;
   }

   return ( move );
}


int playGame ( PUZZLE *puzzle )

{
   int	status = 1;
   int	yt;
   int	xp [3];
   int	c = 'r';

   yt = puzzle->y0 + 2;
   xp [0] = puzzle->x0 + puzzle->height + 1;
   xp [1] = xp [0] + ( ( puzzle->height + 1 ) << 1 );
   xp [2] = xp [1] + ( ( puzzle->height + 1 ) << 1 );

   while ( c == 'r' ) {

	int		peg = LEFT_PEG;
	int		src = -1;
	int		cur_ch = ACS_DIAMOND;
	int		done = 0;
	MOVE_STACK	moveHistory;
	const MOVE	*lastMove;

	resetMoveStack ( &moveHistory );

	move ( yt, xp [0] );
	addch ( cur_ch );
	move ( 0, 0 );
	refresh ();

	while ( ! done ) {

		switch ( c = getch () ) {

		   char	*p;

		   case 'v':
		   case 'j':
		   case KEY_DOWN:

			if ( src != -1 ) {

				move ( yt, xp [peg] );
				addch ( ' ' );

				if ( src != peg ) pushMove ( &moveHistory, src,
									peg );
				if ( src == peg
					|| moveDisk ( puzzle, src, peg ) ) {

					if ( isSolved ( puzzle ) ) {

						p = CONGRATULATIONS;

						move ( yt, puzzle->xc
						- ( sizeof ( CONGRATULATIONS )
								>> 1 ) );
						
						while ( *p ) addch ( *p++ );
						done = 1;
					}

					cur_ch ^= A_REVERSE;
					src = -1;

				} else beep ();

			} else beep ();

			break;

		   case '^':
		   case 'k':
		   case KEY_UP:

			if ( src == -1 && puzzle->peg_tops [peg] > 0 ) {

				src = peg;
				cur_ch ^= A_REVERSE;
				
			} else beep ();

			break;

		   case '<':
		   case 'h':
		   case KEY_LEFT:

			if ( peg > LEFT_PEG && ( src == -1
						|| src == ( peg - 1 )
						|| puzzle->peg_tops [peg - 1]
							<= puzzle->height ) ) {

				move ( yt, xp [peg--] );
				addch ( ' ' );

			} else beep ();

			break;

		   case '>':
		   case 'l':
		   case KEY_RIGHT:

			if ( peg < RIGHT_PEG && ( src == -1
						|| src == ( peg + 1 )
						|| puzzle->peg_tops [peg + 1]
							<= puzzle->height ) ) {

				move ( yt, xp [peg++] );
				addch ( ' ' );

			} else beep ();

			break;

		   case 's':

			move ( yt, xp [peg] );
			addch ( ' ' );

			puzzle->speed = XTREME_SPEED;
			puzzle->warpFactor = 2;

			if ( ( status = generalSolution ( puzzle,
							puzzle->height ) )
						&& isSolved ( puzzle ) ) {
				p = TAUNT;
				move ( yt, puzzle->xc
						- ( sizeof ( TAUNT ) >> 1 ) );
				while ( *p ) addch ( *p++ );
			}

			done = 1;
			break;

		   case ESC:

			if ( src != -1 ) {

				cur_ch ^= A_REVERSE;
				src = -1;
				break;
			}

		   case 'q':

			puzzle->moves = 0;
			status = 0;

		   case 'r':

			done = 1;
			break;

		   case 'u':

			if ( lastMove = popMove ( &moveHistory ) ) {

				if ( src != -1 ) {

					src = -1;
					cur_ch ^= A_REVERSE;
				}

				move ( yt, xp [peg] );
				addch ( ' ' );
				puzzle->moves -= 2;
				peg = lastMove->src;
				moveDisk ( puzzle, lastMove->dest, peg );

			} else beep();

			break;

		   case 'S':

			puzzle->speed = SLOW_SPEED;
			puzzle->warpFactor = 1;
			break;

		   case 'N':

			puzzle->speed = NORMAL_SPEED;
			puzzle->warpFactor = 1;
			break;

		   case 'F':

			puzzle->speed = HIGH_SPEED;
			puzzle->warpFactor = 1;
			break;

		   case 'X':

			puzzle->speed = XTREME_SPEED;
			puzzle->warpFactor = 1;
			break;

		   case 'W':

			puzzle->speed = XTREME_SPEED;
			puzzle->warpFactor = 2;
			break;

		   case ERR:

			break;

		   default:

			beep ();
			break;
		}

		if ( ! done ) {

			move ( yt, xp [peg] );
			addch ( cur_ch );
		}

		move ( 0, 0 );
		refresh ();
	}

	if ( c != 'q' && c != 'r' && c != ESC )
		while ( ( c = getch() ) == ERR );

	if ( c == 'r' ) {

		resetPuzzle ( puzzle );
		displayPuzzle ( puzzle );

	} else ungetch ( c );
   }

   return ( status );
}
