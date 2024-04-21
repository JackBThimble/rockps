#include <errno.h>
#include <fcntl.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "random.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD         4

char *choices[] = {"Rock", "Paper", "Scissors", "Show Scores", "Exit"};

void
init_curses(void);
void
print_main_menu(void);
void
print_center_x(WINDOW *win, int line, int x_offset, const char *str, ...);
void
play(int n, int r);
void
           show_scores(void);

static int player_score  = 0;
static int cpu_score     = 0;
static int rounds_played = 0;

int
main(void)
{
        init_curses();

        while (1) {
                unsigned int random_int     = urandom();
                int          player_1_input = -1;

                print_main_menu();

                while (player_1_input < 1 || player_1_input > 5) {
                        int ch = getch();
                        if (ch >= '0' && ch <= '5') {
                                char *cptr;
                                player_1_input =
                                        (int)strtol((char *)&ch, &cptr, 10);
                        } else {
                                clear();
                                int line = LINES / 2;
                                print_center_x(stdscr, line, 0,
                                               "Invalid selection...");
                                print_center_x(stdscr, line + 1, 0,
                                               "Press any key to continue.");
                                refresh();
                                getch();
                                clear();
                                print_main_menu();
                        }
                }

                switch (player_1_input) {
                case 1:
                        play(1, (random_int % 3) + 1);
                        break;
                case 2:
                        play(2, (random_int % 3) + 1);
                        break;
                case 3:
                        play(3, (random_int % 3) + 1);
                        break;
                case 4:
                        show_scores();
                        break;
                case 5:
                        endwin();
                        exit(0);
                        break;
                default:
                        endwin();
                        exit(0);
                        break;
                }
        }
        endwin();

        return 0;
}

void
show_scores(void)
{
        clear();
        int   line = LINES / 2;
        float win_percent =
                ((float)player_score / (player_score + cpu_score) * 100.0);
        float loss_percent = cpu_score /
                             (float)((float)player_score + (float)cpu_score) *
                             100.0;
        float tie_percent =
                (float)((rounds_played - (float)(player_score + cpu_score)) /
                        (float)rounds_played) *
                100.0;
        print_center_x(stdscr, line - 4, 0, "SCORE BOARD");
        print_center_x(stdscr, line + 1, -10, "Your score: %d", player_score);
        print_center_x(stdscr, line + 2, -10, "CPU score: %d", cpu_score);
        print_center_x(stdscr, line + 3, -10, "Rounds played: %d",
                       rounds_played);
        print_center_x(stdscr, line + 4, -10, "Win percentage: %f",
                       win_percent);
        print_center_x(stdscr, line + 5, -10, "Loss percentage: %f",
                       loss_percent);
        print_center_x(stdscr, line + 6, -10, "Draw percentage: %f",
                       tie_percent);
        print_center_x(stdscr, line + 10, 0,
                       "Press any key to return to the main menu...");
        refresh();
        getch();
        print_main_menu();
}

void
play(int n, int r)
{
        rounds_played++;
        int line = LINES / 2;

        clear();
        switch (r) {
        case 1:
                switch (n) {
                case 1:
                        print_center_x(stdscr, line - 4, 0, "ROCK vs ROCK");
                        print_center_x(stdscr, line, 0, "You tied.");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0,
                                       "PAPER covers ROCK");
                        print_center_x(stdscr, line, 0, "YOU WIN!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        player_score++;
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "ROCK breaks SCISSORS");
                        print_center_x(stdscr, line, 0, "YOU LOSE!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        cpu_score++;
                        break;
                default:
                        break;
                }
                break;
        case 2:
                switch (n) {
                case 1:
                        print_center_x(stdscr, line - 4, 0,
                                       "PAPER covers ROCK");
                        print_center_x(stdscr, line, 0, "YOU LOSE!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        cpu_score++;
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0, "PAPER vs PAPER");
                        print_center_x(stdscr, line, 0, "You tied.");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS cut PAPER");
                        print_center_x(stdscr, line, 0, "YOU WIN!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        player_score++;
                        break;
                default:
                        break;
                }
                break;
        case 3:
                switch (n) {
                case 1:
                        print_center_x(stdscr, line - 4, 0,
                                       "ROCK breaks SCISSORS");
                        print_center_x(stdscr, line, 0, "YOU WIN!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        player_score++;
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS cut PAPER");
                        print_center_x(stdscr, line, 0, "YOU LOSE!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        cpu_score++;
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS vs SCISSORS");
                        print_center_x(stdscr, line, 0, "You tied.");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        getch();
                        break;
                default:
                        break;
                }
                break;
        default:
                break;
        }
}
void
print_main_menu(void)
{
        clear();
        print_center_x(stdscr, 8, 0, "Let's Play!!!");
        print_center_x(stdscr, 10, 0, "Choose your fate: ");
        for (int i = 0; i < (int)ARRAY_SIZE(choices); i++)
                print_center_x(stdscr, i + 12, -4, "%d. %s.", i + 1,
                               choices[i]);
        refresh();
}

void
print_center_x(WINDOW *win, int line, int x_offset, const char *str, ...)
{
        va_list args;
        va_start(args, (char *));
        int max_x;
        int start_y, start_x;
        max_x    = getmaxx(win);

        start_y  = line;
        start_x  = (max_x / 2) - (strlen(str) / 2);
        start_x += x_offset;
        move(start_y, start_x);
        vw_printw(win, str, args);
}

void
init_curses(void)
{
        initscr();
        start_color();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
}
