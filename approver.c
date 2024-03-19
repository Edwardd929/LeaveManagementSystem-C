#include "main.h"
#include "function.h"


//check if the date is valid
char* check_date(char *date){
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
        }else if(month_num<1 || month_num>12){
            printf("Please enter a valid month between 1 and 12.\n\n");
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

//approve or reject leave application
void approve_reject(char* staff_id,char* role){
    char staff_position[100];

    int line,line2,line3,line4,line5;
    int index=0;

    int leave_num=0;
    char* department_txt;

    char select[100];
    int select_status;
    int select_num;

    int approve_reject_leave_index;
    int selected[1000];
    char option[100];
    int option_num;
    int option_status;
    char leave_type[100];

    int true_date_index;
    int limit_date_index;


    char back[100];
    int back_num;
    int back_status;

    int total_leave;

    char department[100];

    int enough=1;

    line=count_txt_line("apply_leave.txt");
    line2=count_txt_line("leave_summary.txt");
    line3=count_txt_line("leave_calendar.txt");
    line4=count_txt_line("department_leave.txt");
    line5=count_txt_line("staff_info.txt");

    struct leave *approve_reject_leave = (struct leave *) malloc (line* sizeof(struct leave));
    struct leave_summary* modify_leave_summary = (struct leave_summary*) malloc(line2 * sizeof(struct leave_summary));
    struct calendar *modify_calendar = (struct calendar *) malloc(line3 * sizeof(struct calendar));
    struct department_leave *modify_department_leave= (struct department_leave *) malloc(line4 * sizeof(struct department_leave));
    struct staff *staff_info = (struct staff *) malloc(line5 * sizeof(struct staff));
    union head_member *search_head_member = (union head_member *) malloc (line5* sizeof(union head_member));

    read_apply_leave(approve_reject_leave);
    read_leave_summary_file(modify_leave_summary);
    read_leave_calendar(modify_calendar);
    read_department_file(modify_department_leave);
    read_staff_file(staff_info);

    //if the role is CEO, find the staff id of head
    if(strcmp(role,"CEO")==0){
        strcpy(staff_position,"Head");
        for (int i=0;i<line5;i++){
            if(strcmp(staff_info[i].staff_position,staff_position)==0){
                strcpy(search_head_member[index].staffID,staff_info[i].staff_id);
                index++;
            }
        }
    //if the role is head, find the staff id of the member of the same department
    }else if(strcmp(role,"Head")==0){
        strcpy(staff_position,"Member");
        for (int i=0;i<line5;i++){
            if(strcmp(staff_id,staff_info[i].staff_id)==0){
                strcpy(department,staff_info[i].department);
            }
        }
        for (int i=0;i<line5;i++){
            if((strcmp(staff_info[i].staff_position,staff_position)==0)&&(strcmp(staff_info[i].department,department)==0)){
                strcpy(search_head_member[index].staffID,staff_info[i].staff_id);
                index++;
            }
        }
    }

    printf("\n\n==Approve/Reject Leave Application==\n");

    for(int i=0;i<line;i++){
        //find the pending leave application
        if(strcmp(approve_reject_leave[i].status,"pending")==0){
            for (int j=0;j<index;j++){
                //display the leave application available for approval or rejection
                if(strcmp(search_head_member[j].staffID,approve_reject_leave[i].staffID)==0){
                    selected[leave_num]=i;
                    leave_num++;
                    printf("\n---------------------------------------------------------------------------------\n");
                    printf("Leave Application %d\n",leave_num);
                    printf("Staff ID: %s\n", approve_reject_leave[i].staffID);
                    printf("Leave Type: %s\n",approve_reject_leave[i].leave_type);
                    printf("Leave Date From: %s\n",approve_reject_leave[i].from);
                    printf("Leave Date To: %s\n",approve_reject_leave[i].to);
                    printf("Total Days (exclude weekend): %d\n",approve_reject_leave[i].first_month_days+approve_reject_leave[i].second_month_days);
                    printf("Reason: %s\n",approve_reject_leave[i].reason);
                    printf("Status: %s",approve_reject_leave[i].status);
                    printf("\n---------------------------------------------------------------------------------\n");
                }
            }
        }
    }

    //if there is no leave for approval or rejection
    if (leave_num==0){
        printf("There are currently no pending leave applications to be approved or rejected.\n");
    }else{
        //get the number
        do{
            printf("Please enter the number of leave application you want to approve or reject: Leave Application ");
            fgets(select,100,stdin);
            select_status=blank_check(select);
            if(select_status==0){
                continue;
            }else if(sscanf(select,"%d",&select_num)!=1){
                printf("Please enter number.\n\n");
                select_status=0;
            }else if(select_num<0 || select_num>leave_num){
                if(leave_num!=1){
                    printf("The number is out of range. Please enter the number between 1 and %d.\n\n",leave_num);
                }else{
                    printf("The number is out of range.\n\n");
                }
                select_status=0;
            }else{
                select_status=1;
            }
        }while(select_status==0);

        //prompt the user to approve or reject
        do{
            printf("\nLeave Application %d has been selected. Press 1 to approve. Press 2 to reject.\n",select_num);
            fgets(option,100,stdin);
            option_status=blank_check(option);
            if(option_status==0){
                continue;
            }else if(sscanf(option,"%d",&option_num)!=1){
                printf("Invalid input. Please enter number.\n\n");
                option_status=0;
            }else if(option_num==1){
                strcpy(option,"approved");
                option_status=1;
            }else if(option_num==2){
                strcpy(option,"rejected");
                option_status=1;
            }else{
                printf("The number is out of range.\n\n");
                option_status=0;
            }
        }while(option_status==0);

        approve_reject_leave_index = selected[select_num-1];

        strcpy(approve_reject_leave[approve_reject_leave_index].status,option);
        strcpy(leave_type,approve_reject_leave[approve_reject_leave_index].leave_type);

        //calculate total days exclude weekends
        total_leave=approve_reject_leave[approve_reject_leave_index].first_month_days+approve_reject_leave[approve_reject_leave_index].second_month_days;

        //if the user wants to approve the leave application
        if(option_num==1){
            for (int i=0;i<line2;i++){
                //deduct the leave balance of the staff id according to how much days he or she applied (exclude weekend)
                if(strcmp(approve_reject_leave[approve_reject_leave_index].staffID,modify_leave_summary[i].staffID)==0){
                    if(strcmp(leave_type, "Annual Leave ")==0){
                        modify_leave_summary[i].annual_leave-=total_leave;
                    }else if(strcmp(leave_type, "Compassionate Leave ")==0){
                        modify_leave_summary[i].compassionate_leave-=total_leave;
                    }else if(strcmp(leave_type, "Emergency Leave ")==0){
                        modify_leave_summary[i].emergency_leave-=total_leave;
                    }else if(strcmp(leave_type, "Maternity Leave ")==0){
                        modify_leave_summary[i].maternity_leave-=total_leave;
                    }else if(strcmp(leave_type, "Medical Leave ")==0){
                        modify_leave_summary[i].medical_leave-=total_leave;
                    }else{
                        printf("Error modifying leave summary text.");
                        return 1;
                    }
                    if(modify_leave_summary[i].annual_leave<0 || modify_leave_summary[i].compassionate_leave<0 || modify_leave_summary[i].emergency_leave<0 ||
                       modify_leave_summary[i].maternity_leave<0 || modify_leave_summary[i].medical_leave<0){
                        printf("The leave can't be approved. Insufficient leave balance.\n");
                        enough=0;
                    }
                }
            }

            for(int i=0;i<line3;i++){
                if(strcmp(approve_reject_leave[approve_reject_leave_index].from,modify_calendar[i].date)==0){
                    true_date_index=i;
                    break;
                }
            }

            limit_date_index=true_date_index+approve_reject_leave[approve_reject_leave_index].days-1;

            //add 1 to the date that the leave application had been applied and be approved by the approver
            for(int i=true_date_index;i<=limit_date_index;i++){
                if(strcmp(leave_type, "Annual Leave ")==0){
                    modify_calendar[i].annual_leave+=1;
                }else if(strcmp(leave_type, "Compassionate Leave ")==0){
                    modify_calendar[i].compassionate_leave+=1;
                }else if(strcmp(leave_type, "Emergency Leave ")==0){
                    modify_calendar[i].emergency_leave+=1;
                }else if(strcmp(leave_type, "Maternity Leave ")==0){
                    modify_calendar[i].maternity_leave+=1;
                }else if(strcmp(leave_type, "Medical Leave ")==0){
                    modify_calendar[i].medical_leave+=1;
                }else{
                    printf("Error modifying leave calendar text.");
                    return 1;
                }
            }

            //find the department of the staff id
            for (int i=0;i<line5;i++){
                if(strcmp(approve_reject_leave[approve_reject_leave_index].staffID,staff_info[i].staff_id)==0){
                        department_txt=staff_info[i].department;
                        break;
                    }
            }

            //add the total days of the approved leave application exclude weekend to the department leave text file
            for(int i=0; i<line4;i++){
                if((strcmp(modify_department_leave[i].department, department_txt)==0)
                    && (strstr(approve_reject_leave[approve_reject_leave_index].from,modify_department_leave[i].month)!=NULL)){
                    if(strcmp(leave_type, "Annual Leave ")==0){
                        modify_department_leave[i].annual_leave+=approve_reject_leave[approve_reject_leave_index].first_month_days;
                        modify_department_leave[i+1].annual_leave+=approve_reject_leave[approve_reject_leave_index].second_month_days;
                    }else if(strcmp(leave_type, "Compassionate Leave ")==0){
                        modify_department_leave[i].compassionate_leave+=approve_reject_leave[approve_reject_leave_index].first_month_days;
                        modify_department_leave[i+1].compassionate_leave+=approve_reject_leave[approve_reject_leave_index].second_month_days;
                    }else if(strcmp(leave_type, "Emergency Leave ")==0){
                        modify_department_leave[i].emergency_leave+=approve_reject_leave[approve_reject_leave_index].first_month_days;
                        modify_department_leave[i+1].emergency_leave+=approve_reject_leave[approve_reject_leave_index].second_month_days;
                    }else if(strcmp(leave_type, "Maternity Leave ")==0){
                        modify_department_leave[i].maternity_leave+=approve_reject_leave[approve_reject_leave_index].first_month_days;
                        modify_department_leave[i+1].maternity_leave+=approve_reject_leave[approve_reject_leave_index].second_month_days;
                    }else if(strcmp(leave_type, "Medical Leave ")==0){
                        modify_department_leave[i].medical_leave+=approve_reject_leave[approve_reject_leave_index].first_month_days;
                        modify_department_leave[i+1].medical_leave+=approve_reject_leave[approve_reject_leave_index].second_month_days;
                    }else{
                        printf("Error modifying department leave text file.");
                        return 1;
                    }
                }
            }
            if(enough==1){
                //save the text file with the updated information
                save_leave_summary(modify_leave_summary);
                save_leave_calendar(modify_calendar);
                save_leave_department(modify_department_leave);

            }

        }
        if(enough==1){
            save_leave_status(approve_reject_leave);
            printf("\nLeave application %d has been successfully %s.\n", select_num,option);
        }

    }

    //free the memory of cleave when it is not needed anymore
    free(approve_reject_leave);
    free(modify_leave_summary);
    free(modify_calendar);
    free(modify_department_leave);
    free(staff_info);

    //prompt the user to enter 1 to back to the approver menu page
    if(leave_num==0 || leave_num==1){
        do{
            printf("\nSince there are no pending leave applications left for approval or rejection, please enter 1 to return to the Approver Menu page.\n");
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
                    head_approver_menu(staff_id,role);
                }else{
                    approver_menu(staff_id,role);
                }
                back_status=1;
                break;
            }else{
                printf("Invalid input. Please try again.\n\n");
                back_status=0;
            }
        }while(back_status==0);
    //prompt the user to enter 1 to approver or reject other leave application and enter 2 to back to the approver menu page
    }else{
        printf("\n");
        do{
            printf("Would you like to approve or reject another leave? Enter 1 for yes or 2 to return to the Approver Menu page.\n");
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
                approve_reject(staff_id,role);
                back_status=1;
                break;
            }else if(back_num==2){
                if (strcmp(role,"Head")==0){
                    head_approver_menu(staff_id,role);
                }else{
                    approver_menu(staff_id,role);
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


//search a date and view the number of staff who applied leave on the specified date
void search_date(char* staff_id,char* role){
    int day;
    int month;
    char* month_word;
    int year;
    char date[11];
    char* date_selected;
    char month_list[12][50]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    int i;
    int line;

    char back[100];
    int back_num;
    int back_status;

    int date_status;

    line=count_txt_line("leave_calendar.txt");
    struct calendar *read_calendar = (struct calendar *) malloc(line * sizeof(struct calendar));
    read_leave_calendar(read_calendar);

    printf("\n\n==Search a Date and View the Number of Staff who Applied Leave on the Specified Date==\n");

    //check if the date entered is valid or the date is weekdays or not
    do{
        date_selected=check_date(date);
        sscanf(date_selected,"%d-%d-%d",&year,&month,&day);
        date_status=weekend_check(day,month);
        if(date_status==1){
            printf("The staff does not work on weekend. Please search another date.\n\n");
        }
    }while(date_status==1);

    month_word=month_list[month-1];
    sprintf(date_selected,"%d%s%d",day,month_word,year);

    //print the number of leaves applied on the selected date
    for(i=0;i<line;i++){
        if(strcmp(date_selected,read_calendar[i].date)==0){
            printf("\nThe number of staffs applied leave on %s :\n\n", read_calendar[i].date);
            printf("+------------------------+---------+\n");
            printf("| Type of Leave           | Number |\n");
            printf("+------------------------+---------+\n");
            printf("| %-23s | %-6d |\n", "Annual Leave", read_calendar[i].annual_leave);
            printf("| %-23s | %-6d |\n", "Compassionate Leave", read_calendar[i].compassionate_leave);
            printf("| %-23s | %-6d |\n", "Emergency Leave", read_calendar[i].emergency_leave);
            printf("| %-23s | %-6d |\n", "Maternity Leave", read_calendar[i].maternity_leave);
            printf("| %-23s | %-6d |\n", "Medical Leave", read_calendar[i].medical_leave);
            printf("+------------------------+---------+\n\n");

        }
    }

    free(read_calendar);

    //prompt the user to enter 1 to view the other date and enter 2 to back to approver menu page
    do{
        printf("Would you like to search for another date to view the number of staff who have applied for leave? Enter 1 for yes or 2 to return to the Approver Menu page.\n");
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
            search_date(staff_id,role);
            back_status=1;
            break;
        }else if(back_num==2){
            if (strcmp(role,"Head")==0){
                head_approver_menu(staff_id,role);
            }else{
                approver_menu(staff_id,role);
            }
            back_status=1;
            break;
        }else{
            printf("The number entered is out of range. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);
}
