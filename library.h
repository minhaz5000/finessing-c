#ifndef LIBRARY_H
#define LIBRARY_H
typedef struct container
{
	int id;
	char *question;
	char *code;
	char *opt[4];
	char *ans;
	int opt_count;
	int timer;
	int type;
} container;

typedef struct SAVE
{
	char id[32];
	int progress_flag[15];
} Save;

typedef enum
{

	_system_default_,
	_background_,

	_menu_default_, 
	_menu_dark_, // dark is unavailable
	_menu_current_,

	_topic_noob_, // noob is red
	_topic_mastered_, // green is mastered
	_topic_current_noob_, // current has a greyish bg
	_topic_current_mastered_,

	PURPLE_txt_BLACK_bg,
	BLACK_txt_PURPLE_bg,
	RED_txt_BLACK_bg,
	BLACK_txt_RED_bg,
	ORANGE_txt_BLACK_bg,
	DEEP_BLUE_txt_BLACK_bg,
	_back_to_black_,

	_option_ABCD_,

	_option_braces_,

	_about_composition_part_

} color_pairs;

// enum for topics and data files
typedef enum
{
	Datatypes = 11,
	Declaration_Init = 12,
	Input_Output = 13,
	Array = 14,
	Iteration = 15,
	Control_Statements = 16,
	Strings = 21,
	Pointers = 22,
	Functions = 23,
	Structures = 24,
	File = 31,
	Preprocessor = 32,
	Memory_Allocation = 33,
	Command_Line_Args = 34,
	C_Standard_Library = 35
} topics;

// MAX NUMBER OF QUESTIONS PER FILE LOADED TO REPOSITORY
#define MAX_CONTAINER_COUNT 128

#define _OPTION_A 'A'
#define _OPTION_B 'B'
#define _OPTION_C 'C'
#define _OPTION_D 'D'
#define QUIT_BUTTON 'Q'

#define BEGIN_FLAG "<begin>"
#define END_FLAG "</end>"
#define QUESTION_FLAG_BEGIN "<q>"
#define QUESTION_FLAG_END "</q>"
#define CODE_FLAG_BEGIN "<code>"
#define CODE_FLAG_END "</code>"
#define OPTION_FLAG_BEGIN "<opt>"
#define OPTION_FLAG_END "</opt>"
#define ANS_FLAG_BEGIN "<ans>"
#define ANS_FLAG_END "</ans>"
#define ID_FLAG_BEGIN "<id>"
#define ID_FLAG_END "</id>"

#define PASS_MARKS 12

container *create_container(char *s);
char *token_input(const char *input, const char *flag_begin, const char *flag_end);
int init_data(const char *FILEPATH, container **array);
container **repo_load(int topic, int *count);
void repo_destroy(container **arr, int count);
void decrypt(char *buffer, size_t size);

int first_menu(void); // first menu after login PLAY HOWTO ABOUT and EXIT button
int quiz_tier_menu(Save userdat); // beginner intermediate advanced
int beginner_menu(Save userdat); 
int intermediate_menu(Save userdat);
int advanced_menu(Save userdat);
int menu_control(Save userdat, int menucode); // controls all menus and ties them together can load any menu via the menucode

// Prints the Logo
void logo();

void about(void);
void demo(void); // help menu

char timer(int second);

Save login(void);

void cursor_go_whooosh(); // hides cursor
void cursor_comebaccc();  // unhides cursor

void center_addstr(int y, char *text); // centers any string using the predefined COLS constant
void delayed_center_addstr(int y, char *text, int time); // delays a centered text
void print_grid(int y);
void print_full_row(int y, char ch, int color_pair); 
void print_rectang(int start_x, int start_y, int end_x, int end_y, int color_pair, char ch);
void print_in_sub_window(int start_x, int start_y, int end_x, int end_y, int color_pair, char *str, int naptime);
void print_full_row_for_logo(int y, char ch, int color_pair);
void score_ascii_art(int score);

void naprefresh(int time);

void color_initialize_all();

int score_from_question(container question, int i);

int rand_comparison(const void *a, const void *b);
void shuffle(void *base, size_t nmemb, size_t size);

Save load_savefile(char *FILEPATH);
int update_savefile(Save *save_file);

void update_userdata_from_menucode(Save *userdata, int menucode);

#endif