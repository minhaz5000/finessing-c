#include <ncurses.h>
#include "library.h"

int main(void)
{
    initscr();
    start_color();
    color_initialize_all(); // just all the system colors

    cursor_go_whooosh();
    bkgd(COLOR_PAIR(_background_));

    Save userdata = login();
    int current_menu = -2; // For main menu
    for (;;)
    {
        int selected_quiz = menu_control(userdata, current_menu);
        if (selected_quiz > 100)
        {
            break;
        }
        int q_count;
        container **repo = repo_load(selected_quiz, &q_count);
        int score = 0;
        for (int i = 0; i < 15; ++i)
        {
            int temp = score_from_question(*(repo[i]), i + 1);

            if (temp < 10)
                score += temp;
            else
            {
                break;
            }
        }

        score_ascii_art(score);

        if (score > PASS_MARKS)
        {
            update_userdata_from_menucode(&userdata, selected_quiz);
        }
        current_menu = selected_quiz / 10 - 1;
        repo_destroy(repo, q_count);
    }

    update_savefile(&userdata);

    refresh();

    endwin();

    return 0;
}