#ifndef MENUS_H
#define MENUS_H
#include <ncurses.h>
#include <sys/types.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD         4

extern u_int16_t player_score;
extern u_int16_t cpu_score;
extern u_int16_t rounds_played;

void
init_curses(void);

void
pause_for_keyin(void);

void
print_main_menu(void);

void
print_center_x(WINDOW *win, int line, int x_offset, const char *str, ...);

void
print_scores(void);
#endif  // MENUS_H
