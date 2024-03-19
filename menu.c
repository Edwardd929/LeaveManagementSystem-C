
#include "main.h"
#include "function.h"


void login_menu() {
	char ans[100];
	int ans_value;
	int ans_status;

    printf("\n\n");
	printf(" -------------------------------------\n");
    printf("              Main Page               \n");
    printf(" -------------------------------------\n");

    printf("1. Login\n");
    printf("2. Exit \n");

	do{
        printf("Please enter your choice by typing number: ");
        fgets(ans,100,stdin);
        ans_status=blank_check(ans);
        if (ans_status==0) {
            continue;
        }else if(sscanf(ans,"%d",&ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            ans_status=0;
        }else if(ans_value == 1) {
            ans_status=1;
            check_username();
            break;
        }else if (ans_value == 2) {
            printf("Thank you for using the system. Goodbye!\n");
            exit(0);
            break;
        }else{
            printf("Number out of range. Please enter number between 1-2.\n\n");
            ans_status=0;
        }
	}while(ans_status==0);
}

void admin_menu(){
    int admin_ans_value;
    char admin_ans[100];
    int admin_ans_status;
    printf("\n");
	printf(" -------------------------------------\n");
    printf("            Admin User Menu           \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Add New Staff Information                   |\n");
    printf("| 2. Update the Leave Balance                    |\n");
    printf("| 3. Search a Staff's Leave Information          |\n");
    printf("| 4. Generate Monthly Report                     |\n");
    printf("| 5. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");
    do{
        printf("Please enter your choice by typing number: ");
        fgets(admin_ans,100,stdin);
        admin_ans_status=blank_check(admin_ans);
        if (admin_ans_status ==0){
            continue;
        }else if(sscanf(admin_ans,"%d",&admin_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            admin_ans_status=0;
        }else if(admin_ans_value==1){
            new_staff();
            admin_ans_status=1;
        }else if(admin_ans_value==2){
            update_leave();
            admin_ans_status=1;
        }else if(admin_ans_value==3){
            search_leave();
            admin_ans_status=1;
        }else if(admin_ans_value==4){
            generate_report();
            admin_ans_status=1;
        }else if(admin_ans_value==5){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the main page.\n\nk");
            login_menu();
            admin_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n\n");
            admin_ans_status=0;
        }
    }while(admin_ans_status==0);
}


void staff_menu(char* staff_id, char* role){
    int staff_ans_value;
    char staff_ans[100];
    int staff_ans_status;

    printf("\n");
	printf(" -------------------------------------\n");
    printf("            Staff User Menu           \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Apply Leave                                 |\n");
    printf("| 2. Cancel Leave                                |\n");
    printf("| 3. Check the leave status                      |\n");
    printf("| 4. Check the summary of leave information      |\n");
    printf("| 5. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");

    do{
        printf("Please enter your choice by typing number: ");
        fgets(staff_ans,100,stdin);
        staff_ans_status=blank_check(staff_ans);
        if (staff_ans_status ==0){
            continue;
        }else if(sscanf(staff_ans,"%d",&staff_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            staff_ans_status=0;
        }else if(staff_ans_value==1){
            apply_leave(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==2){
            cancel_leave(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==3){
            check_leave_status(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==4){
            check_leave_summary(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==5){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the main page.\n");
            login_menu();
            staff_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n");
            staff_ans_status=0;
        }
    }while(staff_ans_status==0);
}

void approver_menu(char* staff_id, char* role){
    int approver_ans_value;
    char approver_ans[100];
    int approver_ans_status;

    printf("\n");
	printf(" -------------------------------------\n");
    printf("           Approver User Menu         \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Approve/ Reject Leave Application           |\n");
    printf("| 2. Search a date and view                      |\n");
    printf("|    the number of staff who applied leave       |\n");
    printf("| 3. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");

    do{
        printf("Please enter your choice by typing number: ");
        fgets(approver_ans,100,stdin);
        approver_ans_status=blank_check(approver_ans);
        if (approver_ans_status ==0){
            continue;
        }else if(sscanf(approver_ans,"%d",&approver_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            approver_ans_status=0;
        }else if(approver_ans_value==1){
            approve_reject(staff_id,role);
            approver_ans_status=1;
        }else if(approver_ans_value==2){
            search_date(staff_id,role);
            approver_ans_status=1;
        }else if(approver_ans_value==3){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the main page.\n");
            login_menu();
            approver_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n");
            approver_ans_status=0;
        }
    }while(approver_ans_status==0);
}

void head_staff_menu(char* staff_id,char* role){
    int staff_ans_value;
    char staff_ans[100];
    int staff_ans_status;

    printf("\n");
	printf(" -------------------------------------\n");
    printf("            Staff User Menu           \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Apply Leave                                 |\n");
    printf("| 2. Cancel Leave                                |\n");
    printf("| 3. Check the leave status                      |\n");
    printf("| 4. Check the summary of leave information      |\n");
    printf("| 5. Switch to Leave Approval                    |\n");
    printf("| 6. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");

    do{
        printf("Please enter your choice by typing number: ");
        fgets(staff_ans,100,stdin);
        staff_ans_status=blank_check(staff_ans);
        if (staff_ans_status ==0){
            continue;
        }else if(sscanf(staff_ans,"%d",&staff_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            staff_ans_status=0;
        }else if(staff_ans_value==1){
            apply_leave(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==2){
            cancel_leave(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==3){
            check_leave_status(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==4){
            check_leave_summary(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==5){
            head_approver_menu(staff_id,role);
            staff_ans_status=1;
        }else if(staff_ans_value==6){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the mian page.\n");
            login_menu();
            staff_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n");
            staff_ans_status=0;
        }
    }while(staff_ans_status==0);
}

void head_approver_menu(char* staff_id,char* role){
    int approver_ans_value;
    char approver_ans[100];
    int approver_ans_status;

    printf("\n");
	printf(" -------------------------------------\n");
    printf("           Approver User Menu         \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Approve/ Reject Leave Application           |\n");
    printf("| 2. Search a date and view                      |\n");
    printf("|    the number of staff who applied leave       |\n");
    printf("| 3. Switch to Leave Applicant                   |\n");
    printf("| 4. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");

    do{
        printf("Please enter your choice by typing number: ");
        fgets(approver_ans,100,stdin);
        approver_ans_status=blank_check(approver_ans);
        if (approver_ans_status ==0){
            continue;
        }else if(sscanf(approver_ans,"%d",&approver_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            approver_ans_status=0;
        }else if(approver_ans_value==1){
            approve_reject(staff_id,role);
            approver_ans_status=1;
        }else if(approver_ans_value==2){
            search_date(staff_id,role);
            approver_ans_status=1;
        }else if(approver_ans_value==3){
            head_staff_menu(staff_id,role);
            approver_ans_status=1;
        }else if(approver_ans_value==4){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the main page.\n");
            login_menu();
            approver_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n");
            approver_ans_status=0;
        }
    }while(approver_ans_status==0);
}


void head_menu(char* staff_id,char* role){
    int head_ans_value;
    char head_ans[100];
    int head_ans_status;
    char clear_ans[100];

    printf("\n");
	printf(" -------------------------------------\n");
    printf("           Role Selection             \n");
    printf(" -------------------------------------\n");
    printf("\n");
    printf(" ------------------------------------------------ \n");
    printf("| 1. Leave Applicant                             |\n");
    printf("| 2. Leave Approval                              |\n");
    printf("| 3. Log Out                                     |\n");
    printf(" ------------------------------------------------ \n\n");


    do{
        printf("Please enter your choice by typing number: ");
        fgets(head_ans,100,stdin);
        head_ans_status=blank_check(head_ans);
        if (head_ans_status ==0){
            continue;
        }else if(sscanf(head_ans,"%d",&head_ans_value)!=1){
            printf("Invalid input. Please enter number.\n\n");
            head_ans_status=0;
        }else if(head_ans_value==1){
            head_staff_menu(staff_id,role);
            head_ans_status=1;
        }else if(head_ans_value==2){
            head_approver_menu(staff_id,role);
            head_ans_status=1;
        }else if(head_ans_value==3){
            printf("Your session has ended and you have been logged out of the system. You will now be redirected back to the main page.\n");
            login_menu();
            head_ans_status=1;
        }else{
            printf("This number is out of range. Please enter a valid number.\n");
            head_ans_status=0;
        }
    }while(head_ans_status==0);
}


