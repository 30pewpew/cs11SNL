#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* playah - a structure made for each player where we can store information such
as their position in the board*/
typedef struct {
  int x;
  // x - position in the x coordinate
  int y;
  // y - position in the y coordinate
  int px;
  // px - x position in the character array: players, in structure: cell
  int py;
  // py - y position in the character array: players, in structure: cell
}playah;

/* cell - a structure made for each "cell" in the board that stores information
 such as players and staticElements present in that specifi cell*/
typedef struct {
  char staticElements[2][2];
  /* staticElements - a multidimensional array that will contain the non-moving
  elements of a cell such as snake heads/tails and ladder beginning/ends. These
  will be denoted by "H#", "T#", "B#", and "E#", respectively. The # will
  be replaced by a unique number to differ each snakeHead from each other.
  There can only be a maximum of two static elements per cell. */
  char players[2][2];
  /* players - a multidimensional array that will contain the players of a
  cell. These will be denoted by a symbol. There can be a maximum of 4 players
  in a cell. (You have 4 players in the game.)*/
}cell;

void printBoard(cell board[][8], char blah);
int isPlayerPresent(cell box);
void advancePlayer(cell board[][8], int *x, int *y, int px, int py, int steps);
int checkPlayer(cell board[][8], playah *dude);
int checkWin(cell board[][8], playah *dude, int *winz);

int main() {
  srand(time(NULL));
  // declarations and initializations:
  playah p1, p2, p3, p4;
  p1.x = 0; p1.y = 7;
  p1.px = 0; p1.py = 0;
  p2.x = 0; p2.y = 7;
  p2.px = 0; p2.py = 1;
  p3.x = 0; p3.y = 7;
  p3.px = 1; p3.py = 0;
  p4.x = 0; p4.y = 7;
  p4.px = 1; p4.py = 1;
  // setting each player's position to be on the bottom left of the board
  cell board[8][8];
  // board - an 8 x 8 multidimensional array of datatype: "cell".
  int i, j, k, l, r, state, winners;
  winners = 0;
  // counters for for loops
  char c, temp[2], plyr, pause;
  /* go through each cell in the board and initialize staticElements
   and players with ' ' */
  for (j = 0; j < 8; j += 1) {
    for (i = 0; i < 8; i += 1) {
      for (k = 0; k < 2; k += 1) {
        for (l = 0; l < 2; l += 1) {
          board[j][i].staticElements[k][l] = ' ';
        }
      }
      for (k = 0; k < 2; k += 1) {
        for (l = 0; l < 2; l += 1) {
          board[j][i].players[k][l] = ' ';
        }
      }
    }
  }
  // open 'board.txt' and fill up the cell array 'board' with the information
  FILE *fp;
  fp = fopen("board.txt", "r");
  // first level loop for each row
  for (j = 0; j < 8; j += 1) {
    // second level loop for the individual cells
    // top half of each cell
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if (c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[0][0] = temp[0];
        board[j][i].staticElements[0][1] = temp[1];
      } else {
        i -= 1;
      }
    }
    // bottom half of each cell
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if (c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[1][0] = temp[0];
        board[j][i].staticElements[1][1] = temp[1];
      } else {
        i -= 1;
      }
    }
  }
  fclose(fp);
  // prompt user to pick whatever player logo they want
  printf("Enter any ASCII character besides  '!', '@', and '#' to be your player token: ");
  scanf("%c", &plyr);
  /*set the bottom left corner to be the starting point and then place all the
  players  there */
  board[7][0].players[0][0] = plyr;
  board[7][0].players[1][0] = '@';
  board[7][0].players[0][1] = '#';
  board[7][0].players[1][1] = '!';
  printBoard(board, plyr);
  printf("Press enter to continue...\n");
  pause = getchar();
  pause = getchar();
  // game loop starts here
  for (;;) {
    //p1
    r = 1 + rand() % 6;
    for (i = 0; i < r; i += 1) {
      advancePlayer(board, &(p1.x), &(p1.y), (p1.px), (p1.py), 1);
      printBoard(board, plyr);
      printf("Player 1 moves %d spaces!\n", r);
      Sleep(500);
    }
    state = checkPlayer(board, &p1);
    switch(state) {
      case 1:
      printf("Player 1 landed on a snake!\n");
      Sleep(1000);
      printBoard(board, plyr);
      break;
      case 2:
      printf("Player 1 landed on a ladder!\n");
      Sleep(1000);
      printBoard(board, plyr);
      default:
      break;
    }
    printf("Press enter to continue...\n");
    //p2
    pause = getchar();
    r = 1 + rand() % 6;
    for (i = 0; i < r; i += 1) {
      advancePlayer(board, &(p2.x), &(p2.y), (p2.px), (p2.py), 1);
      printBoard(board, plyr);
      printf("Player 2 moves %d spaces!\n", r);
      Sleep(500);
    }
    state = checkPlayer(board, &p2);
    switch(state) {
      case 1:
      printf("Player 2 landed on a snake!\n");
      Sleep(1000);
      printBoard(board, plyr);
      break;
      case 2:
      printf("Player 2 landed on a ladder!\n");
      Sleep(1000);
      printBoard(board, plyr);
      default:
      break;
    }
    printf("Press enter to continue...\n");
    pause = getchar();
    //p3
    r = 1 + rand() % 6;
    for (i = 0; i < r; i += 1) {
      advancePlayer(board, &(p3.x), &(p3.y), (p3.px), (p3.py), 1);
      printBoard(board, plyr);
      printf("Player 3 moves %d spaces!\n", r);
      Sleep(500);
    }
    state = checkPlayer(board, &p3);
    switch(state) {
      case 1:
      printf("Player 3 landed on a snake!\n");
      Sleep(1000);
      printBoard(board, plyr);
      break;
      case 2:
      printf("Player 3 landed on a ladder!\n");
      Sleep(1000);
      printBoard(board, plyr);
      default:
      break;
    }
    printf("Press enter to continue...\n");
    pause = getchar();
    //p4
    r = 1 + rand() % 6;
    for (i = 0; i < r; i += 1) {
      advancePlayer(board, &(p4.x), &(p4.y), (p4.px), (p4.py), 1);
      printBoard(board, plyr);
      printf("Player 4 moves %d spaces!\n", r);
      Sleep(500);
    }
    state = checkPlayer(board, &p4);
    switch(state) {
      case 1:
      printf("Player 4 landed on a snake!\n");
      Sleep(1000);
      printBoard(board, plyr);
      break;
      case 2:
      printf("Player 4 landed on a ladder!\n");
      Sleep(1000);
      printBoard(board, plyr);
      default:
      break;
    }
    printf("Press enter to continue...\n");
    pause = getchar();
  }
}

int checkWin(cell board[][8], playah *dude, int *winz) {
  if (dude->y == 0 && dude->x == 0) {

  }
}

/* function that checks the player's current position and if it is in the same
cell as a ladder bottom or a snake head
returns 1 if the player was on a snake
returns 2 if the player was on a ladder*/
// board - the game board
// *dude - pointer to the player in question
int checkPlayer(cell board[][8], playah *dude) {
  int i, j, newx, newy, flagged;
  char num;
  flagged = 0;
  // if the cell the player is in has a snake
  if (board[dude->y][dude->x].staticElements[0][0] == 'S') {
    flagged = 1;
    // set num to the snake#
    num = board[dude->y][dude->x].staticElements[0][1];
    // search the board for its matching tail with the same#
    for (i = 0; i < 8; i += 1) {
      for (j = 0; j < 8; j += 1) {
        if ((board[i][j].staticElements[1][0] == 'T' && board[i][j].staticElements[1][1] == num) ||
        (board[i][j].staticElements[0][0] == 'T' && board[i][j].staticElements[0][1] == num)) {
          // store the coordinates of the matching tail into newx/newy
          newx=j;
          newy=i;
        }
      }
    }
    // move the player to the new coordinates (of the tail)
    board[newy][newx].players[dude->py][dude->px] = board[dude->y][dude->x].players[dude->py][dude->px];
    board[dude->y][dude->x].players[dude->py][dude->px] = ' ';
    dude->x = newx;
    dude->y = newy;
  }
  /* same thing as above but accounting for the different possible positions of
   the snake within the same cell*/
  if (board[dude->y][dude->x].staticElements[1][0] == 'S') {
    flagged = 1;
    num = board[dude->y][dude->x].staticElements[1][1];
    for (i = 0; i < 8; i += 1) {
      for (j = 0; j < 8; j += 1) {
        if ((board[i][j].staticElements[1][0] == 'T' && board[i][j].staticElements[1][1] == num) ||
        (board[i][j].staticElements[0][0] == 'T' && board[i][j].staticElements[0][1] == num)) {
          newx=j;
          newy=i;
        }
      }
    }
    board[newy][newx].players[dude->py][dude->px] = board[dude->y][dude->x].players[dude->py][dude->px];
    board[dude->y][dude->x].players[dude->py][dude->px] = ' ';
    dude->x = newx;
    dude->y = newy;
  }
  /* same things as above but with ladders */
  if (board[dude->y][dude->x].staticElements[1][0] == 'B') {
    flagged = 2;
    num = board[dude->y][dude->x].staticElements[1][1];
    for (i = 0; i < 8; i += 1) {
      for (j = 0; j < 8; j += 1) {
        if ((board[i][j].staticElements[1][0] == 'E' && board[i][j].staticElements[1][1] == num) ||
        (board[i][j].staticElements[0][0] == 'E' && board[i][j].staticElements[0][1] == num)) {
          newx=j;
          newy=i;
        }
      }
    }
    board[newy][newx].players[dude->py][dude->px] = board[dude->y][dude->x].players[dude->py][dude->px];
    board[dude->y][dude->x].players[dude->py][dude->px] = ' ';
    dude->x = newx;
    dude->y = newy;
  }
  if (board[dude->y][dude->x].staticElements[0][0] == 'B') {
    flagged = 2;
    num = board[dude->y][dude->x].staticElements[0][1];
    for (i = 0; i < 8; i += 1) {
      for (j = 0; j < 8; j += 1) {
        if ((board[i][j].staticElements[1][0] == 'E' && board[i][j].staticElements[1][1] == num) ||
        (board[i][j].staticElements[0][0] == 'E' && board[i][j].staticElements[0][1] == num)) {
          newx=j;
          newy=i;
        }
      }
    }
    board[newy][newx].players[dude->py][dude->px] = board[dude->y][dude->x].players[dude->py][dude->px];
    board[dude->y][dude->x].players[dude->py][dude->px] = ' ';
    dude->x = newx;
    dude->y = newy;
  }
  return flagged;
}

/* function that moves a player[px][py] in cell board[*x][*y]  'steps' amount
forward */
void advancePlayer(cell board[][8], int *x, int *y, int px, int py, int steps) {
  if (steps == 0) return;
  char plyr;
  int LR, curx, cury, i;
  // LR - a variable to tell which direction the player should be moving

  plyr = board[*y][*x].players[py][px];
  // store the player character into the 'plyr' variable
  if (*y % 2 == 0) {
    LR = 0;
  } else {
    LR = 1;
  }
  // if the player is on an even numbered row, it's moving towards the left(0)
  // odd numbered row towards the right(1)
  curx = *x;
  cury = *y;
  // store current player position into 'curx' and 'cury'

  while (steps > 0) {
    // break loop if there are no more steps to be made
    if (steps == 0) break;
    // if the player is on an odd numbered row
    if (LR == 1) {
      // move the player towards the end of the row(right side)
      for (i = curx; i < 7; i += 1) {
        curx += 1;
        steps -= 1;
        // so long as there are steps to be made
        if (steps == 0) break;
      }
    // otherwise if the player is on an even numbered row
    } else if (LR == 0) {
      // move the player to the other end of the row (left side)
      for (i = curx; i > 0; i -= 1) {
        curx -= 1;
        steps -= 1;
        // so long as there are steps to be made
        if (steps == 0) break;
      }
    }
    /* if the player is on the right end of the row and it still has more steps
    to nake, move it up*/
    if (LR == 1 && curx == 7 && steps > 0) {
      cury -= 1;
      steps -= 1;
      LR = 0;
      if (steps == 0) break;
    /* if the player is on the left end of the row and it still has more steps
    to make, move it up*/
    } else if (LR == 0 && curx == 0 && steps > 0) {
      cury -= 1;
      steps -= 1;
      LR = 1;
      if (steps == 0) break;
    }
    if (steps == 0) break;
  }
  // copy plyr char into the new position
  board[cury][curx].players[py][px] = plyr;
  // clear the old position
  board[*y][*x].players[py][px] = ' ';
  // update player information in the main() function
  *x = curx;
  *y = cury;
}

/* function that returns a non-zero value if there is a player present in
cell being checked. returns 0 if there are no players in the cell */
// box - of datatype cell
int isPlayerPresent(cell box) {
  // assume there are no players present in the cell
  int presence = 0;
  if (box.players[0][0] != ' ' ||
  box.players[0][1] != ' ' ||
  box.players[1][0] != ' ' ||
  box.players[1][1] != ' ') {
    // if the cell player data is not empty the there is a player present
    presence = 1;
  }
  // return
  return presence;
}

/* function that prints out the current state of the game board */
// board - a multidimensional array of datatype cell
void printBoard(cell board[][8], char blah) {
  // clear the screen
  system("cls");
  // declarations and initializations
  int i, j;
  // i, j - counters for for loop
  char temp[2];
  // char siu
  printf("   %c%c%c%c", 201, 205, 205, 205); // ╔═══
  for (i = 0; i < 7; i += 1) {
    printf("%c%c%c%c", 203, 205, 205, 205); // ╦═══
  }
  printf("%c\n", 187); // ╗
  for (j = 0; j < 8; j += 1) {
    printf("   ", j + 1);
    // top half of the row
    for (i = 0; i < 8; i += 1) {
      if (isPlayerPresent(board[j][i])) {
        // if the cell contains players, print them out
        temp[0] = board[j][i].players[0][0];
        temp[1] = board[j][i].players[0][1];
      } else {
        // otherwise, print the staticElements in the cell
        temp[0] = board[j][i].staticElements[0][0];
        temp[1] = board[j][i].staticElements[0][1];
      }
      printf("%c%c %c",186,temp[0],temp[1]); // ║S 1
    }
    printf("%c\n   ",186); // ║
    // bottom half of the row
    for (i = 0; i < 8; i += 1) {
      if (isPlayerPresent(board[j][i])) {
        temp[0] = board[j][i].players[1][0];
        temp[1] = board[j][i].players[1][1];
      } else {
        temp[0] = board[j][i].staticElements[1][0];
        temp[1] = board[j][i].staticElements[1][1];
      }
      printf("%c%c %c",186,temp[0],temp[1]); // ║T 1
    }
    printf("%c\n",186); // ║
    if (j != 7) {
      printf("   %c%c%c%c",204,205,205,205); // ╠═══
      for (i = 0; i < 7; i += 1) {
        printf("%c%c%c%c",206,205,205,205); // ╬═══
      }
      printf("%c\n",185); // ╣
    } else {
      printf("   %c%c%c%c",200,205,205,205); // ╚═══
      for (i = 0; i < 7; i += 1) {
        printf("%c%c%c%c",202,205,205,205); // ╩═══
      }
      printf("%c\n",188); // ╝
    }
  }
  printf("\n");
  printf("Snake Heads: S#\t\tPlayer 1: %c\n", blah);
  printf("Snake Tails: T#\t\tPlayer 2: @\n");
  printf("Ladder Bottoms: B#\tPlayer 3: #\n");
  printf("Ladder Ends: E#\t\tPlayer 4: !\n");
  printf("\n");
}
