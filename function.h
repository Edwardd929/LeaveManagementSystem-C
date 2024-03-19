#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

//login.c
struct staff{
    char staff_id[100];
    char name[100];
    char age[100];
    char email[100];
    char contact_number[100];
    char staff_position[100];
    char department[100];
    char job_title[100];
    char username[100];
    char password[100];
};

void check_username();
void check_password(char* txtPassword, char* role, char* staff_id);


//menu.c
void login_menu();
void staff_menu(char* staff_id,char* role);
void admin_menu();
void approver_menu(char* staff_id,char* role);
void head_staff_menu(char* staff_id,char* role);
void head_approver_menu(char* staff_id,char* role);
void head_menu(char* staff_id,char* role);

//admin.c
struct staff_leave{
    char staff_id[100];
    int total;
};
char* get_department(char* name, char* department);
void new_staff();
void update_leave();
void search_leave();
void generate_report();

//staff.c
extern char current_date[100];
extern int current_year,current_month,current_day;
struct leave
{
    char staffID[100];
    char leave_type[100];
    char from[100];
    char to[100];
    int days;
    int first_month_days;
    int second_month_days;
    char reason[100];
    char status[100];
};

struct leave_summary
{
    char staffID[100];
    int annual_leave;
    int compassionate_leave;
    int emergency_leave;
    int maternity_leave;
    int medical_leave;
};

struct calendar
{
    char date[100];
    int annual_leave;
    int compassionate_leave;
    int emergency_leave;
    int maternity_leave;
    int medical_leave;
};

void get_current_date();
char* get_date(char* final_date,int leave_type);
int date_diff(int start_day,int start_month,int end_day,int end_month,int max_day);
char* check_date_advance_three(char *date);
char* check_date_advance(char *date);
char* check_date_before(char *date);

void apply_leave(char* staff_id,char* role);
void cancel_leave(char* staff_id,char* role);
void check_leave_status(char* staff_id,char* role);
void check_leave_summary(char* staff_id,char* role);


//approver.c
struct department_leave
{
    char department[100];
    char month[100];
    int annual_leave;
    int compassionate_leave;
    int emergency_leave;
    int maternity_leave;
    int medical_leave;
};

union head_member
{
    char staffID[100];
};

char* check_date(char *date);

void approve_reject(char* staff_id,char* role);
void search_date(char* staff_id,char* role);


//file.c
void read_leave_summary_file(struct leave_summary *read_leave_summary);
void read_staff_file(struct staff *read_staff);
void read_leave_calendar(struct calendar *read_calendar);
void read_department_file(struct department_leave *read_department_leave);
void read_apply_leave(struct leave *read_apply_leave);
void save_leave_summary(struct leave_summary *save_leave_summary);
void save_leave_calendar(struct calendar *save_leave_calendar);
void save_leave_department(struct department_leave *save_department_leave);
void save_leave_status(struct leave *save_apply_leave);

//extra_function.c
int blank_check(char *answer);
char* rstrip(char* word);
int number_check(char *answer);
int special_character(char* answer);
int vertical_bar(char* answer);
int space(char* answer);
void create_department_leave();
void replace_word(char* sentence,char ori,char update);
void create_calendar();
int count_line_leave(char* str);
int calculate_day(int day, int month);
int month_to_num(char month_txt[100]);
int not_count_weekends(int day1, int day2, int month1, int month2);
int weekend_check(int day, int month);

#endif // FUNCTION_H_INCLUDED
