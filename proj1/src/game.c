#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  game_t *game = malloc(sizeof(game_t));

  game->num_rows = 18;
  game->board = malloc(sizeof(char *) * game->num_rows);

  for (int i=0; i < game->num_rows; i++){
    game->board[i] = malloc(sizeof(char) * 22);
  }

  strcpy(game->board[0], "####################\n");
  strcpy(game->board[1], "#                  #\n");
  strcpy(game->board[2], "# d>D    *         #\n");

  for (int i=3; i < game->num_rows - 1; i++){
    strcpy(game->board[i], game->board[1]);
  }

  strcpy(game->board[game->num_rows-1], game->board[0]);

  game->num_snakes = 1;
  game->snakes = malloc(sizeof(snake_t));

  game->snakes->tail_row = 2;
  game->snakes->tail_col = 2;
  game->snakes->head_row = 2;
  game->snakes->head_col = 4;
  game->snakes->live = 1;

  return game;
}


/* Task 2 */
void free_game(game_t *game) {
  for (int i=0; i < game->num_rows; i++){
    free(game->board[i]);
  }

  free(game->board);
  free(game->snakes);
  free(game);

  return;
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  for (int i=0; i < game->num_rows; i++){
    fprintf(fp, "%s", game->board[i]);
  }

  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  return (strchr("wasd", c) != NULL);
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  return (strchr("WASDx", c) != NULL);
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  return (strchr("wasd^<v>WASDx", c) != NULL);
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  switch (c) {
    case '^':
      return 'w';
      break;

    case '<':
      return 'a';
      break;

    case 'v':
      return 's';
      break;

    case '>':
      return 'd';
      break; 

    default: 
      return '?';
      break;     
  }
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  switch (c) {
    case 'W':
      return '^';
      break;

    case 'A':
      return '<';
      break;

    case 'S':
      return 'v';
      break;

    case 'D':
      return '>';
      break; 

    default: 
      return '?';
      break;     
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  switch (c) {
    case 'v':
    case 's':
    case 'S':
      return cur_row + 1;
      break;

    case '^':
    case 'w':
    case 'W':
      return cur_row - 1;
      break;

    default:   
      return cur_row;
      break;
  }
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  switch (c) {
    case '>':
    case 'd':
    case 'D':
      return cur_col + 1;
      break;

    case '<':
    case 'a':
    case 'A':
      return cur_col - 1;
      break;

    default:   
      return cur_col;
      break;
  }
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  /*沒看好寫成for loop了
    unsigned int cnt_snake = 0;
    unsigned int tail_to_head_row, tail_to_head_col;
    char tail_to_head, _next_square;
    bool found_tail = false;


    for (unsigned int i=0; i < game->num_rows; i++){
      for (unsigned int j=0; j < 20; j++){

        if (is_tail(game->board[i][j])){
          if (cnt_snake == snum){
            tail_to_head_row = i;
            tail_to_head_col = j;
            tail_to_head = body_to_tail(game->board[i][j]);
            found_tail = true;
            break;
          }
          cnt_snake++;
        }
      }
      if (found_tail){
        break;
      }
    }
    
    while (!is_head(tail_to_head)){
      tail_to_head_row = get_next_row(tail_to_head_row, tail_to_head);
      tail_to_head_col = get_next_col(tail_to_head_col, tail_to_head);
      tail_to_head = game->board[tail_to_head_row][tail_to_head_col];
    }

    tail_to_head_row = get_next_row(tail_to_head_row, tail_to_head);
    tail_to_head_col = get_next_col(tail_to_head_col, tail_to_head);
    _next_square = game->board[tail_to_head_row][tail_to_head_col];

    return _next_square;
  */
  unsigned int head_row = game->snakes[snum].head_row;
  unsigned int head_col = game->snakes[snum].head_col;
  char head = get_board_at(game, head_row, head_col);
  unsigned int next_hr = get_next_row(head_row, head);
  unsigned int next_hc = get_next_col(head_col, head);
  char next_square = get_board_at(game, next_hr, next_hc);
  return next_square;
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  unsigned int head_row = game->snakes[snum].head_row;
  unsigned int head_col = game->snakes[snum].head_col;
  char head = get_board_at(game, head_row, head_col);
  unsigned int next_hr = get_next_row(head_row, head);
  unsigned int next_hc = get_next_col(head_col, head);
  set_board_at(game, head_row, head_col, head_to_body(head));
  set_board_at(game, next_hr, next_hc, head);

  game->snakes[snum].head_row = next_hr;
  game->snakes[snum].head_col = next_hc;
  return;
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  unsigned int tail_row = game->snakes[snum].tail_row;
  unsigned int tail_col = game->snakes[snum].tail_col;
  char tail = get_board_at(game, tail_row, tail_col);
  char new_tail = body_to_tail(get_board_at(game, get_next_row(tail_row, tail), get_next_col(tail_col, tail)));
  unsigned int new_tr = get_next_row(tail_row, tail);
  unsigned int new_tc = get_next_col(tail_col, tail);
  set_board_at(game, tail_row, tail_col, ' ');
  set_board_at(game, new_tr, new_tc, new_tail);
  game->snakes[snum].tail_row = new_tr;
  game->snakes[snum].tail_col = new_tc;
  return;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  for (unsigned int snum = 0; snum < game->num_snakes; snum++) {
    if (!game->snakes[snum].live) {
      continue;
    }

    char next_square_char = next_square(game, snum);

    if (next_square_char == ' ' || next_square_char == '*') {
      update_head(game, snum);
      if (next_square_char == ' ') {
        update_tail(game, snum);
      } else {
        (*add_food)(game);
      }
    } else {
      game->snakes[snum].live = false;
      set_board_at(game, game->snakes[snum].head_row, game->snakes[snum].head_col, 'x');
    }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  if (fp == NULL) {
    return NULL;
  }

  unsigned int capacity = 16;
  unsigned int length = 0;
  char *lineptr = malloc(sizeof(char) * capacity);
  if (lineptr == NULL) {
    return NULL;
  }

  lineptr[0] = '\0';

  while (true) {
    unsigned int rem_space = capacity - length;

    char *result = fgets(lineptr + length, (int)rem_space, fp);
    length = (unsigned int)strlen(lineptr);

    if (result == NULL) {
      if (length == 0) {
        free(lineptr);
        return NULL;
      }
      /*一行讀完但沒\n*/
      break; 
    }
    
    /*一行讀完且有\n*/
    if (lineptr[length - 1] == '\n') {
      break;
    }

    /*如果空間不夠讀完一行*/
    capacity *= 2;
    char *new_lineptr = realloc(lineptr, capacity * sizeof(char));
    if (new_lineptr == NULL) {
        free(lineptr);
        return NULL;
    }
    lineptr = new_lineptr;
  }

  char *exact_lineptr = realloc(lineptr, (length + 1) * sizeof(char));
  if (exact_lineptr == NULL) {
      free(lineptr);
      return NULL;
  }
  lineptr = exact_lineptr;

  return lineptr;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  game_t *game = malloc(sizeof(game_t));
  if (game == NULL) {
    return NULL;
  }

  unsigned int row_cnt = 0;
  game->board = NULL;

  char *line;
  line = read_line(fp);

  while (line != NULL) {
    game->board = realloc(game->board, sizeof(char *) * (row_cnt + 1));
    if (game->board == NULL) {
      free_game(game);
      return NULL;
    }
    game->board[row_cnt] = line;
    line = read_line(fp);
    row_cnt++;
  }
    
  if (row_cnt == 0) {
    free_game(game);
    return NULL;
  }

  game->num_rows = row_cnt;
  game->num_snakes = 0;
  game->snakes = NULL;

  return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  char trace = get_board_at(game, game->snakes[snum].tail_row, game->snakes[snum].tail_col);
  unsigned int cur_row = game->snakes[snum].tail_row;
  unsigned int cur_col = game->snakes[snum].tail_col;

  while (!is_head(trace)) {
    cur_row = get_next_row(cur_row, trace);
    cur_col = get_next_col(cur_col, trace);
    trace = get_board_at(game, cur_row, cur_col);
  }
  game->snakes[snum].head_row = cur_row;
  game->snakes[snum].head_col = cur_col;
  return;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  game->snakes = NULL;
  
  unsigned int row_cnt = 0;
  unsigned int snake_cnt = 0;
  while (row_cnt < game->num_rows) {
    unsigned int col_cnt = 0;
    while (col_cnt < strlen(game->board[row_cnt])-1) {
      if (is_tail(get_board_at(game, row_cnt, col_cnt))) {
        game->snakes = realloc(game->snakes, sizeof(snake_t) * (snake_cnt + 1));
        if (game->snakes == NULL) {
          free_game(game);
          return NULL;
        }
        game->snakes[snake_cnt].tail_row = row_cnt;
        game->snakes[snake_cnt].tail_col = col_cnt;
        find_head(game, snake_cnt);
        game->snakes[snake_cnt].live = true;
        snake_cnt++;
      }
      col_cnt++;
    }
    row_cnt++;
  }
  game->num_snakes = snake_cnt;
  return game;
}
