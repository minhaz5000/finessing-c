#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "library.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int quiz_tier_menu(Save userdat)
{

    // bool values that determine the available tiers for quiz
    bool flag[3] = {false, false, false};

    int sum = 0;

    for (int i = 0; i < 15; i++)
    {
        sum += userdat.progress_flag[i];
    }

    flag[0] = true;

    if (sum >= 6) // f
        flag[1] = true;
    if (sum >= 10)
        flag[2] = true;

    // actual number for quiz
    int menu_selectable = flag[0] + flag[1] + flag[2];

    // le menue
    char menu[3][16] = {"Beginner",
                        "Intermediate",
                        "Advanced"};

    // menu y abscissa

    int y = 19;

    ////////////////////////////////////////////////////////
    //                                                    //
    //              initailize the menu                   //
    //                                                    //
    ////////////////////////////////////////////////////////

    // first menu object highlighted as current pos
    attrset(COLOR_PAIR(_menu_current_) | A_BOLD);
    center_addstr(y + 2 * 0, menu[0]);
    attroff(A_BOLD);
    attrset(COLOR_PAIR(_system_default_));

    for (int i = 1; i < 3; i++)
    {

        if (flag[i]) // true means that it is available
        {
            attrset(COLOR_PAIR(_menu_default_) | A_BOLD);
        }
        else // we make it a dark hue and will not be touched by user at least for now
        {
            attrset(COLOR_PAIR(_menu_dark_) | A_BOLD);
        }

        center_addstr(y + 2 * i, menu[i]);

        // addstr(menu[i]);

        attroff(A_BOLD);
        attrset(COLOR_PAIR(_system_default_));
    }

    int ch;

    int i = 0, selected = 0;
    flushinp();
    // flushes out extra text

    // selected is the quiz user will choose to do

    while (!selected)
    {
        // menu markers are the quiz tags that are available to iterate via arrow keys
        bool menu_markers[menu_selectable];

        // initialize all to zero
        for (int K = 0; K < menu_selectable; K++)
        {
            menu_markers[K] = false;
        }

        ch = wgetch(stdscr);

        if (ch == KEY_UP)
        {
            i--;
        }
        else if (ch == KEY_DOWN)
        {
            i++;
        }
        else if (ch == '\n')
        {
            selected = i;
            break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            selected = -2;
        }

        // bound checking
        if (i < 0)
            i = menu_selectable - 1;
        else if (i >= menu_selectable)
            i = 0;

        menu_markers[i] = true;

        for (int K = 0; K < menu_selectable; K++)
        {

            if (menu_markers[K]) // value true means it's where the cursor is currently
            {
                attrset(COLOR_PAIR(_menu_current_) | A_BOLD);
            }
            else
            {
                attrset(COLOR_PAIR(_menu_default_) | A_BOLD | A_DIM);
            }
            center_addstr(y + 2 * K, menu[K]);

            // all extra attributes turned off and we restore system to default theme
            attroff(A_BOLD);
            attroff(A_DIM);
            attrset(COLOR_PAIR(_system_default_));
            refresh();
        }
    }

    napms(200);
    refresh();

    return selected;
}
//----------------------------------------------------------------

int beginner_menu(Save userdat)
{

    // bool values that determine the current mastery of topics of the quiz
    bool flag[6] = {false, false, false, false, false, false};

    for (int i = 0; i < 6; i++)
    {
        flag[i] = userdat.progress_flag[i];
    }

    // number of topics for this quiz
    int menu_selectable = 6;

    // ze topiczzz
    char menu[6][50] = {" Datatypes ",                      // 0
                        " Declaration and Initialization ", // 1
                        " Input/Output ",                   // 2
                        " Arrays ",                         // 3
                        " Iteration ",                      // 4
                        " Control Statements "};            // 5

    int y = 19;

    ////////////////////////////////////////////////////////
    //                                                    //
    //              initailize the menu                   //
    //                                                    //
    ////////////////////////////////////////////////////////

    if (flag[0]) // value true means it is mastered and colored green
        attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
    else // needs to be mastered and colored red
        attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);

    center_addstr(y + 2 * 0, menu[0]);

    for (int K = 1; K < menu_selectable; K++)
    {

        if (flag[K]) // value true means it is mastered and colored green
            attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
        else // needs to be mastered and colored red
            attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);

        center_addstr(y + 2 * K, menu[K]);

        // all extra attributes turned off and we restore system to default theme
        attroff(A_BOLD);
        attrset(COLOR_PAIR(_system_default_));
    }

    int ch;

    int i = 0, selected = 0;

    flushinp();
    // flushes out extra text

    // selected is the quiz user will choose to do

    while (!selected)
    {
        // menu markers are the quiz tags that are available to iterate via arrow keys
        bool menu_markers[menu_selectable];

        // initialize all to zero
        for (int K = 0; K < menu_selectable; K++)
        {
            menu_markers[K] = false;
        }

        ch = wgetch(stdscr);

        if (ch == KEY_UP)
        {
            i--;
        }
        else if (ch == KEY_DOWN)
        {
            i++;
        }
        else if (ch == '\n')
        {
            selected = i + 1;
            // break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            selected = -11;
            // break;
        }

        // bound checking and cycling from bottom back to top
        if (i < 0)
            i = menu_selectable - 1;
        else if (i >= menu_selectable)
            i = 0;

        menu_markers[i] = true;

        for (int K = 0; K < menu_selectable; K++)
        {

            if (menu_markers[K]) // value true means it's where the cursor is currently
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);
            }
            else
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);
            }
            center_addstr(y + 2 * K, menu[K]);

            // all extra attributes turned off and we restore system to default theme
            attroff(A_BOLD);
            attrset(COLOR_PAIR(_system_default_));
        }
        refresh();
    }

    // printw("BROKEN OUT OF LOOP BY PRESSING ENTER\n");

    refresh();

    selected = 10 + selected;

    return selected;
}

int intermediate_menu(Save userdat)
{

    // bool values that determine the current mastery of topics of the quiz
    bool flag[4] = {false, false, false, false};
    ;

    // number of topics for this quiz
    int menu_selectable = 4;

    for (int i = 0; i < menu_selectable; i++)
    {
        flag[i] = userdat.progress_flag[6 + i];
    }

    // ze topiczzz
    char menu[4][50] = {" Strings ",                             // 6
                        " Pointers ",                            // 7
                        " Functions ",                           // 8
                        " Structures Unions and Enumerations "}; // 9

    int y = 19;

    ////////////////////////////////////////////////////////
    //                                                    //
    //              initailize the menu                   //
    //                                                    //
    ////////////////////////////////////////////////////////

    if (flag[0]) // value true means it is mastered and colored green
        attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
    else // needs to be mastered and colored red
        attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);

    center_addstr(y + 2 * 0, menu[0]);

    for (int K = 1; K < menu_selectable; K++)
    {

        if (flag[K]) // value true means it is mastered and colored green
            attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
        else // needs to be mastered and colored red
            attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);

        center_addstr(y + 2 * K, menu[K]);

        // all extra attributes turned off and we restore system to default theme
        attroff(A_BOLD);
        attrset(COLOR_PAIR(_system_default_));
    }

    int ch;

    int i = 0, selected = 0;

    // selected is the quiz user will choose to do
    flushinp();
    // flushes out extra text

    while (!selected)
    {
        // menu markers are the quiz tags that are available to iterate via arrow keys
        bool menu_markers[menu_selectable];

        // initialize all to zero
        for (int K = 0; K < menu_selectable; K++)
        {
            menu_markers[K] = false;
        }

        ch = wgetch(stdscr);

        if (ch == KEY_UP)
        {
            i--;
        }
        else if (ch == KEY_DOWN)
        {
            i++;
        }
        else if (ch == '\n')
        {
            selected = i + 1;
            // break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            selected = -21;
            // return selected;
        }

        // bound checking and cycling from bottom back to top
        if (i < 0)
            i = menu_selectable - 1;
        else if (i >= menu_selectable)
            i = 0;

        menu_markers[i] = true;

        for (int K = 0; K < menu_selectable; K++)
        {

            if (menu_markers[K]) // value true means it's where the cursor is currently
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);
            }
            else
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);
            }
            center_addstr(y + 2 * K, menu[K]);

            // all extra attributes turned off and we restore system to default theme
            attroff(A_BOLD);
            attrset(COLOR_PAIR(_system_default_));
        }
        refresh();
    }

    // printw("BROKEN OUT OF LOOP BY PRESSING ENTER\n");

    refresh();

    selected = 20 + selected;

    return selected;
}

int advanced_menu(Save userdat)
{

    // napms(50);

    // bool values that determine the current mastery of topics of the quiz
    bool flag[5] = {false, false, false, false, false};
    ;

    // number of topics for this quiz
    int menu_selectable = 5;

    for (int i = 0; i < menu_selectable; i++)
    {
        flag[i] = userdat.progress_flag[10 + i];
    }

    // ze topiczzz
    char menu[5][50] = {" File Processing ",        // 10
                        " Preprocessor ",           // 11
                        " Memory Allocation ",      // 12
                        " Command Line Arguments ", // 13
                        " C Standard Library "};    // 14
    /*
    "File Processing",
    "Preprocessor",
    "Memory Allocation",
    "Command Line Arguments",
    "C Standard Library"
    */

    int y = 19;

    ////////////////////////////////////////////////////////
    //                                                    //
    //              initailize the menu                   //
    //                                                    //
    ////////////////////////////////////////////////////////

    if (flag[0]) // value true means it is mastered and colored green
        attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
    else // needs to be mastered and colored red
        attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);

    center_addstr(y + 2 * 0, menu[0]);

    for (int K = 1; K < menu_selectable; K++)
    {

        if (flag[K]) // value true means it is mastered and colored green
            attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
        else // needs to be mastered and colored red
            attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);

        center_addstr(y + 2 * K, menu[K]);

        // all extra attributes turned off and we restore system to default theme
        attroff(A_BOLD);
        attrset(COLOR_PAIR(_system_default_));
    }

    int ch;

    int i = 0, selected = 0;

    // selected is the quiz user will choose to do
    flushinp();
    // flushes out extra text

    while (!selected)
    {
        // menu markers are the quiz tags that are available to iterate via arrow keys
        bool menu_markers[menu_selectable];

        // initialize all to zero
        for (int K = 0; K < menu_selectable; K++)
        {
            menu_markers[K] = false;
        }

        ch = wgetch(stdscr);

        if (ch == KEY_UP)
        {
            i--;
        }
        else if (ch == KEY_DOWN)
        {
            i++;
        }
        else if (ch == '\n')
        {
            selected = i + 1;
            // break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            selected = -31;
            // return selected;
        }

        // bound checking and cycling from bottom back to top
        if (i < 0)
            i = menu_selectable - 1;
        else if (i >= menu_selectable)
            i = 0;

        menu_markers[i] = true;

        for (int K = 0; K < menu_selectable; K++)
        {

            if (menu_markers[K]) // value true means it's where the cursor is currently
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);
            }
            else
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);
            }
            center_addstr(y + 2 * K, menu[K]);

            // all extra attributes turned off and we restore system to default theme
            attroff(A_BOLD);
            attrset(COLOR_PAIR(_system_default_));
        }
        refresh();
    }

    // printw("BROKEN OUT OF LOOP BY PRESSING ENTER\n");

    refresh();

    selected = 30 + selected;

    return selected;
}

int menu_control(Save userdat, int menucode)
{

    while (1)
    {
        if (menucode == -2) // -2 is for load menu
        {
            clear();
            attrset(COLOR_PAIR(_system_default_));
            logo();
            refresh();
            menucode = first_menu();
        }

        if (menucode == -1) // -1 is for quiz menu
        {
            clear();
            attrset(COLOR_PAIR(_system_default_));
            logo();
            refresh();
            menucode = quiz_tier_menu(userdat);
        }
        else if (menucode == 0) // 0 is for beginner topics menu
        {
            clear();
            attrset(COLOR_PAIR(_system_default_));
            logo();
            refresh();
            menucode = beginner_menu(userdat);
        }
        else if (menucode == 1) // 1 is for intermediate menu
        {
            clear();
            attrset(COLOR_PAIR(_system_default_));
            logo();
            refresh();
            menucode = intermediate_menu(userdat);
        }
        else if (menucode == 2) // 2 is for advanced menu
        {
            clear();
            attrset(COLOR_PAIR(_system_default_));
            logo();
            refresh();
            menucode = advanced_menu(userdat);
        }
        else if (menucode > 10)
        {
            break;
        }
    }

    return menucode;
}

void logo() // logo takes up 14 y-axis spaces with two empty at the bottom
{

    printw("\n");

    print_full_row(0, '*', BLACK_txt_PURPLE_bg);
    // print_full_row_for_logo(0, '*', BLACK_txt_PURPLE_bg);

    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg));

    char finessing_logo_str[8][61] = {
        "  __  _                         _                     _____ ",
        " / _|(_)                       (_)                   / ____|",
        "| |_  _  _ __    ___  ___  ___  _  _ __    __ _     | |     ",
        "|  _|| || '_ \\  / _ \\/ __|/ __|| || '_ \\  / _` |    | |     ",
        "| |  | || | | ||  __/\\__ \\\\__ \\| || | | || (_| |    | |____ ",
        "|_|  |_||_| |_| \\___||___/|___/|_||_| |_| \\__  |     \\_____|",
        "                                           __/ |            ",
        "                                          |___/             "};

    int x = (COLS - 60) / 2;

    for (int i = 0; i < 8; i++)
    {
        mvaddstr(1 + i, x, finessing_logo_str[i]);
    }

    print_full_row(10, '*', BLACK_txt_PURPLE_bg);
    // print_full_row_for_logo(10, '*', BLACK_txt_PURPLE_bg);

    printw("\n"); // 11
    printw("\n"); // 12

    attrset(COLOR_PAIR(_system_default_));
}

char timer(int second)
{

    printw("\n");

    // ensures that we are at beginning of line for getyx
    int x, y;
    getyx(stdscr, y, x);

    x = (COLS - 5) / 2;

    attrset(COLOR_PAIR(BLACK_txt_RED_bg));

    move(y, x);

    int ch;

    // minute:second fromat from just seconds
    int minute = second / 60;
    second = second % 60;

    nodelay(stdscr, TRUE);
    // detaches program flow from getch input

    printw("%.2d:%.2d", minute, second);
    while (1)
    {

        ch = getch();

        if (ch == _OPTION_A || ch == _OPTION_B || ch == _OPTION_C || ch == _OPTION_D || ch == QUIT_BUTTON)
        {
            break;
        }
        else if (!(minute + second))
        {
            // initialize dummy value
            ch = '!';
            break;
        }

        second--;

        if (second == -1)
        {
            minute--;
            second = 59;
        }

        printw("\b\b\b\b\b%.2d:%.2d", minute, second);
        // /b is escape char prints backspace
        // so this goes back and reprints over original text

        napms(1000);
        refresh();
    }

    flushinp();
    // flushes out extra text

    nodelay(stdscr, FALSE);
    // brings program flow to normal

    return ch;
}

// login function
Save login()
{

    clear();
    logo();
    char *str = calloc(COLS, sizeof(char));
    char *only_space = calloc(COLS, sizeof(char));

    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg));

    int erase = COLS / 4;

    if (COLS < 20)
        erase = 0;

    print_rectang(COLS / 2 - erase - 4, 16, COLS / 2 + erase + 4, 28, BLACK_txt_PURPLE_bg, ' ');

    print_rectang(COLS / 2 - erase, 20, COLS / 2 + erase, 24, BLACK_txt_PURPLE_bg, ' ');
    int ch;
    int i = 0;

    move(22, COLS / 2);

    center_addstr(18, "~ ENTER YOUR USER ID ~");

    attrset(COLOR_PAIR(RED_txt_BLACK_bg));

    for (;;)
    {
        ch = getch();
        if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT || ch == KEY_F(1) || ch == KEY_F(2) || ch == KEY_F(3) || ch == KEY_F(4) || ch == KEY_F(5) || ch == KEY_F(6) || ch == KEY_F(7) || ch == KEY_F(8) || ch == KEY_F(9) || ch == KEY_F(10) || ch == KEY_F(11) || ch == KEY_F(12))
        {
            continue;
        }
        else if (ch == '\n')
        {
            if (i == 0)
            {
                delayed_center_addstr(26, "Hey, can I get a String ?", 50);
                napms(1500);
                center_addstr(26, "                          ");

                continue;
            }
            break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            if (i == 0)
                continue;
            else
            {
                center_addstr(22, only_space);
                refresh();
                i--;
                str[i] = '\0';
            }
        }
        else if (i > COLS / 2 - 2)
        {
            // move(26, x);
            delayed_center_addstr(26, "Sometimes it's best to not LITERALLY think out of the box", 50);
            napms(1500);
            center_addstr(26, "                                                          ");
            flushinp();
            continue;
        }
        else
        {
            only_space[i] = ' ';
            str[i] = ch;
            i++;
        }
        center_addstr(22, str);
        refresh();
    }

    Save userdata = load_savefile(str);
    free(only_space);
    free(str);
    return userdata;
}

// load savefile if exists or initialize new savefile
Save load_savefile(char *FILEPATH)
{
    char name[32];
    sprintf(name, "save/%s.sav", FILEPATH);
    FILE *fp = fopen(name, "rb");
    Save save_file;
    if (!fp)
    {
        // check for save directory
        DIR *d;
        if ((d = opendir("save")) == NULL)
        {
            mkdir("save", 0777);    // create save dir if it doesn't exist
        }
        else
            closedir(d);

        FILE *fp = fopen(name, "wb");
        strcpy(save_file.id, FILEPATH);
        for (int i = 0; i < 15; ++i)
        {
            save_file.progress_flag[i] = 0;
        }
        if (fwrite(&save_file, sizeof(Save), 1, fp) == 0)
        {
            fprintf(stderr, "Failed to Load Save File....\n");
            exit(EXIT_FAILURE);
        }
        fclose(fp);
        attrset(COLOR_PAIR(RED_txt_BLACK_bg));
        char text[] = "New, huh? Welcome aboard";
        int len = strlen(text);
        int x = (COLS - len) / 2;
        move(26, x);
        int t = strlen(text);
        for (int i = 0; i < t; i++)
        {
            printw("%c", text[i]);
            refresh();
            napms(50);
        }
        napms(500);
    }
    else
    {
        attrset(COLOR_PAIR(RED_txt_BLACK_bg));
        char text[] = "WELCOME BACK :D";
        int len = strlen(text);
        int x = (COLS - len) / 2;
        move(26, x);
        int t = strlen(text);
        for (int i = 0; i < t; i++)
        {
            printw("%c", text[i]);
            refresh();
            napms(50);
        }
        napms(500);
        fread(&save_file, sizeof(Save), 1, fp);
        fclose(fp);
    }

    return save_file;
}

// update save from progress
int update_savefile(Save *save_file)
{
    char name[64];
    sprintf(name, "save/%s.sav", save_file->id);
    FILE *fp = fopen(name, "wb");
    if (!fp)
    {
        fprintf(stderr, "Error in accessing savefile\n");
        return -1;
    }
    if (fwrite(save_file, sizeof(Save), 1, fp) == 0)
    {
        fprintf(stderr, "Error in updating savefile\n");
        return -1;
    }
    fclose(fp);
    return 0;
}

void center_addstr(int y, char *text)
{
    int len = strlen(text);
    int x = (COLS - len) / 2;
    mvaddstr(y, x, text);
    refresh();
}

void delayed_center_addstr(int y, char *text, int time)
{
    int len = strlen(text);
    int x = (COLS - len) / 2;
    move(y, x);
    int t = strlen(text);
    for (int i = 0; i < t; i++)
    {
        printw("%c", text[i]);
        refresh();
        napms(time);
    }

    refresh();
}

void print_grid(int y)
{
    move(y, 0);

    int j = 0;
    for (int i = 1; i < COLS; i++)
    {
        printw("%d", j);
        j++;
        if (i % 10 == 0)
            j = 0;
    }
}

void print_full_row(int y, char ch, int color_pair) // takes window size and prints an entire row with a char;
{
    move(y, 1);
    attrset(COLOR_PAIR(color_pair));

    for (int i = 0; i < COLS - 2; i++)
    {
        printw("%c", ch);
    }
}

void cursor_go_whooosh()
{

    curs_set(0);
    // hides cursor so no more flickering
    // HAIL STACKOVERFLOW

    noecho();
    // prevents extra char from our buffer popping up here and there

    keypad(stdscr, TRUE);
    // Allows to take input from extra keyboard keys like up and down
}

void cursor_comebaccc()
{
    // basically reverses everything cursor_go_whooosh func does

    echo();

    curs_set(1);

    keypad(stdscr, FALSE);
}

void print_rectang(int start_x, int start_y, int end_x, int end_y, int color_pair, char ch)
{

    attrset(COLOR_PAIR(color_pair));

    move(start_y, start_x);
    for (int i = start_x; i <= end_x; i++)
    {
        printw("%c", ch);
    }

    move(end_y, start_x);
    for (int i = start_x; i <= end_x; i++)
    {
        printw("%c", ch);
    }

    for (int i = 0; i < end_y - start_y; i++)
    {
        move(start_y + i, start_x);
        printw("%c", ch);
    }

    for (int i = 0; i < end_y - start_y; i++)
    {
        move(start_y + i, end_x);
        printw("%c", ch);
    }

    refresh();
}

void print_in_sub_window(int start_x, int start_y, int end_x, int end_y, int color_pair, char *str, int naptime)
{
    (void)end_y;
    int current_x, current_y;
    attrset(COLOR_PAIR(color_pair));
    move(start_y, start_x);
    int t = strlen(str);
    for (int K = 0; K < t; K++)
    {
        getyx(stdscr, current_y, current_x);
        if (current_x + 1 == end_x)
            move(current_y + 1, start_x);
        if (str[K] == '\n')
            move(current_y + 1, start_x);
        else
            printw("%c", str[K]);
        napms(naptime);
        refresh();
    }
}

void naprefresh(int time)
{
    napms(time);
    refresh();
}

int score_from_question(container question, int i)
{
    int opt_naptime = 0;

    int wait_time =10;

    int row, col;
    clear();

    int max = 0;
    attrset(COLOR_PAIR(_back_to_black_));

    for (int i = 0; i < 4; i++)
    {
        clear();
        int len = strlen(question.opt[i]);
        printw("%s", question.opt[i]);
        getyx(stdscr, row, col);

        int val = (len / (COLS - 3)) + 1;
        if (row > val && row > max)
            max = row;
        else if (row < val && val > max)
            max = val;
    }
    max++;

    clear();

    print_full_row(1, '-', _option_ABCD_);

    attrset(COLOR_PAIR(_option_braces_));

    int len, temp;

    if (i < 10)
    {
        temp = strlen(" Question 0 ");
        len = (COLS - temp) / 2;
    }
    else
    {
        temp = strlen(" Question 00 ");
        len = (COLS - temp) / 2;
    }

    move(3, len);
    printw(" Question %d \n\n", i);

    getyx(stdscr, row, col);

    print_in_sub_window(1, row, COLS, 0, ORANGE_txt_BLACK_bg, question.question, wait_time);
    // printw("this row 1");

    printw("\n\n");
    // printw("this row 2");

    getyx(stdscr, row, col);
    print_in_sub_window(6, row, COLS, 0, DEEP_BLUE_txt_BLACK_bg, question.code, wait_time);
    // printw("%s\n", question.code);

    if (strcmp(question.code, "\0") != 0)
    {
        printw("\n\n");
    }
    getyx(stdscr, row, col);

    printw("\n");
    getyx(stdscr, row, col);

    print_in_sub_window((COLS / 2) + 2, row + 1, COLS - 2, row + max, ORANGE_txt_BLACK_bg, question.opt[1], opt_naptime);
    print_in_sub_window(col + 1, row + 1, (COLS / 2) - 2, row + max, ORANGE_txt_BLACK_bg, question.opt[0], opt_naptime);

    print_rectang(col, row, (COLS / 2) - 1, row + max + 1, _option_braces_, ' ');
    naprefresh(wait_time);
    print_rectang((COLS / 2) + 1, row, COLS - 1, row + max + 1, _option_braces_, ' ');
    naprefresh(wait_time);

    attrset(COLOR_PAIR(_option_ABCD_));
    move(row, ((COLS / 2) - 11) / 2);

    printw(" OPTION A ");
    naprefresh(wait_time);
    move(row, COLS / 2 + ((COLS - 1 - (COLS / 2) + 1) - 10) / 2);
    printw(" OPTION B ");
    naprefresh(wait_time);
    move(row + max + 2, 0);
    //"OPTION A"

    // getch();
    refresh();

    getyx(stdscr, row, col);
    move(row + 2, 0);
    getyx(stdscr, row, col);
    print_in_sub_window(col + 1, row + 1, (COLS / 2) - 2, row + max, ORANGE_txt_BLACK_bg, question.opt[2], opt_naptime);
    print_in_sub_window((COLS / 2) + 2, row + 1, COLS - 2, row + max, ORANGE_txt_BLACK_bg, question.opt[3], opt_naptime);

    print_rectang(col, row, (COLS / 2) - 1, row + max + 1, _option_braces_, ' ');
    naprefresh(wait_time);
    print_rectang((COLS / 2) + 1, row, COLS - 1, row + max + 1, _option_braces_, ' ');
    naprefresh(wait_time);

    attrset(COLOR_PAIR(_option_ABCD_));
    move(row, ((COLS / 2) - 11) / 2);
    printw(" OPTION C ");
    naprefresh(wait_time);
    move(row, COLS / 2 + ((COLS - 1 - (COLS / 2) + 1) - 10) / 2);
    printw(" OPTION D ");
    naprefresh(wait_time);
    move(row + max + 2, 0);
    printw("\n\n\n");
    attrset(COLOR_PAIR(ORANGE_txt_BLACK_bg));
    getyx(stdscr, row, col);
    center_addstr(row, " Time ");
    print_full_row(row + 6, '-', _option_ABCD_);

    move(row + 1, 0);
    int ch = timer(question.timer);

    printw("\n");

    int retval = 0;

    if (ch == QUIT_BUTTON)
    {
        retval = 100;
    }
    else if (ch == _OPTION_A)
    {
        retval = !strcmp(question.ans, question.opt[0]);
    }
    else if (ch == _OPTION_B)
    {
        retval = !strcmp(question.ans, question.opt[1]);
    }
    else if (ch == _OPTION_C)
    {
        retval = !strcmp(question.ans, question.opt[2]);
    }
    else if (ch == _OPTION_D)
    {
        retval = !strcmp(question.ans, question.opt[3]);
    }

    attrset(COLOR_PAIR(RED_txt_BLACK_bg));
    int ans_wait_time = 50;

    if (retval == 1)
    {
        delayed_center_addstr(row + 4, "That is correct", ans_wait_time);
        napms(1500);
    }
    else if (ch == '!')
    {
        char str[500] = {"Answer: "};
        strcat(str, question.ans);
        delayed_center_addstr(row + 4, str, ans_wait_time);
        napms(2000);
    }
    else if (retval == 0)
    {
        char str[500] = {"Wrong, correct ans: "};
        strcat(str, question.ans);
        delayed_center_addstr(row + 4, str, ans_wait_time);
        napms(2000);
    }
    flushinp();
    delayed_center_addstr(LINES - 3, "Press any key to continue", 10);
    getch();
    flushinp();
    return retval;
}

// Initialize all color in ncurses
void color_initialize_all()
{
    init_pair(_background_, COLOR_BLUE, COLOR_BLACK);

    // main menu
    init_pair(_menu_dark_, 231, COLOR_BLACK);
    // init_pair(_menu_current_, COLOR_RED, COLOR_BLACK);
    init_pair(_menu_current_, COLOR_RED, 235);
    init_pair(_menu_default_, COLOR_BLUE, COLOR_BLACK);

    init_pair(_system_default_, COLOR_WHITE, COLOR_BLACK);

    // logo
    init_pair(PURPLE_txt_BLACK_bg, 93, COLOR_BLACK);
    init_pair(BLACK_txt_PURPLE_bg, COLOR_BLACK, 93);

    // topics menu
    init_pair(_topic_noob_, 161, COLOR_BLACK);
    init_pair(_topic_current_noob_, 161, 235);
    init_pair(_topic_mastered_, 47, COLOR_BLACK);
    init_pair(_topic_current_mastered_, 47, 235);

    init_pair(RED_txt_BLACK_bg, 196, COLOR_BLACK);

    // timer color
    init_pair(BLACK_txt_RED_bg, COLOR_BLACK, 196);

    // option and quiz
    init_pair(_option_braces_, COLOR_BLACK, 9);
    init_pair(ORANGE_txt_BLACK_bg, 208, COLOR_BLACK);
    init_pair(_option_ABCD_, 196, 11);
    // init_pair(ORANGE_txt_BLACK_bg, 208, COLOR_BLACK);
    init_pair(DEEP_BLUE_txt_BLACK_bg, 51, COLOR_BLACK);
    init_pair(_about_composition_part_, 155, COLOR_BLACK);
    init_pair(_back_to_black_, COLOR_BLACK, COLOR_BLACK);
}

// swap two elements in array
// uses memcpy
void swap(char *base, size_t size, int n, int m, char *temp)
{
    char *a = base + size * n;
    char *b = base + size * m;
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

// shuffle array using fisher-yates shuffling algorithm
void shuffle(void *base, size_t nmemb, size_t size)
{
    srand(time(NULL));
    char *temp = malloc(sizeof(char) * size);   // used as medium for swapping
    for (int i = nmemb - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(base, size, i, j, temp);
    }
    free(temp);
}

// create container from given character string
container *create_container(char *s)
{
    char *p = s;
    container *add = malloc(sizeof(container));
    char *id = token_input(p, ID_FLAG_BEGIN, ID_FLAG_END);
    // 8 digit id of which, first 3 digit = unique id, 1 digit type, 1 digit = option count, 3 digit timer
    sscanf(id, "%3d%1d%1d%3d", &add->id, &add->type, &add->opt_count, &add->timer);
    int count = add->opt_count;
    p = strstr(p, ID_FLAG_END);
    free(id);
    add->question = token_input(p, QUESTION_FLAG_BEGIN, QUESTION_FLAG_END);
    p = strstr(p, QUESTION_FLAG_END);
    add->code = token_input(p, CODE_FLAG_BEGIN, CODE_FLAG_END);
    p = strstr(p, CODE_FLAG_END);
    for (int i = 0; i < count && i < 4; ++i) // option input, Maximum 4 options
    {
        add->opt[i] = token_input(p, OPTION_FLAG_BEGIN, OPTION_FLAG_END);
        p = strstr(p, OPTION_FLAG_END) + strlen(OPTION_FLAG_END);
    }
    add->ans = token_input(p, ANS_FLAG_BEGIN, ANS_FLAG_END);
    return add;
}

// tokenizer for extracting values in between begin and end flags
char *token_input(const char *input, const char *flag_begin, const char *flag_end)
{
    char *begin, *end;
    begin = strstr(input, flag_begin);
    if (begin == NULL)
    {
        char *output = strdup("\0");
        return output;
    }
    begin += strlen(flag_begin);
    while (*begin == '\n' || *begin == ' ')
        ++begin;
    end = strstr(input, flag_end) - 1;
    if (end < begin)
    {
        char *output = strdup("\0");
        return output;
    }
    int len = end - begin + 1;
    char *output = malloc((len + 1) * sizeof(char));
    strncpy(output, begin, len);
    // for (int i = 0; i < len; ++i)
    //     output[i] = begin[i];
    output[len] = '\0';
    return output;
}

// Initialize data to a container pointer array
int init_data(const char *FILEPATH, container **array)
{
    // buffer text file
    char *buffer = NULL;
    size_t buffer_length;
    FILE *fp = fopen(FILEPATH, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load file %s\n", FILEPATH);
        return -1;
    }
    if (fseek(fp, 0L, SEEK_END) == 0)
        buffer_length = ftell(fp);  // get buffer character count
    else
        return -1;

    buffer = malloc(sizeof(char) * (buffer_length + 1));
    rewind(fp);
    fread(buffer, sizeof(char), buffer_length, fp); // read all character to buffer
    fclose(fp);
    decrypt(buffer, buffer_length);     // decrypt buffer
    int container_read = 0;     // keep count of the containers/ questions read from buffer
    container *element;
    char *itr = strstr(buffer, BEGIN_FLAG); // iterate to first BEGIN_FLAG
    while (itr)
    {
        element = create_container(itr); // create container
        array[container_read++] = element;  // save it in array
        itr = strstr(itr, END_FLAG); // iterate to END_FLAG
        itr = strstr(itr, BEGIN_FLAG); // iterate TO next BEGIN_FLAG
    }
    free(buffer);
    return container_read;
}

// Loads entire repository according to given topic.
container **repo_load(int topic, int *count)
{
    char name[64];
    sprintf(name, "data/%d.txt", topic);
    container **arr = malloc(MAX_CONTAINER_COUNT * sizeof(container *));
    int x = init_data(name, arr);
    *count = x; // set count to number of containers read
    // Shuffle the array
    shuffle(arr, x, sizeof(container *));
    // Shuffle for Options. Enabled only for type 1 in id
    for (int i = 0; i < x; ++i)
    {
        if (arr[i]->type)
        {
            char **p = arr[i]->opt;
            shuffle(p, 4, sizeof(char *));
        }
    }
    return arr;
}

// free all allocated memory in the given repo
void repo_destroy(container **arr, int count)
{
    container *itr;
    for (int i = 0; i < count; ++i)
    {
        itr = arr[i];
        free(itr->question);
        free(itr->ans);
        free(itr->opt[0]);
        free(itr->opt[1]);
        free(itr->opt[2]);
        free(itr->opt[3]);
        free(itr->code);
        free(itr);
    }
    free(arr);
}

void update_userdata_from_menucode(Save *userdata, int menucode)
{
    // Changed from switch-case to if else
    // see topics enum for values of Datatypes, Strings ... etc

    if (menucode >= Datatypes && menucode <= Control_Statements)
        userdata->progress_flag[menucode % 10 - 1] = true;
    else if (menucode >= Strings && menucode <= Structures)
        userdata->progress_flag[menucode % 20 + 5] = true;
    else if (menucode >= File && menucode <= C_Standard_Library)
        userdata->progress_flag[menucode % 30 + 9] = true;
    else
    {
        fprintf(stderr, "menucode error, out of bound.\n");
        return;
    }

/*    switch (menucode)
    {
        case Datatypes:
            userdata->progress_flag[0] = true;
            break;
        case Declaration_Init:
            userdata->progress_flag[1] = true;
            break;
        case Input_Output:
            userdata->progress_flag[2] = true;
            break;
        case Array:
            userdata->progress_flag[3] = true;
            break;
        case Iteration:
            userdata->progress_flag[4] = true;
            break;
        case Control_Statements:
            userdata->progress_flag[5] = true;
            break;
        case Strings:
            userdata->progress_flag[6] = true;
            break;
        case Pointers:
            userdata->progress_flag[7] = true;
            break;
        case Functions:
            userdata->progress_flag[8] = true;
            break;
        case Structures:
            userdata->progress_flag[9] = true;
            break;
        case File:
            userdata->progress_flag[10] = true;
            break;
        case Preprocessor:
            userdata->progress_flag[11] = true;
            break;
        case Memory_Allocation:
            userdata->progress_flag[12] = true;
            break;
        case Command_Line_Args:
            userdata->progress_flag[13] = true;
            break;
        case C_Standard_Library:
            userdata->progress_flag[14] = true;
            break;

        default:
        break;
    }*/
}

void demo(void)
{
    clear();
    flushinp();
    int rows, cols;
    (void) cols;    // cols unused
    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg) | A_BOLD);
    char howto_str[5][100] = {
        "__  __   ______   __     __                   ______  ______\n",
        "/\\ \\_\\ \\ /\\  __ \\ /\\ \\  _ \\ \\      _____      /\\__  _\\/\\  __ \\\n",
        " \\ \\  __ \\\\ \\ \\/\\ \\\\ \\ \\/ \".\\ \\    <_____>     \\/_/\\ \\/\\ \\ \\/\\ \\\n",
        "   \\ \\_\\ \\_\\\\ \\_____\\\\ \\__/\".~\\_\\                  \\ \\_\\ \\ \\_____\\\n",
        "   \\/_/\\/_/ \\/_____/ \\/_/   \\/_/                   \\/_/  \\/_____/" };

    for (int i = 0; i < 5; i++)
    {
        center_addstr(4 + i, howto_str[i]);
    }
    move(LINES / 4, 0);
    getyx(stdscr, rows, cols);

    print_in_sub_window(4, rows, (COLS / 2) - 1, 0, ORANGE_txt_BLACK_bg, "In Menus - \n\n\nUse UP and DOWN ARROW KEYS to move\n\nENTER to go forward\n\nBACKSPACE to go back", 50);

    move(LINES / 2, 0);
    getyx(stdscr, rows, cols);

    print_in_sub_window((COLS / 2) + 1, rows, COLS - 1, 0, DEEP_BLUE_txt_BLACK_bg, "While in a quiz-\n\n\nUse CAPITAL A B C D to answer\n\nPress Q to quit mid quiz\n\n", 50);

    attrset(COLOR_PAIR(RED_txt_BLACK_bg));

    delayed_center_addstr(LINES - 6, "Have Fun.... :D", 50);

    flushinp();
    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg) | A_BOLD);
    delayed_center_addstr(LINES - 4, "Press any KEY to go back", 20);

    getch();
    flushinp();
    clear();
}

void about(void)
{

    clear();
    int wait_time = 25;
    flushinp();
    int rows, cols;
    (void) cols;

    /*
       ____     _________      _____     __     __   ___________
      (    )    (_   __  \    / ___ \    ) )   ( (  (_____  ____)
      / /\ \      ) (__)  )  / /   \ \  ( (     ) )       ) )
     | (__) |     \    __/  ( ()   () )  ) )   ( (       ( (
     )      (     /  __  \  ( ()   () ) ( (     ) )       ) )
    /   /\   \   _) (__)  )  \ \___/ /   ) \___/ (       ( (
   /___(  )___\ (________/    \_____/    \_______/       /__\

    */
    char str[7][100] =
        {
            "      ____     _________      _____     __     __   ___________  \n",
            "     (    )    (_   __  \\    / ___ \\    ) )   ( (  (_____  ____) \n",
            "     / /\\ \\      ) (__)  )  / /   \\ \\  ( (     ) )       ) )     \n",
            "    | (__) |     \\    __/  ( ()   () )  ) )   ( (       ( (      \n",
            "    )      (     /  __  \\  ( ()   () ) ( (     ) )       ) )     \n",
            "   /   /\\   \\   _) (__)  )  \\ \\___/ /   ) \\___/ (       ( (      \n",
            "  /___(  )___\\ (________/    \\_____/    \\_______/       /__\\      " };

    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg) | A_BOLD);
    for (int i = 0; i < 7; i++)
    {
        center_addstr(2 + i, str[i]);
    }
    printw("\n\n\n\n\n\n\n\n\n");
    getyx(stdscr, rows, cols);

    attrset(COLOR_PAIR(ORANGE_txt_BLACK_bg) | A_BOLD);
    delayed_center_addstr(rows, "Finessing-C is a text based quiz system about... YOU guessed it! C programming Language.", wait_time);

    printw("\n\n\n\n\n\n\n\n");
    getyx(stdscr, rows, cols);
    int rows_for_feature = rows;

    print_in_sub_window(COLS / 4, rows, (COLS / 2) - 1, 0, _about_composition_part_,
                        "      Composition\n"
                        "\n"
                        "   Back-end made using C\n"
                        "\n"
                        "Front-end made using NCurses",
                        wait_time);
    printw("\n\n\n\n");
    getyx(stdscr, rows, cols);
    print_in_sub_window(COLS / 4 - 4, LINES / 2 + 5, (COLS / 2) - 1, 0, DEEP_BLUE_txt_BLACK_bg,
                        "                Team\n"
                        "\n\n"
                        "Minhaz - 200041227 - IUT CSE20 2nd Sem\n\n"
                        "Rizwan - 200041221 - IUT CSE20 2nd Sem\n\n"
                        "Sameer - 200041231 - IUT CSE20 2nd Sem\n\n"
                        "             Year - 2022",
                        wait_time);

    print_in_sub_window(COLS / 2 + 1, rows_for_feature, COLS - 1, 0, RED_txt_BLACK_bg,
                        "Features:\n"
                        "\n\n\n"
                        "Randomized quiz system with colorful NCurses UI.\n\n\n"
                        "Program randomly selects questions for a quiz.\n\n\n"
                        "Further shuffles options in the quiz.\n\n\n"
                        "Has a timer for each question.\n\n\n"
                        "Questions are sorted by specific topics with increasing knowledge tiers.\n\n\n"
                        "Saves user progress so that a user can continue from where they left off.\n\n\n",
                        wait_time);
    flushinp();
    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg) | A_BOLD);
    delayed_center_addstr(LINES - 4, "Press any KEY to go back", 20);
    getch();
    flushinp();
    clear();
}

int first_menu(void) // first menu after login PLAY HOWTO ABOUT and EXIT button
{

    // bool values that determine the available tiers for quiz
    bool flag[4] = {true, false, false, true};

    // actual number for quiz
    int menu_selectable = 4;

    // le menue
    char menu[4][50] = {"   PLAY   ",
                        "   How-To-Play   ",
                        "   About   ",
                        "   Exit   "};

    // menu y abscissa

    int y = 19;

    ////////////////////////////////////////////////////////
    //                                                    //
    //              initailize the menu                   //
    //                                                    //
    ////////////////////////////////////////////////////////

    if (flag[0]) // value true means it is mastered and colored green
        attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
    else // needs to be mastered and colored red
        attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);

    center_addstr(y + 2 * 0, menu[0]);

    for (int K = 1; K < menu_selectable; K++)
    {

        if (flag[K]) // value true means it is mastered and colored green
            attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
        else // needs to be mastered and colored red
            attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);

        center_addstr(y + 2 * K, menu[K]);

        // all extra attributes turned off and we restore system to default theme
        attroff(A_BOLD);
        attrset(COLOR_PAIR(_system_default_));
    }

    int ch;

    int i = 0, selected = 0;

    // selected is retvalue

    while (!selected)
    {

        logo();
        // menu markers are the tags that are available to iterate via arrow keys
        bool menu_markers[menu_selectable];

        // initialize all to zero
        for (int K = 0; K < menu_selectable; K++)
        {
            menu_markers[K] = false;
        }

        ch = wgetch(stdscr);

        if (ch == KEY_UP)
        {
            i--;
        }
        else if (ch == KEY_DOWN)
        {
            i++;
        }
        else if (ch == '\n')
        {

            if (i == 0)
            {
                selected = -1;
            }
            else if (i == 1)
            {
                demo();
            }
            else if (i == 2)
            {
                // ABOUT
                about();
            }
            else if (i == 3)
            {

                return 1000;
            }
        }

        // bound checking
        if (i < 0)
            i = menu_selectable - 1;
        else if (i >= menu_selectable)
            i = 0;

        menu_markers[i] = true;

        for (int K = 0; K < menu_selectable; K++)
        {

            if (menu_markers[K]) // value true means it's where the cursor is currently
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_current_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_current_noob_) | A_BOLD);
            }
            else
            {
                if (flag[K]) // value true means it is mastered and colored green
                    attrset(COLOR_PAIR(_topic_mastered_) | A_BOLD);
                else // needs to be mastered and colored red
                    attrset(COLOR_PAIR(_topic_noob_) | A_BOLD);
            }
            center_addstr(y + 2 * K, menu[K]);

            // all extra attributes turned off and we restore system to default theme
        }
        refresh();
    }

    // napms(200);
    refresh();

    return selected;
}

// Simple xor decryption for text.
void decrypt(char *buffer, size_t size)
{
    unsigned flag = size % 2;
    for (size_t i = 0; i < size; ++i)
    {
        buffer[i] ^= flag;
        buffer[i] ^= 'y';
    }
}

void score_ascii_art(int score)
{
    clear();

    int row, cols;
    (void) cols;

    char score_str[13][300] = {
        "                                                                                _____   \n",
        "            _____           _____           ____      ___________          _____\\    \\  \n",
        "       _____\\    \\     _____\\    \\_     ____\\_  \\__   \\          \\        /    / |    | \n",
        "      /    / \\    |   /     /|     |   /     /     \\   \\    /\\    \\      /    /  /___/| \n",
        "     |    |  /___/|  /     / /____/|  /     /\\      |   |   \\_\\    |    |    |__ |___|/ \n",
        "  ____\\    \\ |   || |     | |____|/  |     |  |     |   |      ___/     |       \\       \n",
        " /    /\\    \\|___|/ |     |  _____   |     |  |     |   |      \\  ____  |     __/ __    \n",
        "|    |/ \\    \\      |\\     \\|\\    \\  |     | /     /|  /     /\\ \\/    \\ |\\    \\  /  \\   \n",
        "|\\____\\ /____/|     | \\_____\\|    |  |\\     \\_____/ | /_____/ |\\______| | \\____\\/    |  \n",
        "| |   ||    | |     | |     /____/|  | \\_____\\   | /  |     | | |     | | |    |____/|  \n",
        " \\|___||____|/       \\|_____|    ||   \\ |    |___|/   |_____|/ \\|_____|  \\|____|   | |  \n",
        "                            |____|/    \\|____|                                 |___|/   "

    };

    char string[16][6][50] =
        {
            {"  ___        ___ __   _____  \n",
             " / _ \\      /  //_ | | ____| \n",
             "| | | |    /  /  | | | |__   \n",
             "| | | |   /  /   | | |___ \\  \n",
             "| |_| |  /  /    | |  ___) | \n",
             " \\___/  /__/     |_| |____/   "},

            {" __       ___ __   _____  \n",
             "/_ |     /  //_ | | ____| \n",
             " | |    /  /  | | | |__   \n",
             " | |   /  /   | | |___ \\  \n",
             " | |  /  /    | |  ___) | \n",
             " |_| /__/     |_| |____/   "},

            {" ___        ___ __   _____  \n",
             "|__ \\      /  //_ | | ____| \n",
             "   ) |    /  /  | | | |__   \n",
             "  / /    /  /   | | |___ \\  \n",
             " / /_   /  /    | |  ___) | \n",
             "|____| /__/     |_| |____/   "},

            {" ____        ___ __   _____  \n",
             "|___ \\      /  //_ | | ____| \n",
             "  __) |    /  /  | | | |__   \n",
             " |__ <    /  /   | | |___ \\  \n",
             " ___) |  /  /    | |  ___) | \n",
             "|____/  /__/     |_| |____/  \n"},

            {" _  _         ___ __   _____  \n",
             "| || |       /  //_ | | ____| \n",
             "| || |_     /  /  | | | |__   \n",
             "|__   _|   /  /   | | |___ \\  \n",
             "   | |    /  /    | |  ___) | \n",
             "   |_|   /__/     |_| |____/   "},

            {" _____       ___ __   _____  \n",
             "| ____|     /  //_ | | ____| \n",
             "| |__      /  /  | | | |__   \n",
             "|___ \\    /  /   | | |___ \\  \n",
             " ___) |  /  /    | |  ___) | \n",
             "|____/  /__/     |_| |____/   "},

            {"   __        ___ __   _____  \n",
             "  / /       /  //_ | | ____| \n",
             " / /_      /  /  | | | |__   \n",
             "| '_ \\    /  /   | | |___ \\  \n",
             "| (_) |  /  /    | |  ___) | \n",
             " \\___/  /__/     |_| |____/   "},

            {" ______       ___ __   _____  \n",
             "|____  |     /  //_ | | ____| \n",
             "    / /     /  /  | | | |__   \n",
             "   / /     /  /   | | |___ \\  \n",
             "  / /     /  /    | |  ___) | \n",
             " /_/     /__/     |_| |____/   "},

            {"  ___        ___ __   _____  \n",
             " / _ \\      /  //_ | | ____| \n",
             "| (_) |    /  /  | | | |__   \n",
             " > _ <    /  /   | | |___ \\  \n",
             "| (_) |  /  /    | |  ___) | \n",
             " \\___/  /__/     |_| |____/   "},

            {"  ___        ___ __   _____  \n",
             " / _ \\      /  //_ | | ____| \n",
             "| (_) |    /  /  | | | |__   \n",
             " \\__  |   /  /   | | |___ \\  \n",
             "   / /   /  /    | |  ___) | \n",
             "  /_/   /__/     |_| |____/   "},

            {" __    ___        ___ __   _____  \n",
             "/_ |  / _ \\      /  //_ | | ____| \n",
             " | | | | | |    /  /  | | | |__   \n",
             " | | | | | |   /  /   | | |___ \\  \n",
             " | | | |_| |  /  /    | |  ___) | \n",
             " |_|  \\___/  /__/     |_| |____/   "},

            {" __   __       ___ __   _____  \n",
             "/_ | /_ |     /  //_ | | ____| \n",
             " | |  | |    /  /  | | | |__   \n",
             " | |  | |   /  /   | | |___ \\  \n",
             " | |  | |  /  /    | |  ___) | \n",
             " |_|  |_| /__/     |_| |____/   "},

            {" __   ___        ___ __   _____  \n",
             "/_ | |__ \\      /  //_ | | ____| \n",
             " | |    ) |    /  /  | | | |__   \n",
             " | |   / /    /  /   | | |___ \\  \n",
             " | |  / /_   /  /    | |  ___) | \n",
             " |_| |____| /__/     |_| |____/   "},

            {" __   ____        ___ __   _____  \n",
             "/_ | |___ \\      /  //_ | | ____| \n",
             " | |   __) |    /  /  | | | |__   \n",
             " | |  |__ <    /  /   | | |___ \\  \n",
             " | |  ___) |  /  /    | |  ___) | \n",
             " |_| |____/  /__/     |_| |____/   "},

            {" __   _  _         ___ __   _____  \n",
             "/_ | | || |       /  //_ | | ____| \n",
             " | | | || |_     /  /  | | | |__   \n",
             " | | |__   _|   /  /   | | |___ \\  \n",
             " | |    | |    /  /    | |  ___) | \n",
             " |_|    |_|   /__/     |_| |____/   "},

            {" __   _____       ___ __   _____  \n",
             "/_ | | ____|     /  //_ | | ____| \n",
             " | | | |__      /  /  | | | |__   \n",
             " | | |___ \\    /  /   | | |___ \\  \n",
             " | |  ___) |  /  /    | |  ___) | \n",
             " |_| |____/  /__/     |_| |____/   "}

        };

    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg));
    for (int i = 0; i < 13; i++)
    {
        center_addstr(1 + i, score_str[i]);
    }

    printw("\n\n\n");

    getyx(stdscr, row, cols);

    attrset(COLOR_PAIR(ORANGE_txt_BLACK_bg));
    for (int i = 0; i < 6; i++)
    {
        center_addstr(row + i, string[score][i]);
    }

    printw("\n\n\n\n\n");
    getyx(stdscr, row, cols);

    attrset(COLOR_PAIR(RED_txt_BLACK_bg));
    if (score >= PASS_MARKS)
        delayed_center_addstr(row, "Good job you did it!", 25);
    else
        delayed_center_addstr(row, "Better luck next time", 25);

    attrset(COLOR_PAIR(PURPLE_txt_BLACK_bg));
    delayed_center_addstr(LINES - 3, "Press any key to continue", 20);
    getch();
    flushinp();
    napms(300);
}