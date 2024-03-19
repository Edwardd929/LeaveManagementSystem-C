#include "main.h"
#include "function.h"


void replace_word(char* sentence,char ori,char update){
    int word_len;
    word_len=strlen(sentence);
    for(int i=0;i<word_len;i++){
        // if the the word store in ori variable found in sentence, replace the word with the word store in update variable
        if(sentence[i]==ori){
            sentence[i]=update;
        }
    }
}



int number_check(char *answer) {
    int len = strlen(answer);
    for (int i=0;i<len;i++) {
        //check if the answer consist of alphabetical or special character
        if (!isdigit(answer[i])) {
            return 0;
        }
    }
    return 1;
}

int blank_check(char *answer){
    int len=strlen(answer);

    //remove the newline (\n)
    //\n means new line, \0 means null character
    if(len>0 && answer[len-1]=='\n') {
        answer[len-1]='\0';
    }
    len=strlen(answer);

    bool all_spaces= true;
    for(int i=0;i<len; i++){
        //check if the answer consist of space
        if(answer[i]!=' '){
            all_spaces=false;
            break;
        }
    }
    if(all_spaces){
        len=0;
    }
    //check if the user's input is blank
    if(len==0) {
        printf("Please don't leave it blank.\n\n");
    }
    return len;
}

int special_character(char* answer) {
    int word_len;
    word_len = strlen(answer);
    for(int i=0; i<word_len; i++) {
        //check if the answer consists of the special character
        if(!isalnum(answer[i])) {
            printf("Invalid input. Please don't include special character.\n\n");
            return 0;
        }
    }
    return 1;
}

int vertical_bar(char* answer) {
    int word_len;
    word_len = strlen(answer);
    for(int i=0; i<word_len; i++) {
        //check if the answer consists of the '|' character
        if(answer[i]=='|') {
            printf("Invalid input. Please don't include '|'.\n\n");
            return 0;
        }
    }
    return 1;
}

int space(char* answer) {
    int word_len;
    word_len = strlen(answer);
    for(int i=0; i<word_len; i++) {
        //check if the answer consists of the space in between
        if(answer[i]==' ') {
            printf("Invalid input. Please don't include space.\n\n");
            return 0;
        }
    }
    return 1;
}

char* rstrip(char* word){
    int word_len;
    char* word_end;

    //find the length of string
    word_len = strlen(word);

    // create a pointer to the last character of the word
    word_end = word + word_len - 1;

    // iterate backwards through the word until the first non-whitespace character found
    //this ensures that all the whitespace such as tab and space are removed from the end of the string
    while (word_end>=word_len && isspace(*word_end)){
        word_end--;
    }

    // set the first non-whitespace character to the null character
    *(word_end + 1) = '\0';
    return word;
}

void create_calendar(){
    //month_days is an array that stores the number of days for each month in year 2023
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //month_list is an array that stores all the month
    char month_list[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};

    int i,j;
    FILE *calendar=fopen("leave_calendar.txt","w");

    //create a 2023 calendar by looping through each month and each day
    for(i=0;i<12;i++){
        for(j=0;j<month_days[i];j++){
            fprintf(calendar,"%d%s2023 | Annual Leave: 0 | Compassionate Leave: 0 | Emergency Leave: 0 | Maternity Leave: 0 | Medical Leave: 0\n",j+1,month_list[i]);
        }
    }
    printf("The calendar of year 2023 has been successfully created.");
}

void create_department_leave(){
    //departments is an array that stores all the departments in APU
    char departments[9][100] = {
    "Academic Administration",
    "Asia Pacific Language Centre",
    "Faculty of Business and Management",
    "Faculty of Computing and Technology",
    "Human Resources",
    "Operations Management",
    "School of Foundation Studies",
    "School of Psychology",
    "Technology Services",
    };
    int i,j;

    char month_list[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};

    FILE *department_leave_write=fopen("department_leave.txt","w");

    //create a monthly department calendar by looping through each department and each month
    for(i=0;i<9;i++){
        for(j=0;j<12;j++){
            fprintf(department_leave_write,
                    "%s | %s | Annual Leave: 0 | Compassionate Leave: 0 | Emergency Leave: 0 | Maternity Leave: 0 | Medical Leave: 0\n",
                    departments[i],month_list[j]);
        }
    }
    printf("The department_leave.txt has been successfully created.\n\n");
}

int calculate_day(int day, int month) {
    //days_per_month is the array that store the number of each days per month in year 2023
    int days_per_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_day = day;

    //to calculate the cumulative days from 1/1/2023
    for (int i=1; i<month; i++) {
        total_day += days_per_month[i];
    }

    return total_day;
}

int month_to_num(char month_txt[100]) {
    char* months[] = {"", "January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};

    //to convert the month name to month number
    for (int i=1; i<=12; i++) {
        if (strstr(month_txt, months[i]) != NULL) {
            return i;
            break;
        }
    }

    // invalid month
    return 0;
}



int count_txt_line(char* str){
    int line_count = 0;
    char line[256];

    FILE* fo;
    fo = fopen(str,"r");

    //to count the number of lines in the text file by looping through each line until the line is NULL
    if(fo!=NULL){
        while(fgets(line,sizeof(line),fo)){
            line_count++;
        }
        fclose(fo);
    }
    return line_count;
}

int not_count_weekends(int day1, int day2, int month1, int month2) {
    int total;
    int total_days = 0;
    int year=2023;
    // Calculate the days between from and to dates
    struct tm from_date = {0};
    from_date.tm_year = year - 1900;
    from_date.tm_mon = month1 - 1;
    from_date.tm_mday = day1;
    //calculate seconds
    time_t time1 = mktime(&from_date);

    struct tm to_date = {0};
    to_date.tm_year = year - 1900;
    to_date.tm_mon = month2 - 1;
    to_date.tm_mday = day2;
    //calculate seconds
    time_t time2 = mktime(&to_date);

    double difference = difftime(time2, time1);
    //60*60*24 is to calculate from second to day
    total = difference/(60*60*24)+1;

    // Exclude weekends
    for (int i = 0; i < total; i++) {
        struct tm current_date = *localtime(&time1);
        current_date.tm_mday += i;
        mktime(&current_date);
        //not Saturday(6) and Sunday(0)
        if (current_date.tm_wday != 0 && current_date.tm_wday != 6) {
            total_days++;
        }
    }
    return total_days;
}

int weekend_check(int day, int month) {
    struct tm date = {.tm_mday = day, .tm_mon = month-1, .tm_year = 2023-1900 };

    // Use mktime to convert the input date to a time_t value
    time_t time = mktime(&date);

    // Use localtime to get the tm struct for the input date
    struct tm *date_now = localtime(&time);

    // Check if the day is a weekend
    if (date_now->tm_wday == 0 || date_now->tm_wday == 6) {
        return 1;
    } else {
        return 0;
    }
}
