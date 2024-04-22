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

#include "game.h"
#include "print.h"
#include "random.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD         4

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
                        print_scores();
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
