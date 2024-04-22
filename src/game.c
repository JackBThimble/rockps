#include "game.h"

#include "print.h"

int player_score  = 0;
int cpu_score     = 0;
int rounds_played = 0;

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
                        pause_for_keyin();
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0,
                                       "PAPER covers ROCK");
                        print_center_x(stdscr, line, 0, "YOU WIN!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
                        player_score++;
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "ROCK breaks SCISSORS");
                        print_center_x(stdscr, line, 0, "YOU LOSE!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
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
                        pause_for_keyin();
                        cpu_score++;
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0, "PAPER vs PAPER");
                        print_center_x(stdscr, line, 0, "You tied.");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS cut PAPER");
                        print_center_x(stdscr, line, 0, "YOU WIN!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
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
                        pause_for_keyin();
                        player_score++;
                        break;
                case 2:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS cut PAPER");
                        print_center_x(stdscr, line, 0, "YOU LOSE!!!");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
                        cpu_score++;
                        break;
                case 3:
                        print_center_x(stdscr, line - 4, 0,
                                       "SCISSORS vs SCISSORS");
                        print_center_x(stdscr, line, 0, "You tied.");
                        print_center_x(stdscr, line + 1, 0,
                                       "Press any key to continue...");
                        refresh();
                        pause_for_keyin();
                        break;
                default:
                        break;
                }
                break;
        default:
                break;
        }
}
