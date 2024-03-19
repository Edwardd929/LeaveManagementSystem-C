#include "main.h"
#include "function.h"

//prompt the user to enter the department by typing number
char* get_department(char* name, char* department){
    int department_num;
    int department_status;

    printf("\n");
    do{
        printf(" ------------------------------------------------------- \n");
        printf("| Number |                Department Name               |\n");
        printf("|--------|----------------------------------------------|\n");
        printf("|   1    |      Academic Administration                 |\n");
        printf("|   2    |      Asia Pacific Language Centre            |\n");
        printf("|   3    |      Faculty of Business and Management      |\n");
        printf("|   4    |      Faculty of Computing and Technology     |\n");
        printf("|   5    |      Human Resources                         |\n");
        printf("|   6    |      Operations Management                   |\n");
        printf("|   7    |      School of Foundation Studies            |\n");
        printf("|   8    |      School of Psychology                    |\n");
        printf("|   9    |      Technology Services                     |\n");
        printf(" ------------------------------------------------------- \n\n");

        printf("Please enter the number that represent the department area of %s: ",name);

        fgets(department,100,stdin);

        //blank_check() will return 0 if the user leave it blank
        department_status=blank_check(department);

        //if the user leave it blank, department_status = 0
        if(department_status==0){
            continue;
        //sscanf is use to converet department to department_num which declare as integer, if it cant be convert, it will return 0
        }else if(sscanf(department,"%d",&department_num)!=1){
            printf("Invalid input. Please enter number.\n\n");
            department_status=0;
        }else if(department_num<1 || department_num>9){
            printf("Number out of range. Please enter number between 1-9.\n\n");
            department_status=0;
        }else{
            department_status=1;
        }
    }while(department_status==0);

    switch (department_num){
        case 1:
            strcpy(department,"Academic Administration");
            break;
        case 2:
            strcpy(department,"Asia Pacific Language Centre");
            break;
        case 3:
            strcpy(department,"Faculty of Business and Management");
            break;
        case 4:
            strcpy(department,"Faculty of Computing and Technology");
            break;
        case 5:
            strcpy(department,"Human Resources");
            break;
        case 6:
            strcpy(department,"Operations Management");
            break;
        case 7:
            strcpy(department,"School of Foundation Studies");
            break;
        case 8:
            strcpy(department,"School of Psychology");
            break;
        case 9:
            strcpy(department,"Technology Services");
            break;
    }
    return department;
}


// add new staff information
void new_staff(){
    struct staff add_staff;

    int line;

    int new_staff_id;

    int name_num;
    int name_status;

    int age_num;
    int age_status;

    int email_status;

    int contact_num;
    int contact_status;

    char ans[100];
    char* department;

    int job_title_num;
    int job_title_status;

    int username_num;
    int username_status;

    int password_status;

    char confirm[100];
    int confirm_status;
    int confirm_num;

    char back[100];
    int back_num;
    int back_status;

    int staff_id;

    char admin_login_data[100];

    //count the line of text file and store in line variable
    line=count_txt_line("staff_info.txt");

    //allocate dynamic memory for an the structure read_staff with size of line to avoid wastage of memory
    struct staff* read_staff = (struct staff*) malloc (line* sizeof(struct staff)) ;


    printf("\n===Add New Staff's Information===\n");

    read_staff_file(read_staff);

    //The +2 is used to move the pointer to two positions after the "AP"
    //atoi converts the result to the integer
    staff_id = atoi(strstr(read_staff[line-1].staff_id, "AP") + 2);

    //create a new staff id by adding 1
    new_staff_id=staff_id+1;

    printf("\n");

    //get the name
    do{
        printf("Please enter the name: ");
        fgets(add_staff.name,100, stdin);
        name_status = blank_check(add_staff.name);
        if (name_status!=0){
            name_status=vertical_bar(add_staff.name);
            if (name_status!=0 && (sscanf(add_staff.name, "%d", &name_num)== 1)){
                printf("Invalid input. Please enter alphabetical characters only.\n\n");
                name_status=0;
            }
        }
        if(name_status!=0){
            for(int i=0;i<line;i++){
                if(strcmp(read_staff[i].name,add_staff.name)==0){
                    printf("This name is already associated with another account. Please enter a different name.\n\n");
                    name_status=0;
                    break;
                }
            }
        }
    }while(name_status == 0);

    printf("\n");

    //get the age
    do{
        printf("Please enter the age: ");
        fgets(add_staff.age,100, stdin);
        age_status = blank_check(add_staff.age);
        if (age_status==0){
            continue;
        }else if (!number_check(add_staff.age)) {
            printf("Invalid input. Please enter the number.\n\n");
            age_status=0;
        }else if (sscanf(add_staff.age, "%d", &age_num) != 1) {
            age_status=0;
        }else if(age_num<20 || age_num>90){
            printf("Invalid input. Please enter a valid age in the range between 20-90.\n\n");
            age_status=0;
        }else{
            age_status=1;
        }
    }while(age_status==0);

    printf("\n");

    //get the email
    do{
        printf("Please enter the APU email(which ends with @apu.edu.my): ");
        fgets(add_staff.email,100, stdin);
        email_status = blank_check(add_staff.email);
        if(email_status!=0){
            email_status = vertical_bar(add_staff.email);
            if(email_status!=0){
                email_status=space(add_staff.email);
            }
            if(email_status!=0 && strstr(add_staff.email, "@apu.edu.my") == NULL){
                printf("Invalid Input! Please enter a valid APU email(which ends with @apu.edu.my).\n\n");
                email_status=0;
            }
        }
        if(email_status!=0){
            for(int i=0;i<line;i++){
                if(strcmp(read_staff[i].email,add_staff.email)==0){
                    printf("This email is already associated with another account. Please enter a different email.\n\n");
                    email_status=0;
                    break;
                }
            }
        }
    }while(email_status == 0);

    printf("\n");

    //get the contact number
    do{
        printf("Please enter the contact number without spaces and dash: +60");
        fgets(add_staff.contact_number,100, stdin);
        contact_status = blank_check(add_staff.contact_number);
        if (contact_status==0){
            continue;
        }else if (!number_check(add_staff.contact_number)){
            printf("Invalid input. Please enter the number.\n\n");
            contact_status=0;
        }else if (sscanf(add_staff.contact_number, "%d", &contact_num) != 1) {
            contact_status=0;
        }else if(strlen(add_staff.contact_number) == 9 || strlen(add_staff.contact_number) == 10){
            contact_status=1;
        }else{
            printf("Invalid phone number. Please enter a valid phone number with 9 or 10 digits.\n\n");
            contact_status=0;
        }
        if(contact_status!=0){
            for(int i=0;i<line;i++){
                if(strcmp(read_staff[i].contact_number,add_staff.contact_number)==0){
                    printf("This phone number is already associated with another account. Please enter a different phone number.\n\n");
                    contact_status=0;
                    break;
                }
            }
        }
    }while(contact_status==0);


    strcpy(add_staff.staff_position,"Member");
    department=get_department(add_staff.name,ans);
    strcpy(add_staff.department,department);

    printf("\n");

    //get the job title

    do{
        printf("Please enter the job title: ");
        fgets(add_staff.job_title,100, stdin);
        job_title_status = blank_check(add_staff.job_title);
        if(job_title_status!=0){
            job_title_status=vertical_bar(add_staff.job_title);
            if(job_title_status!=0 &&(sscanf(add_staff.job_title, "%d", &job_title_num)== 1)){
                printf("Please enter a valid job title.\n\n");
                job_title_status=0;
            }
        }
    }while(job_title_status == 0);

    printf("\n");

    //get the username

     do{
        printf("Please enter the username: ");
        fgets(add_staff.username,100, stdin);
        username_status = blank_check(add_staff.username);
        if(username_status!=0){
            username_status = vertical_bar(add_staff.username);
            if(username_status!=0){
                username_status=space(add_staff.username);
            }
            if (username_status!=0 &&(sscanf(add_staff.username, "%d", &username_num)== 1)){
                printf("Please enter a valid username which contains characters.\n\n");
                username_status=0;
            }
        }
        if(username_status!=0){
            for(int i=0;i<line;i++){
                if(strcmp(read_staff[i].username,add_staff.username)==0){
                    printf("This username is already associated with another account. Please enter a different username.\n\n");
                    username_status=0;
                    break;
                }
            }
        }
        if(username_status!=0){
            FILE* admin_login_file = fopen("admin_login.txt", "r");

            //read login.txt line by line
            while (fgets(admin_login_data, 100, admin_login_file) != NULL) {
                //spilt the lines by '|'
                char* txtUsername = strtok(admin_login_data, " | ");
                char* txtPassword = rstrip(strtok(NULL, " | "));

                //compare if the user input is same with the txtUsername in admin file
                if (strcmp(txtUsername, add_staff.username) == 0) {
                    printf("This username is already associated with admin account. Please enter a different username.\n\n");
                    username_status=0;
                    break;
                }
            }
        }
    }while(username_status == 0);

    printf("\n");

    //get the password
     do{
        printf("Please enter the password (must be between 8-30 characters long, and should not include '|' or spaces): ");
        fgets(add_staff.password,100, stdin);
        password_status = blank_check(add_staff.password);
        if(password_status!=0){
            password_status = vertical_bar(add_staff.password);
            if(password_status!=0){
                password_status=space(add_staff.password);
            }
            if(password_status!=0 && (strlen(add_staff.password)<8 || strlen(add_staff.password)>30)){
                printf("Invalid input. Password must be between 8-30 characters long.\n\n");
                password_status = 0;
            }
        }
    }while(password_status == 0);

    // Display the staff information entered for final confirmation
    printf("\nPlease check that the following staff information is correct before submitting:\n");
    printf("\n---------------------------------------------------------------------------------\n");
    printf("Staff ID: AP%d\n",new_staff_id);
    printf("Name: %s\n", add_staff.name);
    printf("Age: %s\n", add_staff.age);
    printf("Email: %s\n", add_staff.email);
    printf("Contact number: +60%s\n", add_staff.contact_number);
    printf("Staff position: %s\n", add_staff.staff_position);
    printf("Department: %s\n", add_staff.department);
    printf("Job title: %s\n", add_staff.job_title);
    printf("Username: %s\n", add_staff.username);
    printf("Password: %s\n", add_staff.password);
    printf("\n---------------------------------------------------------------------------------\n");

    // Ask the user to confirm the information
    do{
        printf("\nPlease confirm that the staff information above is correct by entering 1 to save it.\nIf you need to make any changes, enter 2: ");
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
            printf("\nThe new staff info has been successfully added.\n\n");
            printf("The new staff's leave balance will be set to default value. Please update the leave balance if necessary.\n\n");
            confirm_status=1;
        }else if(confirm_num==2){
            printf("\nPlease reenter the correct information.\n");
            confirm_status=1;
            new_staff();
        }else{
            printf("Invalid input. Please enter 1 to save the staff information or enter 2 to make changes.\n\n");
            confirm_status=0;
        }

    }while(confirm_status==0);

    //if the user had confirmed by typing 1
    if(confirm_num==1){
        //open staff_info.txt using append mode
        FILE* staff_info_file = fopen("staff_info.txt", "a");

        // move the pointer to the end of the file
        fseek(staff_info_file, 0, SEEK_END);

        //write the new staff information into the text file
        fprintf(staff_info_file, "AP%d | %s | %s | %s | +60%s | %s | %s | %s | %s | %s\n",new_staff_id,add_staff.name,add_staff.age,
                    add_staff.email,add_staff.contact_number,add_staff.staff_position,add_staff.department,add_staff.job_title,add_staff.username,add_staff.password);

        fclose(staff_info_file);

        //open staff_info.txt using append mode
        FILE* staff_leave_write = fopen("leave_summary.txt", "a");

         // move the pointer to the end of the file
        fseek(staff_leave_write, 0, SEEK_END);

        //write the leave information of the new staff into the text file
        fprintf(staff_leave_write, "AP%d | annual leave:5 | compassionate leave:5 | emergency leave:5 | maternity leave:5 | medical leave:5\n",
                    new_staff_id);

        fclose(staff_leave_write);

        //ask the user to enter 1 to add new staff's information and 2 to back to Admin Menu page
        do{
            printf("Would you like to add another staff's information? Enter 1 for yes or 2 to return to the Admin Menu page.\n");
            fgets(back,100, stdin);
            back_status = blank_check(back);
            if (back_status==0){
                continue;
            }else if (!number_check(back)){
                printf("Invalid input. Please enter number.\n\n");
                back_status=0;
            }else if((sscanf(back, "%d", &back_num) != 1)){
                back_status=0;
            }else if(back_num==1){
                new_staff();
                back_status=1;
                break;
            }else if(back_num==2){
                admin_menu();
                back_status=1;
                break;
            }else{
                printf("The number entered is out of range. Please try again.\n\n");
                back_status=0;
            }
        }while(back_status==0);
    }
    free(read_staff);
}

//update leave balance
void update_leave(){
    int line,line2;
    char staff_id[100];
    int staff_id_status;

    char name[100];
    int name_status;

    int selected;

    char selected_update[100];
    int selected_update_num;
    int selected_status;

    char update_num[100];
    int update_status;
    int update_num2;

    char back[100];
    int back_num;
    int back_status;

    line=count_txt_line("leave_summary.txt");
    line2=count_txt_line("staff_info.txt");

    struct leave_summary* read_leave_summary = (struct leave_summary*) malloc(line * sizeof(struct leave_summary));
    struct staff* read_staff = (struct staff*) malloc (line2* sizeof(struct staff)) ;

    read_leave_summary_file(read_leave_summary);
    read_staff_file(read_staff);

    printf("\n===Update Leave Balance===\n");

    //get the name or staff id
    printf("\n");
    do{
        printf("Please provide the name of the staff whose leave balance needs to be updated. If you have the staff ID, press '1' to enter the staff ID instead: ");
        fgets(name,100, stdin);
        name_status = blank_check(name);

        //if the user type 1
        if((strcmp(name,"1"))==0){
            do{
                printf("\nPlease provide the staff id of the staff whose leave balance needs to be updated: ");
                fgets(staff_id,100, stdin);
                staff_id_status = blank_check(staff_id);
                if (staff_id_status!=0){
                    for (int i=0; i<line; i++){
                        // to find the same staffID by looping through the struct
                        if(strcmp(staff_id,read_leave_summary[i].staffID)==0){
                            selected=i;
                            staff_id_status=1;
                            break;
                        }else{
                            staff_id_status=0;
                        }
                    }
                    if(staff_id_status==0){
                        printf("Staff ID not found. Please enter a valid staff ID starts with 'AP' followed by numbers.\n\n");
                    }
                }
            }while(staff_id_status==0);
        //if the user type name
        }else if(name_status!=0){
            for (int i=0; i<line2; i++){
                //to find the same name by looping through the struct
                if(strcmp(name,rstrip(read_staff[i].name))==0){
                    selected=i;
                    name_status=1;
                    break;
                }else{
                    name_status=0;
                }
            }
            if (name_status==0){
                printf("Name not found. Please enter a valid name.\n\n");
            }
        }
    }while(name_status == 0);

    printf("\n---------------------------------------------------------------------------------\n");
    printf("Current %s's Leave Balance", rstrip(read_staff[selected].name));
    printf("\n---------------------------------------------------------------------------------\n");
    printf("\nAvailable Annual Leave: %d\n",read_leave_summary[selected].annual_leave);
    printf("Available Compassionate Leave: %d\n",read_leave_summary[selected].compassionate_leave);
    printf("Available Emergency Leave: %d\n",read_leave_summary[selected].emergency_leave);
    printf("Available Maternity Leave: %d\n",read_leave_summary[selected].maternity_leave);
    printf("Available Medical Leave: %d\n",read_leave_summary[selected].medical_leave);
    printf("\n---------------------------------------------------------------------------------\n");

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

    //prompt the user to choose the type of leave by entering number
    do{
        printf("Please enter your choice by typing number: ");
        fgets(selected_update,100,stdin);
        selected_status = blank_check(selected_update);
        if (selected_status == 0){
            continue;
        }else if (!number_check(selected_update)){
            printf("Invalid input. Please enter number.\n\n");
            selected_status=0;
        }else if((sscanf(selected_update, "%d", &selected_update_num) != 1)){
            selected_status=0;
        }else if(selected_update_num>0 && selected_update_num<6){
            selected_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n\n");
            selected_status=0;
        }
    }while(selected_status==0);

    //prompt the user to enter the new balance
    do{
        printf("Please enter the new balance: ");
        fgets(update_num,100, stdin);
        update_status = blank_check(update_num);
        if (update_status==0){
            continue;
        }else if (!number_check(update_num)){
            printf("Invalid input. Please enter valid number.\n\n");
            update_status=0;
        }else if (sscanf(update_num, "%d", &update_num2) != 1) {
            update_status=0;
        //the user cant enter the negative balance
        }else if(update_num2<0){
            printf("Invalid input. Please enter a valid balance.\n\n");
            update_status=0;
        }else{
            update_status=1;
        }
    }while(update_status==0);

    switch (selected_update_num){
        case 1:
            read_leave_summary[selected].annual_leave=update_num2;
            break;
        case 2:
            read_leave_summary[selected].compassionate_leave=update_num2;
            break;
        case 3:
            read_leave_summary[selected].emergency_leave=update_num2;
            break;
        case 4:
            read_leave_summary[selected].maternity_leave=update_num2;
            break;
        case 5:
            read_leave_summary[selected].medical_leave=update_num2;
            break;
    }

    //Save the updated leave balance in the text file
    save_leave_summary(read_leave_summary);

    printf("\n");
    printf("The selected leave balance has been successfully updated.\n\n");

    //ask the user to enter 1 to update another staff's leave balance and 2 to back to Admin Menu page
    do{
        printf("Would you like to update another staff's leave balance? Enter 1 for yes or 2 to return to the Admin Menu page.\n");
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
            update_leave();
            back_status=1;
            break;
        }else if(back_num==2){
            admin_menu();
            back_status=1;
            break;
        }else{
            printf("The number entered is out of range. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);

    //free the dynamic memory block
    free(read_leave_summary);
    free(read_staff);
}

//search staff's leave information
void search_leave(){

    int line,line2;

    char staff_id[100];
    int staff_id_status;

    char name[100];
    int name_status;

    int name_len;
    char* name_end;

    int selected;

    char back[100];
    int back_num;
    int back_status;

    printf("\n===Search for Staff's Leave Information===\n");

    //count the line of text file
    line=count_txt_line("leave_summary.txt");
    line2=count_txt_line("staff_info.txt");

    //allocate dynamic memory for an the structure staff_info with size of line of text file to avoid wastage of memory
    struct leave_summary* read_leave_summary = (struct leave_summary*) malloc(line * sizeof(struct leave_summary));
    struct staff* read_staff = (struct staff*) malloc (line2* sizeof(struct staff)) ;

    //read the contents of text file and store in respective struct
    read_leave_summary_file(read_leave_summary);
    read_staff_file(read_staff);

    printf("\n");

    //get the name or staff id
    do{
        printf("Please provide the name of the staff to search for leave information. If you have the staff ID, press '1' to enter the staff ID instead: ");
        fgets(name,100, stdin);
        name_status = blank_check(name);
        //if the user type 1 to enter staff ID
        if((strcmp(name,"1"))==0){
            do{
                printf("\nPlease enter staff id to update leave balance: ");
                fgets(staff_id,100, stdin);
                staff_id_status = blank_check(staff_id);
                if (staff_id_status!=0){
                    for (int i=0; i<line; i++){
                        //if the staff ID can be found in read_leave_summary struct
                        if(strcmp(staff_id,read_leave_summary[i].staffID)==0){
                            selected=i;
                            staff_id_status=1;
                            break;
                        }else{
                            staff_id_status=0;
                        }
                    }
                    //if the staff ID cannot be found in read_leave_summary struct
                    if(staff_id_status==0){
                        printf("Staff ID not found. Please enter a valid staff ID starts with 'AP' followed by numbers.\n\n");
                    }
                }
            }while(staff_id_status==0);
        //if the user type staff's name
        }else if(name_status!=0){
            for (int i=0; i<line2; i++){
                //if the name can be found in read_staff struct
                if(strcmp(name,rstrip(read_staff[i].name))==0){
                    selected=i;
                    name_status=1;
                    break;
                }else{
                    name_status=0;
                }
            }
            //if the name cannot be found in read_staff struct
            if (name_status==0){
                printf("Name not found. Please enter a valid name.\n\n");
            }
        }
    }while(name_status == 0);

    printf("\n");
    printf("+-------------------------------------------------------------------+\n");
    printf(" %s's Leave Information \n", rstrip(read_staff[selected].name));
    printf("+------------+---------------+------------+------------+------------+\n");
    printf("| Annual     | Compassionate | Emergency  | Maternity  | Medical    |\n");
    printf("+------------+---------------+------------+------------+------------+\n");
    printf("| %-10d | %-13d | %-10d | %-10d | %-10d |\n",
            read_leave_summary[selected].annual_leave,
            read_leave_summary[selected].compassionate_leave,
            read_leave_summary[selected].emergency_leave,
            read_leave_summary[selected].maternity_leave,
            read_leave_summary[selected].medical_leave);
    printf("+------------+---------------+------------+------------+------------+\n");
    printf("\n");


    //ask the user to enter 1 to search another staff's leave information and 2 to back to Admin Menu page
    do{
        printf("Would you like to search another staff's leave information? Enter 1 for yes or 2 to return to the Admin Menu page.\n");
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
            back_status=1;
            search_leave();
            break;
        }else if(back_num==2){
            admin_menu();
            back_status=1;
            break;
        }else{
            printf("The number entered is out of range. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);

    free(read_leave_summary);
    free(read_staff);
}

//generate monthly report for school or department
void generate_report(){

    int line2,line3,line4;
    char choice[100];
    int choice_num;
    int choice_status;

    char ans[100];
    char* department;

    char name[100];

    char month_choice[100];
    int month_choice_num;
    int month_choice_status;

    char title[300];
    FILE* monthly_report;

    int selected;
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int day_count=0;
    int total_annual_leave=0;
    int total_compassionate_leave=0;
    int total_emergency_leave=0;
    int total_maternity_leave=0;
    int total_medical_leave=0;

    int total_leave;
    float average_total_leave;

    double average_annual_leave=0;
    double average_compassionate_leave=0;
    double average_emergency_leave=0;
    double average_maternity_leave=0;
    double average_medical_leave=0;

    char back[100];
    int back_num;
    int back_status;

    char every_line[255];

    char month1[100];
    char month2[100];
    int day1,day2;
    int month_num1,month_num2;
    int total;
    int largest;
    char selected_staff_id[100][100];
    int same=0;


    //count the line for each text file
    line2=count_txt_line("department_leave.txt");
    line3=count_txt_line("apply_leave.txt");
    line4=count_txt_line("staff_info.txt");

    //allocate dynamic memory for an the structure staff_info with size of text file line to avoid wastage of memory
    struct department_leave* read_department_leave = (struct department_leave*) malloc (line2* sizeof(struct department_leave)) ;
    struct department_leave* read_total_leave = (struct department_leave*) malloc (line2* sizeof(struct department_leave)) ;
    struct leave *sleave = (struct leave *) malloc (line3* sizeof(struct leave));
    struct staff *staff_info = (struct staff *) malloc(line4 * sizeof(struct staff));
    struct staff_leave *staff_leave = (struct staff_leave *) malloc(100 * sizeof(struct staff_leave));

    printf("\n ===Generate monthly report(txt file)===\n\n");

    //prompt the user to choose the monthly report for department or school by typing number
    do{
        printf("1. Monthly Report for Department\n");
        printf("2. Monthly Report for School\n");
        printf("Please enter your choice by typing number: ");
        fgets(choice,100,stdin);
        choice_status=blank_check(choice);
        if (choice_status==0){
            continue;
        }else if(sscanf(choice,"%d",&choice_num)!=1){
            printf("Invalid input. Please enter number.\n\n");
            choice_status=0;
        }else if(choice_num==1 || choice_num==2){
            choice_status=1;
        }else{
            printf("Number is out of range. Please enter number between 1-2.\n\n");
            choice_status=0;
        }
    }while(choice_status==0);


    //if the user choose monthly report for department by typing 1
    if(choice_num==1){
        strcpy(name,"monthly report");
        printf("\n\n");
        //ask the user to choose a department
        department=get_department(name,ans);
        //replace the space between the department sentence with '_' to use as the title of text file
        replace_word(department,' ','_');
    }

    //prompt the user to enter month by typing number
    do{
        printf("\n1. January\n");
        printf("2. February\n");
        printf("3. March\n");
        printf("4. April\n");
        printf("5. May\n");
        printf("6. June\n");
        printf("7. July\n");
        printf("8. August\n");
        printf("9. September\n");
        printf("10. October\n");
        printf("11. November\n");
        printf("12. December\n");
        printf("Please enter the month by typing number: ");
        fgets(month_choice,100,stdin);
        month_choice_status=blank_check(month_choice);
        if(month_choice_status==0){
            continue;
        }else if(sscanf(month_choice,"%d",&month_choice_num)!=1){
            printf("Invalid input. Please enter number.\n\n");
            month_choice_status=0;
        }else if(month_choice_num<1 || month_choice_num>12){
            printf("Number is out of range. Please enter number between 1-12.\n\n");
            month_choice_status=0;
        }else{
           month_choice_status=1;
        }
    }while(month_choice_status==0);

    read_apply_leave(sleave);

    int staff=0;
    same=0;
    largest=0;
    for(int i=0;i<line3;i++){
        if(strcmp(sleave[i].status,"approved")==0){
            sscanf(sleave[i].from, "%d%s",&day1,month1);
            sscanf(sleave[i].to, "%d%s",&day2,month2);
            month_num1=month_to_num(month1);
            month_num2=month_to_num(month2);
            if(month_num1==month_choice_num){
                total=sleave[i].first_month_days;
                strcpy(staff_leave[staff].staff_id,sleave[i].staffID);
                staff_leave[staff].total=total;
                staff++;
            }else if(month_num2==month_choice_num){
                total=sleave[i].second_month_days;
                strcpy(staff_leave[staff].staff_id,sleave[i].staffID);
                staff_leave[staff].total=total;
                staff++;
            }

            if(month_num1==month_choice_num || month_num2==month_choice_num){
                for (int j=0; j<staff-1;j++) {
                    if (strcmp(sleave[i].staffID, staff_leave[j].staff_id) == 0) {
                        total += staff_leave[j].total;
                    }
                }
                // Use >= to include the case where there are multiple staff IDs with the largest leave
                if(total>=largest){
                    // Reset the array if a new largest value is found
                    if(total>largest){
                        largest=total;
                        same = 0;
                    }
                    // Store the staff ID in the array
                    strcpy(selected_staff_id[same], sleave[i].staffID);
                    same++;
                }
            }

        }
    }


    //if the user choose for school monthly report by typing 2
    if(choice_num==2){
        department="School";
        //generate the title for text file
        switch (month_choice_num){
            case 1:
                strcpy(title,"January_school_report.txt");
                strcpy(month_choice,"January");
                break;
            case 2:
                strcpy(title,"February_school_report.txt");
                strcpy(month_choice,"February");
                break;
            case 3:
                strcpy(title,"March_school_report.txt");
                strcpy(month_choice,"March");
                break;
            case 4:
                strcpy(title,"April_school_report.txt");
                strcpy(month_choice,"April");
                break;
            case 5:
                strcpy(title,"May_school_report.txt");
                strcpy(month_choice,"May");
                break;
            case 6:
                strcpy(title,"June_school_report.txt");
                strcpy(month_choice,"June");
                break;
            case 7:
                strcpy(title,"July_school_report.txt");
                strcpy(month_choice,"July");
                break;
            case 8:
                strcpy(title,"August_school_report.txt");
                strcpy(month_choice,"August");
                break;
            case 9:
                strcpy(title,"September_school_report.txt");
                strcpy(month_choice,"September");
                break;
            case 10:
                strcpy(title,"October_school_report.txt");
                strcpy(month_choice,"October");
                break;
            case 11:
                strcpy(title,"November_school_report.txt");
                strcpy(month_choice,"November");
                break;
            case 12:
                strcpy(title,"December_school_report.txt");
                strcpy(month_choice,"December");
                break;
        }


        read_department_file(read_total_leave);
        //calculate the total leave for each leave type by looping through the struct
        for(int i=0;i<line2;i++){
            if(strcmp(read_total_leave[i].month,month_choice)==0){
                total_annual_leave+=read_total_leave[i].annual_leave;
                total_compassionate_leave+=read_total_leave[i].compassionate_leave;
                total_emergency_leave+=read_total_leave[i].emergency_leave;
                total_maternity_leave+=read_total_leave[i].maternity_leave;
                total_medical_leave+=read_total_leave[i].medical_leave;
            }
        }

        //set the day_count to the total day of the selected month
        day_count=month_days[month_choice_num-1];

       //calculate the total leave
        total_leave=total_annual_leave+total_compassionate_leave+total_emergency_leave+total_maternity_leave+total_medical_leave;

        //calculate the average leave
        average_total_leave= (float)total_leave/day_count;
        average_annual_leave=(float)total_annual_leave/day_count;
        average_compassionate_leave=(float)total_compassionate_leave/day_count;
        average_emergency_leave=(float)total_emergency_leave/day_count;
        average_maternity_leave=(float)total_maternity_leave/day_count;
        average_medical_leave=(float)total_medical_leave/day_count;


    }else if(choice_num==1){
        //generate the title for the department text file
        switch (month_choice_num){
            case 1:
                sprintf(title, "%s_%s_report.txt", "January", department);
                strcpy(month_choice,"January");
                break;
            case 2:
                sprintf(title, "%s_%s_report.txt", "February", department);
                strcpy(month_choice,"February");
                break;
            case 3:
                sprintf(title, "%s_%s_report.txt", "March", department);
                strcpy(month_choice,"March");
                break;
            case 4:
                sprintf(title, "%s_%s_report.txt", "April", department);
                strcpy(month_choice,"April");
                break;
            case 5:
                sprintf(title, "%s_%s_report.txt", "May", department);
                strcpy(month_choice,"May");
                break;
            case 6:
                sprintf(title, "%s_%s_report.txt", "June", department);
                strcpy(month_choice,"June");
                break;
            case 7:
                sprintf(title, "%s_%s_report.txt", "July", department);
                strcpy(month_choice,"July");
                break;
            case 8:
                sprintf(title, "%s_%s_report.txt", "August", department);
                strcpy(month_choice,"August");
                break;
            case 9:
                sprintf(title, "%s_%s_report.txt", "September", department);
                strcpy(month_choice,"September");
                break;
            case 10:
                sprintf(title, "%s_%s_report.txt", "October", department);
                strcpy(month_choice,"October");
                break;
            case 11:
                sprintf(title, "%s_%s_report.txt", "November", department);
                strcpy(month_choice,"November");
                break;
            case 12:
                sprintf(title, "%s_%s_report.txt", "December", department);
                strcpy(month_choice,"December");
                break;
        }

        //change back the department name by replace the '_' to space again
        replace_word(department,'_',' ');


        //read the department_leave.txt and store in read_department_leave struct
        read_department_file(read_department_leave);

        //find the same month and same department by looping through the struct
        for(int i=0;i<line2;i++){
            if((strcmp(rstrip(read_department_leave[i].department),department)==0) && (strcmp(read_department_leave[i].month,month_choice)==0)){
                selected=i;
            }
        }

        //set the day_count to the total day of the selected month
        day_count=month_days[month_choice_num-1];

        //calculate total leave and average leave for each leave type
        total_annual_leave=read_department_leave[selected].annual_leave;
        average_annual_leave=(float)total_annual_leave/day_count;

        total_compassionate_leave=read_department_leave[selected].compassionate_leave;
        average_compassionate_leave=(float)total_compassionate_leave/day_count;

        total_emergency_leave=read_department_leave[selected].emergency_leave;
        average_emergency_leave=(float)total_emergency_leave/day_count;

        total_maternity_leave=read_department_leave[selected].maternity_leave;
        average_maternity_leave=(float)total_maternity_leave/day_count;

        total_medical_leave=read_department_leave[selected].medical_leave;
        average_medical_leave=(float)total_medical_leave/day_count;

        //calculate total leave and average leave
        total_leave=total_annual_leave+total_compassionate_leave+total_emergency_leave+total_maternity_leave+total_medical_leave;
        average_total_leave=(float)total_leave/day_count;
    }


    //create the text file according to the name of title
    //open and write the leave statistics into the text file
    monthly_report=fopen(title,"w");
    fprintf(monthly_report, "+--------------------------------------------------------------------------------------------------+\n");
    fprintf(monthly_report, " %s Monthly Report on %s                                                            \n", department,month_choice);
    fprintf(monthly_report, "+--------------------------------------------------------------------------------------------------+\n");
    fprintf(monthly_report, "|         Leave Type          | Total Number of Staff that Applied Leave | Average Leaves Per Month|\n");
    fprintf(monthly_report, "+-----------------------------+------------------------------------------+-------------------------+\n");
    fprintf(monthly_report, "| Total Leave Applied         | %-41d| %-24f|\n", total_leave, average_total_leave);
    fprintf(monthly_report, "| Total Annual Leave Applied  | %-41d| %-24f|\n", total_annual_leave, average_annual_leave);
    fprintf(monthly_report, "| Total Compassionate Applied | %-41d| %-24f|\n", total_compassionate_leave, average_compassionate_leave);
    fprintf(monthly_report, "| Total Emergency Applied     | %-41d| %-24f|\n", total_emergency_leave, average_emergency_leave);
    fprintf(monthly_report, "| Total Maternity Applied     | %-41d| %-24f|\n", total_maternity_leave, average_maternity_leave);
    fprintf(monthly_report, "| Total Medical Applied       | %-41d| %-24f|\n", total_medical_leave, average_medical_leave);
    fprintf(monthly_report, "+-----------------------------+------------------------------------------+-------------------------+\n\n");

    if(choice_num==2){
        if(same!=0){
            fprintf(monthly_report,"During %s, the employee who took the highest number of leaves was %d days, and the leave was taken by:\n\n",month_choice,largest);
            for(int i=0;i<same;i++){
                fprintf(monthly_report,"%s | ",selected_staff_id[i]);
                read_staff_file(staff_info);
                for(int j=0;j<line4;j++){
                    if(strcmp(selected_staff_id[i],staff_info[j].staff_id)==0){
                        fprintf(monthly_report,"Name: %s | ",staff_info[j].name);
                        fprintf(monthly_report,"Department: %s\n",staff_info[j].department);
                    }
                }
            }
        }else{
            fprintf(monthly_report,"There's no staff who apply leave on this month.\n");
        }
    }

    fclose(monthly_report);

    //deallocate the dynamic memory block
    free(read_total_leave);
    free(read_department_leave);
    free(sleave);
    free(staff_info);
    free(staff_leave);

    printf("\nThe %s report for %s has been successfully generated and saved to the text file named '%s'.\n\n",month_choice,department,title);
    printf("Here are the contents of '%s':\n\n",title);

    //open and read the text file
    FILE* read_report=fopen(title,"r");
    if(read_report==NULL){
        printf("Error: Could not open the file.\n");
        return;
    }

    //print the contents of the text file line by line
    while (fgets(every_line, 255, read_report) != NULL) {
        printf("%s", every_line);
    }

    fclose(read_report);

    printf("\n");
    //ask the user to enter 1 to generate another monthly report and 2 to back to Admin Menu page
    do{
        printf("\nWould you like to generate another report? Enter 1 for yes or 2 to return to the Admin Menu page.\n");
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
            generate_report();
            back_status=1;
            break;
        }else if(back_num==2){
            admin_menu();
            back_status=1;
            break;
        }else{
            printf("The number entered is out of range. Please try again.\n\n");
            back_status=0;
        }
    }while(back_status==0);

}

