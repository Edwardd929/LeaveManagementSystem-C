#include "main.h"
#include "function.h"
#define MAX_STRUCTS 1000

//extern variable
char current_date[100];
int current_year,current_month,current_day;

//get current date and store in extern variable - current_year, current_month, current_day
void get_current_date(){
    int n;

    // The NULL passed as an argument to the time function specifies that the current time should be stored in the time_now variable.
    // The time_t data type is used to represent the time.
    time_t time_now = time(NULL);

    struct tm *timeinfo;

    //convert the time stored in the time_now variable to a struct tm
    timeinfo = localtime(&time_now);

    //The strftime function is used to format a date stored in a struct tm object into a string.
    strftime(current_date, sizeof(current_date), "%Y-%m-%d", timeinfo);

    n = sscanf(current_date, "%d-%d-%d", &current_year, &current_month, &current_day);

    //check if the sscanf(current_date) can return 3 values
    if(n!=3){
       printf("Error!");
    }
}

//prompt the user to enter date
char* get_date(char* final_date,int leave_type){
    char date[11];
    char date2[11];
    int n,n2;
    int total_day;
    int day, month, year, day2, month2, year2;
    char* actual_date;
    char* actual_date2;

    //prompt the user to enter From Date
    printf("\nRequest Leave From Date(YYYY-MM-DD)");
    printf("\n---------------------------------------------------------------------------------\n");

    //if leave type is annual leave
    if (leave_type==1){
        actual_date=check_date_advance_three(date);

    //if leave type is medical or compassionate leave
    }else if(leave_type==3 || leave_type==4){
        actual_date=check_date_advance(date);

    //if leave type is emergency or maternity leave
    }else{
        actual_date=check_date_before(date);
    }

    n = sscanf(actual_date, "%d-%d-%d", &year, &month, &day);
    if(n!=3){
       printf("Error!");
    }

    //prompt the user to enter To Date
    printf("\n---------------------------------------------------------------------------------\n");
    printf("\nRequest Leave To Date(YYYY-MM-DD)");
    printf("\n*Enter the same date if the leave date is one day only.");
    printf("\n---------------------------------------------------------------------------------\n");

    actual_date2=check_date(date2);
    n2 = sscanf(actual_date2, "%d-%d-%d", &year2, &month2, &day2);
    if(n2!=3){
       printf("Error!");
    }

    //combine year, month, day,year2,month2,day2 into final_date
    sprintf(final_date, "%d-%d-%d,%d-%d-%d", year, month, day,year2,month2,day2);
    return(final_date);
}




//ensure that the annual leave will be applied 3 days in advance
char* check_date_advance_three(char *date){
    char day[100],month[100];
    int day_num,month_num,year_num;
    int day_status,month_status;
    int day_in_month[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day_a, day_b;

    printf("Year 2023\n");
    year_num=2023;

    do{
        printf("Enter month(MM): ");
        fgets(month,100,stdin);
        month_status=blank_check(month);
        if (month_status==0){
            continue;
        }else if(sscanf(month,"%d",&month_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            month_status=0;
        }else if(current_month==month_num && current_day+3>day_in_month[month_num-1]){
            printf("The annual leave can only be applied in advance.You cannot apply for annual leave for this month as it is less than 3 days in advance.\n");
            printf("Please enter a valid month that is after the current month (%d) - 12.\n\n",current_month+1);
            month_status=0;
        }else if(month_num<current_month || month_num>12){
            printf("The annual leave can only be applied in advance.\n");
            if(current_day+3>day_in_month[current_month-1]){
                printf("Since you cannot apply for annual leave for this month as it is less than 3 days in advance, please enter a valid month that is after to the current one(%d) - 12.\n\n",current_month+1);
            }else{
                printf("Please enter a valid month that is either after or equal to the current one(%d) - 12.\n\n",current_month);
            }
            month_status=0;
        }else{
            month_status=1;
        }
    }while(month_status==0);

    do{
        printf("Enter day(DD): ");
        fgets(day,100,stdin);
        day_status=blank_check(day);
        if (day_status==0){
            continue;
        }else if(sscanf(day,"%d",&day_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            day_status=0;

        }else if(current_month==month_num-1){
            day_a = calculate_day(day_num,month_num);
            day_b= calculate_day(current_day,current_month);
            if(day_a<day_b+3){
                printf("Kindly submit your request for annual leave 3 days in advance.\n");
                printf("Please enter a valid day which is from %d onwards.\n\n",current_day+3-day_in_month[month_num-2]);
                day_status=0;
            }
        }else if(current_month==month_num){
            if(month_num%2==0 && month_num!=2 && month_num<8 && (day_num<current_day+3 || day_num>30)){
                printf("Kindly submit your request for annual leave 3 days in advance.\n");
                printf("Please enter a valid day which is from %d onwards. The last day of this month is 30.\n\n",current_day+3);
                day_status=0;

            }else if(month_num%2==0 && month_num!=2 && month_num>=8 && (day_num<current_day+3 || day_num>31)){
                printf("Kindly submit your request for annual leave 3 days in advance.\n");
                printf("Please enter a valid day which is from %d onwards. The last day of this month is 31.\n\n",current_day+3);
                day_status=0;

            }else if(month_num%2!=0 && month_num<8 && (day_num<current_day+3 || day_num>31)){
                printf("Kindly submit your request for annual leave 3 days in advance.\n");
                printf("Please enter a valid day which is from %d onwards. The last day of this month is 31.\n\n",current_day+3);
                day_status=0;

            }else if(month_num%2!=0 && month_num>=8 && (day_num<current_day+3 || day_num>30)){
                printf("Kindly submit your request for annual leave 3 days in advance.\n");
                printf("Please enter a valid day which is from %d onwards. The last day of this month is 30.\n\n",current_day+3);
                day_status=0;

            }else if(month_num==2){
                //not a leap year
                if(day_num<current_day+3 || day_num>28){
                        printf("Kindly submit your request for annual leave 3 days in advance.\n");
                    printf("Please enter a valid day which is from %d onwards. The last day of this month is 28.\n\n",current_day+3);
                    day_status=0;
                }
            }
        }else{
            if(month_num%2==0 && month_num!=2 && month_num<8 && (day_num<1 || day_num>30)){
                printf("Please enter a valid day between 1 and 30.\n\n");
                day_status=0;

            }else if(month_num%2==0 && month_num!=2 && month_num>=8 && (day_num<1 || day_num>31)){
                printf("Please enter a valid day between 1 and 31.\n\n");
                day_status=0;

            }else if(month_num%2!=0 && month_num<8 && (day_num<1 || day_num>31)){
                printf("Please enter a valid day between 1 and 31.\n\n");
                day_status=0;

            }else if(month_num%2!=0 && month_num>=8 && (day_num<1 || day_num>30)){
                printf("Please enter a valid day between 1 and 30.\n\n");
                day_status=0;

            }else if(month_num==2){
                //not a leap year
                if(day_num<1 || day_num>28){
                    printf("Please enter a valid day between 1 and 28.\n\n");
                    day_status=0;
                }
            }
        }
    }while(day_status==0);

    sprintf(date, "%d-%02d-%02d", year_num, month_num, day_num);
    return(date);
}

//ensure that the emergency and maternity leave will be applied on current day or in advance
char* check_date_advance(char *date){
    char day[100],month[100];
    int day_num,month_num,year_num;
    int day_status,month_status;

    printf("Year 2023\n");
    year_num=2023;

    do{
        printf("Enter month(MM): ");
        fgets(month,100,stdin);
        month_status=blank_check(month);
        if (month_status==0){
            continue;
        }else if(sscanf(month,"%d",&month_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            month_status=0;
        }else if(month_num<current_month || month_num>12){
            printf("The emergency leave/maternity leave can can be applied either in advance or on the same day only.\n");
            printf("Please enter a valid month that is either after or equal to the current one(%d) - 12.\n\n",current_month);
            month_status=0;
        }else{
            month_status=1;
        }
    }while(month_status==0);

    do{
        printf("Enter day(DD): ");
        fgets(day,100,stdin);
        day_status=blank_check(day);
        if (day_status==0){
            continue;
        }else if(sscanf(day,"%d",&day_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            day_status=0;

        }else if(current_month==month_num){
            if(month_num%2==0 && month_num!=2 && month_num<8 && (day_num<current_day || day_num>30)){
                printf("Please enter a valid day that is either after or equal to the current one(%d). The last day of this month is 30.\n\n",current_day);
                day_status=0;

            }else if(month_num%2==0 && month_num!=2 && month_num>=8 && (day_num<current_day || day_num>31)){
                printf("Please enter a valid day that is either after or equal to the current one(%d). The last day of this month is 31.\n\n",current_day);
                day_status=0;

            }else if(month_num%2!=0 && month_num<8 && (day_num<current_day || day_num>31)){
                printf("Please enter a valid day that is either after or equal to the current one(%d). The last day of this month is 31.\n\n",current_day);
                day_status=0;

            }else if(month_num%2!=0 && month_num>=8 && (day_num<current_day || day_num>30)){
                printf("Please enter a valid day that is either after or equal to the current one(%d). The last day of this month is 30.\n\n",current_day);
                day_status=0;

            }else if(month_num==2){
                //not a leap year
                if(day_num<current_day || day_num>28){
                    printf("Please enter a valid day that is either after or equal to the current one(%d). The last day of this month is 28.\n\n",current_day);
                    day_status=0;
                }
            }
        }else{
            if(month_num%2==0 && month_num!=2 && month_num<8 && (day_num<1 || day_num>30)){
                printf("Please enter a valid day between 1 and 30.\n\n");
                day_status=0;

            }else if(month_num%2==0 && month_num!=2 && month_num>=8 && (day_num<1 || day_num>31)){
                printf("Please enter a valid day between 1 and 31.\n\n");
                day_status=0;

            }else if(month_num%2!=0 && month_num<8 && (day_num<1 || day_num>31)){
                printf("Please enter a valid day between 1 and 31.\n\n");
                day_status=0;

            }else if(month_num%2!=0 && month_num>=8 && (day_num<1 || day_num>30)){
                printf("Please enter a valid day between 1 and 30.\n\n");
                day_status=0;

            }else if(month_num==2){
                //not a leap year
                if(day_num<1 || day_num>28){
                    printf("Please enter a valid day between 1 and 28.\n\n");
                    day_status=0;
                }
            }
        }
    }while(day_status==0);

    sprintf(date, "%d-%02d-%02d", year_num, month_num, day_num);
    return(date);
}

//ensure that the medical and compasionate leave will be applied before or on current date
char* check_date_before(char *date){
    char day[100],month[100];
    int day_num,month_num,year_num;
    int day_status,month_status;

    printf("Year 2023\n");
    year_num=2023;

    do{
        printf("Enter month(MM): ");
        fgets(month,100,stdin);
        month_status=blank_check(month);
        if (month_status==0){
            continue;
        }else if(sscanf(month,"%d",&month_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            month_status=0;
        }else if(month_num<1 || month_num>current_month){
            printf("Invalid month! Compassionate leave/ medical leave cannot be applied in advance and can only be requested from the current day or any date prior to it.\n");
            printf("Please enter a number that represents a month that is either before or equal to the current one(%d) - 12.\n\n",current_month);
            month_status=0;
        }else{
            month_status=1;
        }
    }while(month_status==0);

    do{
        printf("Enter day(DD): ");
        fgets(day,100,stdin);
        day_status=blank_check(day);
        if (day_status==0){
            continue;
        }else if(sscanf(day,"%d",&day_num)!= 1){
            printf("Invalid input. Please enter number.\n\n");
            day_status=0;

        }else if(month_num==current_month && (day_num<1 || day_num>current_day)){
            printf("Invalid day! Compassionate leave/ medical leave cannot be applied in advance.\n");
            printf("Please enter a valid day that is either before or equal to the current one(%d).\n\n",current_day);
            day_status=0;

        }else if(month_num%2==0 && month_num!=2 && month_num<8 && (day_num<1 || day_num>30)){
            printf("Please enter a valid day between 1 and 30.\n\n");
            day_status=0;

        }else if(month_num%2==0 && month_num!=2 && month_num>=8 && (day_num<1 || day_num>31)){
            printf("Please enter a valid day between 1 and 31.\n\n");
            day_status=0;

        }else if(month_num%2!=0 && month_num<8 && (day_num<1 || day_num>31)){
            printf("Please enter a valid day between 1 and 31.\n\n");
            day_status=0;

        }else if(month_num%2!=0 && month_num>=8 && (day_num<1 || day_num>30)){
            printf("Please enter a valid day between 1 and 30.\n\n");
            day_status=0;

        }else if(month_num==2){
            //not a leap year
            if(day_num<1 || day_num>28){
                printf("Please enter a valid day between 1 and 28.\n\n");
                day_status=0;
            }
        }
    }while(day_status==0);

    sprintf(date, "%d-%02d-%02d", year_num, month_num, day_num);
    return(date);
}

//Apply leave
void apply_leave(char* staff_id,char* role){
    //cannot apply leave on the same date

    int line,line2;

    struct leave wleave;

    char leave_type[100];
    int leave_type_status;
    int leave_type2;

    int day,month,year,day2,month2,year2;
    int total_day=0;
    char days[100];
    char reason[100];
    int reason_status;
    int reason_num;
    char status[100];
    char month_list[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    char* to_month;
    char* to_month2;
    char first_date[100];
    char last_date[100];
    int selected_read_leave_summary;
    int day_balance;
    int applied_day,applied_day2;
    char applied_month[100];
    char applied_month2[100];
    int applied_month_num, applied_month_num2;
    int applied_num_of_days,applied_num_of_days2;
    int apply_num_of_days,apply_num_of_days2;

    int overlap=0;

    char confirm[100];
    int confirm_status=0;
    int confirm_num;
    int gone=0;

    char back[100];
    int back_num;
    int back_status;

    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int first_month_total=0;
    int second_month_total=0;

    line=count_txt_line("leave_summary.txt");
    line2= count_txt_line("apply_leave.txt");

    struct leave_summary* read_leave_summary = (struct leave_summary*) malloc(line * sizeof(struct leave_summary));
    struct leave *aleave = (struct leave *) malloc (line2* sizeof(struct leave));

    read_leave_summary_file(read_leave_summary);
    read_apply_leave(aleave);

    for (int i=0;i<line;i++){
        if(strcmp(read_leave_summary[i].staffID,staff_id)==0){
            selected_read_leave_summary=i;
        }
    }

    printf("\n==Apply Leave==\n");

    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("| Number |            Type of Leave                  |\n");
    printf("|--------|-------------------------------------------|\n");
    printf("|   1    |            Annual Leave                   |\n");
    printf("|   2    |            Compassionate Leave            |\n");
    printf("|   3    |            Emergency Leave                |\n");
    printf("|   4    |            Maternity Leave                |\n");
    printf("|   5    |            Medical Leave                  |\n");
    printf("-----------------------------------------------------\n");
    printf("\n");

    //print the requirement for each leave type
    do{
        printf("Please enter your choice by typing number: ");
        fgets(leave_type,100, stdin);
        leave_type_status = blank_check(leave_type);
        if (leave_type_status==0){
            continue;
        }else if (sscanf(leave_type, "%d", &leave_type2) != 1) {
            printf("Invalid input. Please enter number.\n\n");
            leave_type_status=0;

        }else if(leave_type2==1){
            printf("\nPlease note that annual leave can only be requested from at least three days before the intended start date.\n\n");
            strcpy(leave_type,"Annual Leave");
            day_balance=read_leave_summary[selected_read_leave_summary].annual_leave;
            leave_type_status=1;

        }else if(leave_type2==2){
            printf("\nPlease note that compassionate leave can only be requested from the current day or a date prior to it, and not in advance.\n\n");
            strcpy(leave_type,"Compassionate Leave");
            day_balance=read_leave_summary[selected_read_leave_summary].compassionate_leave;
            leave_type_status=1;

        }else if(leave_type2==3){
            printf("\nPlease note that emergency leave can only be requested from the current day or a date after the current day.\n\n");
            strcpy(leave_type,"Emergency Leave");
            day_balance=read_leave_summary[selected_read_leave_summary].emergency_leave;
            leave_type_status=1;

        }else if(leave_type2==4){
            printf("\nPlease note that maternity leave can only be requested from the current day or a date after the current day.\n\n");
            strcpy(leave_type,"Maternity Leave");
            day_balance=read_leave_summary[selected_read_leave_summary].maternity_leave;
            leave_type_status=1;

        }else if(leave_type2==5){
            printf("\nPlease note that medical leave can only be requested from the current day or a date prior to it, and not in advance.\n\n");
            strcpy(leave_type,"Medical Leave");
            day_balance=read_leave_summary[selected_read_leave_summary].medical_leave;
            leave_type_status=1;

        }else{
            printf("Number is out of range.\n\n");
            leave_type_status=0;
        }
    }while(leave_type_status==0);


    printf("Leave Application Type: %s\n",leave_type);
    printf("%s Balance before Application: %d\n",leave_type,day_balance);
    printf("\n*Please note that the total number of days requested for leave will exclude weekends, as the APU staff only operates on weekdays.\n");

    //check if the leave application date entered is valid
    while(total_day==0){
        char* final_date=get_date(days,leave_type2);
        sscanf(final_date,"%d-%d-%d,%d-%d-%d",&year,&month,&day,&year2,&month2,&day2);
        int apply_num_of_days = calculate_day(day,month);
        int apply_num_of_days2 = calculate_day(day2,month2);
        total_day=apply_num_of_days2-apply_num_of_days+1;
        if ((day2<day && month==month2)
        ||(month>month2)){
            printf("The dates for your leave request are not valid as they are not in chronological order.\n");
            printf("Kindly provide a valid date range for your leave application.\n\n");
            total_day=0;
        }else if(total_day>28){
            printf("Sorry. You are able to take the maximum of 28 days off only at once through a single leave application.\n");
            printf("Your adherence to our time off policy is greatly appreciated.\n");
            printf("Please enter the date again.\n\n");
            total_day=0;
        }
    }

    //check if the whole leave is on weekend
    if(month==month2){
        first_month_total=not_count_weekends(day,day2,month,month2);
        second_month_total=0;
        if(first_month_total==0){
            overlap=1;
            printf("The leave you applied is weekend. No leave application needed.\n\n");
        }else{
            wleave.first_month_days=first_month_total;
            wleave.second_month_days=second_month_total;
        }
    }else{
        first_month_total=not_count_weekends(day,month_days[month-1],month,month);
        second_month_total=not_count_weekends(1,day2,month2,month2);
        if(first_month_total+second_month_total==0){
            printf("The leave you applied is weekend. No leave application needed.\n\n");
            overlap=1;
        }else{
            wleave.first_month_days=first_month_total;
            wleave.second_month_days=second_month_total;
        }
    }

    //check if the leave application total days is over the leave balance
    if(wleave.first_month_days+wleave.second_month_days>day_balance){
        printf("Leave application unsuccessful. You are limited to taking only %d days off as you have only %d days of leave remaining.\n\n",day_balance,day_balance);
        overlap=1;
    }


    apply_num_of_days = calculate_day(day,month);
    apply_num_of_days2 = calculate_day(day2,month2);

    //check if the leave application is duplicate among same staff
    for(int i=0;i<line2;i++){
        if(strcmp(aleave[i].staffID,staff_id)==0){
            sscanf(aleave[i].from,"%d%s",&applied_day,applied_month);
            sscanf(aleave[i].to,"%d%s",&applied_day2,applied_month2);
            applied_month_num = month_to_num(applied_month);
            applied_month_num2=month_to_num(applied_month2);

            applied_num_of_days = calculate_day(applied_day,applied_month_num);
            applied_num_of_days2 = calculate_day(applied_day2,applied_month_num2);

            if(apply_num_of_days>=applied_num_of_days && apply_num_of_days <=applied_num_of_days2 &&((strcmp(aleave[i].status,"pending")==0) || (strcmp(aleave[i].status,"approved")==0))){
                printf("Leave application unsuccessful. Your requested leave date overlaps with another leave request that you have already submitted.\n");
                printf("Please note that cancelled or rejected leaves will not be considered as overlaps. If you wish to apply for this leave, you will need to cancel the previous request.\n\n");
                overlap=1;
                break;
            }else if(apply_num_of_days2>=applied_num_of_days && apply_num_of_days2 <=applied_num_of_days2 &&((strcmp(aleave[i].status,"pending")==0) || (strcmp(aleave[i].status,"approved")==0))){
                printf("Leave application unsuccessful. Your requested leave date overlaps with another leave request that you have already submitted.\n");
                printf("Please note that cancelled or rejected leaves will not be considered as overlaps. If you wish to apply for this leave, you will need to cancel the previous request.\n\n");
                overlap=1;
                break;
            }
        }
    }

    //if the leave application has met all the criteria
    if(overlap==0){
        do{
            printf("\nReason: ");
            fgets(reason,100, stdin);
            reason_status = blank_check(reason);
            if (sscanf(reason, "%d", &reason_num)== 1){
                printf("Please enter a valid reason.\n\n");
                reason_status=0;
            }
        }while(reason_status == 0);

        to_month=month_list[month-1];
        to_month2=month_list[month2-1];
        sprintf(first_date,"%d%s%d",day,to_month,year);
        sprintf(last_date,"%d%s%d",day2,to_month2,year2);

        printf("\n---------------------------------------------------------------------------------\n");
        if(strcmp(first_date,last_date)==0){
            printf("\nYour Request %s's Date is on %s.\n",leave_type,first_date);
        }else{
            printf("\nYour Request %s's Date is from %s-%s.\n",leave_type,first_date,last_date);
        }
        printf("Total Leave Days (exclude Saturday and Sunday): %d days \n",wleave.first_month_days+wleave.second_month_days);
        printf("Reason: %s\n", reason);
        printf("\n---------------------------------------------------------------------------------\n");


        // Ask the user to confirm the leave application
        do{
            printf("\nPlease confirm that the leave application above is correct by entering 1 to submit it.\nIf you need to make any changes, enter 2: ");
            fgets(confirm,100,stdin);
            confirm_status=blank_check(confirm);
            if(confirm_status==0){
                continue;
            }else if (!number_check(confirm)){
                printf("Invalid input. Please enter number.\n\n");
                confirm_status=0;
            }else if((sscanf(confirm, "%d", &confirm_num) != 1)){
                confirm_status=0;
            }else if(confirm_num==1){
                confirm_status=1;
            }else if(confirm_num==2){
                printf("\nPlease reenter the correct leave application.\n");
                confirm_status=1;
                gone=1;
                apply_leave(staff_id,role);
            }else{
                printf("Invalid input. Please enter 1 to save the staff information or enter 2 to make changes.\n\n");
                confirm_status=0;
            }

        }while(confirm_status==0);

        //if the user had confirmed by typing 1
        if(confirm_num==1){
            strcpy(status,"pending");
            strcpy(wleave.staffID,staff_id);
            strcpy(wleave.leave_type,leave_type);
            strcpy(wleave.from,first_date);
            strcpy(wleave.to,last_date);
            wleave.days=total_day;
            strcpy(wleave.reason,reason);
            strcpy(wleave.status,status);

            FILE *apply_leave_txt = fopen("apply_leave.txt", "a");
            fprintf(apply_leave_txt,"%s | %s | %s | %s | %d | %d | %d | %s | %s\n",wleave.staffID,wleave.leave_type,wleave.from,wleave.to,wleave.days,wleave.first_month_days,
                    wleave.second_month_days,wleave.reason,wleave.status);
            fclose(apply_leave_txt);

            printf("\nYour leave application is successfully uploaded.\n\n");
        }
    }


    free(read_leave_summary);
    free(aleave);

    //if the user does not reenter the leave application
    if(gone==0){
        do{
            printf("Would you like to apply another leave? Enter 1 for yes or 2 to return to the Staff Menu page.\n");
            fgets(back,100, stdin);
            back_status = blank_check(back);
            if (back_status==0){
                continue;
            }else if (!number_check(back)){
                printf("Invalid input. Please enter the number.\n\n");
                back_status=0;
            }else if((sscanf(back, "%d", &back_num) != 1)){
                back_status=0;
            }else if(back_num==1){
                apply_leave(staff_id,role);
                back_status=1;
                break;
            }else if(back_num==2){
                if (strcmp(role,"Head")==0){
                    head_staff_menu(staff_id,role);
                }else{
                    staff_menu(staff_id,role);
                }
                back_status=1;
                break;
            }else{
                printf("The number entered is out of range. Please try again.\n\n");
                back_status=0;
            }
        }while(back_status==0);
    }

}

//cancel leave (approved or pending status, cannot cancel if the on leave date has passed)
void cancel_leave(char* staff_id,char* role){
    //cancel approved leave need refer to apply_leave.txt, leave_summary.txt, leave_calendar.txt, department_leave.txt

    char month_list[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};

    int line,line2,line3,line4,line5;
    int staffFound=0;
    int n;

    int selected[100];
    int leave_num=0;

    char cancel[100];
    int cancel_num;
    int cancel_status;

    int cleave_index;
    char leave_month[100];
    int leave_month_num,leave_day;

    int true_date_index;
    int limit_date_index;

    char* department_txt;
    char leave_type[100];
    int selected_cancel_leave_summary;

    char back[100];
    int back_num;
    int back_status;


    line=count_txt_line("apply_leave.txt");
    line2=count_txt_line("leave_summary.txt");
    line3=count_txt_line("leave_calendar.txt");
    line4=count_txt_line("department_leave.txt");
    line5=count_txt_line("staff_info.txt");

    struct leave *cleave = (struct leave *) malloc (line* sizeof(struct leave));
    struct leave_summary* cancel_leave_summary = (struct leave_summary*) malloc(line2 * sizeof(struct leave_summary));
    struct calendar *cancel_calendar = (struct calendar *) malloc(line3 * sizeof(struct calendar));
    struct department_leave *cancel_department_leave= (struct department_leave *) malloc(line4 * sizeof(struct department_leave));
    struct staff *staff_info = (struct staff *) malloc(line5 * sizeof(struct staff));

    read_apply_leave(cleave);
    read_leave_summary_file(cancel_leave_summary);
    read_leave_calendar(cancel_calendar);
    read_department_file(cancel_department_leave);
    read_staff_file(staff_info);

     for(int i=0;i<line5;i++){
        if(strcmp(staff_id,staff_info[i].staff_id)==0){
            department_txt= staff_info[i].department;
        }
     }

    for(int i=0;i<line2;i++){
        if(strcmp(staff_id,cancel_leave_summary[i].staffID)==0){
            selected_cancel_leave_summary=i;
        }
    }


    for(int i=0;i<line;i++){
        if(strcmp(staff_id,cleave[i].staffID)==0){
            staffFound=1;
            break;
        }
    }

    printf("\n");
    printf("\n==Cancel Leave(approved or pending status)==\n");

    if (staffFound==0){
        printf("\nYou have not apply any leave.\n");
    }else{
        printf("\nLeave Application Available for Cancellation:\n");
        for(int i=0;i<line;i++){
            n = sscanf(cleave[i].from, "%d%s", &leave_day, leave_month);
            if(n!=2){
                printf("Error!");
            }
            for(int j=0;j<12;j++){
                if(strstr(leave_month,month_list[j])!=NULL){
                    leave_month_num=j+1;
                }
            }
            if(((leave_month_num==current_month)&&(leave_day<=current_day))|| (leave_month_num<current_month)){
                continue;
            }
            if((strcmp(cleave[i].status,"cancelled")==0)||(strcmp(cleave[i].status,"rejected")==0)){
                continue;
            }

            //print the leave application one by one
            if(strcmp(staff_id,cleave[i].staffID)==0){
                selected[leave_num]=i;
                leave_num++;
                printf("\n---------------------------------------------------------------------------------\n");
                printf("%s's Leave Application %d\n",staff_id,leave_num);
                printf("Leave Type: %s\n",cleave[i].leave_type);
                printf("Leave Date From: %s\n",cleave[i].from);
                printf("Leave Date To: %s\n",cleave[i].to);
                printf("Total Days (exclude weekend): %d\n",cleave[i].first_month_days+cleave[i].second_month_days);
                printf("Reason: %s\n",cleave[i].reason);
                printf("Status: %s\n",cleave[i].status);
                printf("\n---------------------------------------------------------------------------------\n\n");

            }
        }
        //print the reason of why the leave application is unable to cancel
        if(leave_num==0){
            printf("\nYou do not have a leave application available for cancellation.\n\n");
            printf("+------------------------------------------------------------------------------------------------------------------+\n");
            printf("| Note: This may be due to the following reasons:                                                                  |\n");
            printf("|------------------------------------------------------------------------------------------------------------------|\n");
            printf("|                                                                                                                  |\n");
            printf("| 1. You have not submitted a leave request.                                                                       |\n");
            printf("| 2. Your leave has been cancelled before.                                                                         |\n");
            printf("| 3. Your leave has been rejected.                                                                                 |\n");
            printf("| 4. The start date of your leave has already passed or is due to begin today.                                     |\n");
            printf("|                                                                                                                  |\n");
            printf("+------------------------------------------------------------------------------------------------------------------+\n");

        }else{
            printf("+------------------------------------------------------------------------------------------------------------------+\n");
            printf("| Note: If the leave you want to cancel is not listed above, this may be due to the following reasons:             |\n");
            printf("|------------------------------------------------------------------------------------------------------------------|\n");
            printf("|                                                                                                                  |\n");
            printf("| 1. Your leave has been cancelled before.                                                                         |\n");
            printf("| 3. Your leave has been rejected.                                                                                 |\n");
            printf("| 4. The start date of your leave has already passed or is due to begin today.                                     |\n");
            printf("|                                                                                                                  |\n");
            printf("+------------------------------------------------------------------------------------------------------------------+\n\n");

            //prompt the user to select the leave application by entering number
            do{
                printf("Please enter the number of leave application you want to cancel: %s's Leave Application ",staff_id);
                fgets(cancel,100,stdin);
                cancel_status=blank_check(cancel);
                if(cancel_status==0){
                    continue;
                }else if(sscanf(cancel,"%d",&cancel_num)!=1){
                    printf("Please enter number.\n\n");
                    cancel_status=0;
                }else if(cancel_num<0 || cancel_num>leave_num){
                    if(leave_num!=1){
                        printf("The number is out of range. Please enter the number between 1 and %d.\n\n",leave_num);
                    }else{
                        printf("The number is out of range.\n\n");
                    }
                    cancel_status=0;
                }else{
                    cancel_status=1;
                }
            }while(cancel_status==0);

            cleave_index = selected[cancel_num-1];
            strcpy(leave_type,cleave[cleave_index].leave_type);

            //if the leave status is approved, then need to modify the leave summary text file to add back the leave balance
            if (strcmp(rstrip(cleave[cleave_index].status),"approved")==0){
                if(strcmp(leave_type,"Annual Leave ")==0){
                    cancel_leave_summary[selected_cancel_leave_summary].annual_leave+=(cleave[cleave_index].first_month_days+cleave[cleave_index].second_month_days);
                }else if(strcmp(leave_type,"Compassionate Leave ")==0){
                    cancel_leave_summary[selected_cancel_leave_summary].compassionate_leave+=(cleave[cleave_index].first_month_days+cleave[cleave_index].second_month_days);
                }else if(strcmp(leave_type,"Emergency Leave ")==0){
                    cancel_leave_summary[selected_cancel_leave_summary].emergency_leave+=(cleave[cleave_index].first_month_days+cleave[cleave_index].second_month_days);
                }else if(strcmp(leave_type,"Maternity Leave ")==0){
                    cancel_leave_summary[selected_cancel_leave_summary].maternity_leave+=(cleave[cleave_index].first_month_days+cleave[cleave_index].second_month_days);
                }else if(strcmp(leave_type,"Medical Leave ")==0){
                    cancel_leave_summary[selected_cancel_leave_summary].medical_leave+=(cleave[cleave_index].first_month_days+cleave[cleave_index].second_month_days);
                }

                //if the leave status is approved, then need to modify the leave calendar text file
                for(int i=0;i<line3;i++){
                    if(strcmp(cleave[cleave_index].from,cancel_calendar[i].date)==0){
                        true_date_index=i;
                        break;
                    }
                }

                limit_date_index=true_date_index+cleave[cleave_index].days-1;

                for(int i=true_date_index;i<=limit_date_index;i++){
                    if(strcmp(leave_type, "Annual Leave ")==0){
                        cancel_calendar[i].annual_leave-=1;
                    }else if(strcmp(leave_type, "Compassionate Leave ")==0){
                        cancel_calendar[i].compassionate_leave-=1;
                    }else if(strcmp(leave_type, "Emergency Leave ")==0){
                        cancel_calendar[i].emergency_leave-=1;
                    }else if(strcmp(leave_type, "Maternity Leave ")==0){
                        cancel_calendar[i].maternity_leave-=1;
                    }else if(strcmp(leave_type, "Medical Leave ")==0){
                        cancel_calendar[i].medical_leave-=1;
                    }else{
                        printf("Error modifying leave calendar text.");
                        return 1;
                    }
                }

                //if the leave status is approved, then need to modify the department leave text file
                for(int i=0; i<line4;i++){
                    if((strcmp(cancel_department_leave[i].department, department_txt)==0)
                       && (strstr(cleave[cleave_index].from,cancel_department_leave[i].month)!=NULL)){
                        if(strcmp(leave_type, "Annual Leave ")==0){
                            cancel_department_leave[i].annual_leave-=cleave[cleave_index].first_month_days;
                            cancel_department_leave[i+1].annual_leave-=cleave[cleave_index].second_month_days;
                        }else if(strcmp(leave_type, "Compassionate Leave ")==0){
                            cancel_department_leave[i].compassionate_leave-=cleave[cleave_index].first_month_days;
                            cancel_department_leave[i+1].compassionate_leave-=cleave[cleave_index].second_month_days;
                        }else if(strcmp(leave_type, "Emergency Leave ")==0){
                            cancel_department_leave[i].emergency_leave-=cleave[cleave_index].first_month_days;
                            cancel_department_leave[i+1].emergency_leave-=cleave[cleave_index].second_month_days;
                        }else if(strcmp(leave_type, "Maternity Leave ")==0){
                            cancel_department_leave[i].maternity_leave-=cleave[cleave_index].first_month_days;
                            cancel_department_leave[i+1].maternity_leave-=cleave[cleave_index].second_month_days;
                        }else if(strcmp(leave_type, "Medical Leave ")==0){
                            cancel_department_leave[i].medical_leave-=cleave[cleave_index].first_month_days;
                            cancel_department_leave[i+1].medical_leave-=cleave[cleave_index].second_month_days;
                        }else{
                            printf("Error modifying department leave text file.");
                            return 1;
                        }
                    }
                }

                //save all the text file
                save_leave_summary(cancel_leave_summary);

                save_leave_calendar(cancel_calendar);

                save_leave_department(cancel_department_leave);

            }

            strcpy(cleave[cleave_index].status,"cancelled");

            save_leave_status(cleave);

            printf("\nLeave application %d has been cancelled.\n\n", cancel_num);
        }
    }
    //free the memory of cleave when it is not needed anymore
    free(cleave);
    free(cancel_leave_summary);
    free(cancel_calendar);
    free(cancel_department_leave);
    free(staff_info);

    //prompt the user to enter 1 to return to the Staff Menu page
    if(staffFound==0 || leave_num==0 || leave_num==1){
        do{
            printf("Since there are no leave applications left for cancellation, please enter 1 to return to the Staff Menu page.\n");
            fgets(back,100, stdin);
            back_status = blank_check(back);
            if (back_status==0){
                continue;
            }else if (!number_check(back)){
                printf("Invalid input. Please enter the number.\n\n");
                back_status=0;
            }else if((sscanf(back, "%d", &back_num) != 1)){
                back_status=0;
            }else if(back_num==1){
                if (strcmp(role,"Head")==0){
                    head_staff_menu(staff_id,role);
                }else{
                    staff_menu(staff_id,role);
                }
                back_status=1;
                break;
            }else{
                printf("Invalid input. Please try again.\n\n");
                back_status=0;
            }
        }while(back_status==0);

    //prompt the user to enter 1 to cancel another leave and enter 2 to return to the Staff Menu page
    }else{
        do{
            printf("Would you like to cancel another leave? Enter 1 for yes or 2 to return to the Staff Menu page.\n");
            fgets(back,100, stdin);
            back_status = blank_check(back);
            if (back_status==0){
                continue;
            }else if (!number_check(back)){
                printf("Invalid input. Please enter the number.\n\n");
                back_status=0;
            }else if((sscanf(back, "%d", &back_num) != 1)){
                back_status=0;
            }else if(back_num==1){
                cancel_leave(staff_id,role);
                back_status=1;
                break;
            }else if(back_num==2){
                if (strcmp(role,"Head")==0){
                    head_staff_menu(staff_id,role);
                }else{
                    staff_menu(staff_id,role);
                }
                back_status=1;
                break;
            }else{
                printf("The number entered is out of range. Please try again.\n\n");
                back_status=0;
            }
        }while(back_status==0);
    }

}

//check the leave status
void check_leave_status(char* staff_id,char* role){
    int line;
    int i;
    int size=1;
    int check_status=0;
    int selected[100];
    int leave_num=0;

    char back[100];
    int back_num;
    int back_status;

    line=count_txt_line("apply_leave.txt");

    struct leave *checkleave = (struct leave *) malloc (line* sizeof(struct leave));

    read_apply_leave(checkleave);

    for(i=0;i<line;i++){
        if(strcmp(checkleave[i].staffID,staff_id)==0){
            check_status=1;
            break;
        }
    }
    if(check_status==0){
        printf("You have no any leave application.\n");
    }else{
        for(i=0;i<line;i++){
            if(strcmp(checkleave[i].staffID,staff_id)==0){
                selected[leave_num]=i;
                leave_num++;
                printf("\n---------------------------------------------------------------------------------\n");
                printf("%s's Leave Application %d\n",staff_id,leave_num);
                printf("Leave Type: %s\n",checkleave[i].leave_type);
                printf("Leave Date From: %s\n",checkleave[i].from);
                printf("Leave Date To: %s\n",checkleave[i].to);
                printf("Total Days (exclude weekend): %d\n",checkleave[i].first_month_days+checkleave[i].second_month_days);
                printf("Reason: %s\n",checkleave[i].reason);
                printf("Status: %s\n",checkleave[i].status);
                printf("---------------------------------------------------------------------------------\n");
            }
        }
    }
    free(checkleave);

    printf("\n");
    do{
        printf("Would you like to return to the Staff Menu Page? Enter 1 for yes.\n");
        fgets(back,100, stdin);
        back_status = blank_check(back);
        if (back_status==0){
            continue;
        }else if (!number_check(back)){
            printf("Invalid input. Please enter the number.\n\n");
            back_status=0;
        }else if((sscanf(back, "%d", &back_num) != 1)){
            back_status=0;
        }else if(back_num==1){
            if (strcmp(role,"Head")==0){
                head_staff_menu(staff_id,role);
            }else{
                staff_menu(staff_id,role);
            }
            back_status=1;
            break;
        }else{
            printf("Invalid input. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);
}

//check the summary of leave application
void check_leave_summary(char* staff_id, char* role){
    int i;
    int size=1;
    int line;

    char back[100];
    int back_num;
    int back_status;

    line=count_txt_line("leave_summary.txt");
    struct leave_summary *check_summary = (struct leave_summary*) malloc(line * sizeof(struct leave_summary));

    read_leave_summary_file(check_summary);

    //print the leave summary
    printf("\n");
    for(i=0;i<line;i++){
        if(strcmp(check_summary[i].staffID,staff_id)==0){
            printf("+-----------------------+---------+\n");
            printf("| Type of Leave         | Balance |\n");
            printf("+-----------------------+---------+\n");
            printf("| Annual Leave          | %7d |\n", check_summary[i].annual_leave);
            printf("| Compassionate Leave   | %7d |\n", check_summary[i].compassionate_leave);
            printf("| Emergency Leave       | %7d |\n", check_summary[i].emergency_leave);
            printf("| Maternity Leave       | %7d |\n", check_summary[i].maternity_leave);
            printf("| Medical Leave         | %7d |\n", check_summary[i].medical_leave);
            printf("+-----------------------+---------+\n");

        }
    }
    free(check_summary);

    printf("\n");
    do{
        printf("Would you like to return to the Staff Menu Page? Enter 1 for yes.\n");
        fgets(back,100, stdin);
        back_status = blank_check(back);
        if (back_status==0){
            continue;
        }else if (!number_check(back)){
            printf("Invalid input. Please enter the number.\n\n");
            back_status=0;
        }else if((sscanf(back, "%d", &back_num) != 1)){
            back_status=0;
        }else if(back_num==1){
            if (strcmp(role,"Head")==0){
                head_staff_menu(staff_id,role);
            }else{
                staff_menu(staff_id,role);
            }
            back_status=1;
            break;
        }else{
            printf("Invalid input. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);
}
