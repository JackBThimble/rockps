#ifndef MENUS_H
#define MENUS_H
#include <ncurses.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD         4

extern int player_score;
extern int cpu_score;
extern int rounds_played;

void
init_curses(void);

void
print_main_menu(void);

void
print_center_x(WINDOW *win, int line, int x_offset, const char *str, ...);

void
print_scores(void);
#endif  // MENUS_H
