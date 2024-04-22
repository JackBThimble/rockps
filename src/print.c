#define _POSIX_C_SOURCE 199309L
#include "print.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *choices[] = {"Rock", "Paper", "Scissors", "Show Scores", "Exit"};

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

void
print_main_menu(void)
{
        clear();
        print_center_x(stdscr, 8, 0, "Let's Play!!!");
        print_center_x(stdscr, 10, 0, "Choose your fate: ");
        for (int i = 0; i < (int)ARRAY_SIZE(choices); i++) {
                print_center_x(stdscr, i + 12, -4, "%d. %s.", i + 1,
                               choices[i]);
        }
        refresh();
}

void
print_center_x(WINDOW *win, int line, int x_offset, const char *str, ...)
{
        char    buf[256];
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
print_scores(void)
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
