
#include "main.h"
#include "function.h"

#define MAX_ATTEMPTS 3


void check_password(char* txtPassword, char* role, char* staff_id) {
    char staffID[100];
    strcpy(staffID,staff_id);
    char staffRole[100];
    strcpy(staffRole,role);

    char password[100];
    int try = MAX_ATTEMPTS;
    int pass_index;
    char pass_char;

    while (try > 0) {
        printf("\n");
        printf("Please enter your password: ");
        pass_index=0;

        //13 is the ASCII value for Enter key
        //8 is the ASCII value for backspace key
        //getch will get the user input character by character without displaying the user input on screen
        while ((pass_char=getch())!= 13){
            if(pass_char == 8){
                if(pass_index>0){
                    pass_index--;
                    // \b is backspace
                    printf("\b \b");
                }
            }else{
                password[pass_index]=pass_char;
                printf("*");
                //Once the pass_char had stored in first index of password, pass_index will increase by 1 to store the next pass_char in the next index of password
                pass_index++;
            }
        }

        // \0 is null character that terminates the string
        password[pass_index]='\0';

        //remove the newline
        int password_len = strlen(password);
        if (password_len > 0 && password[password_len - 1] == '\n') {
            password[password_len - 1] = '\0';
        }

        password_len = strlen(password);

        //check if the user's input is blank
        if (password_len == 0) {
            printf("\nPlease don't leave it blank.\n");
            check_password(txtPassword,role,staff_id);
            break;
        }

        //if the password is same with the txtPassword
        if (strcmp(password, txtPassword) == 0) {
            printf("\n\nLogin Successfully.\n\n");
            //different roles will access to different menu
            if(strcmp(role,"CEO")==0){
                approver_menu(staffID,staffRole);
                break;
            }else if(strcmp(role,"Member")==0){
                staff_menu(staffID,staffRole);
                break;
            }else if(strcmp(role,"Head")==0){
                head_menu(staffID,staffRole);
                break;
            }else if(strcmp(role,"Admin")==0){
                admin_menu();
                break;
            }

        }else {
            try -= 1;
            printf("\nIncorrect Password. %d attempts remaining.\n", try);
        }
    }

    // the user has 3 try to type the password, when all the try are used up , which means try equal to 0, it will call login_menu()
    if (try == 0) {
        printf("\nMaximum number of attempts reached.\n\n");
        printf("Going over the limit of attempts will return you back to the main page.\n\n");
        login_menu();
    }
}



void check_username() {

    char username[100];
    int line;
    int size=1;
    int username_status;
    char admin_login_data[100];
    int num=0;

    //count the line of text file and store in line variable
    line=count_txt_line("staff_info.txt");

    //allocate dynamic memory for an the structure staff_info with size of line to avoid wastage of memory
    struct staff *staff_info = (struct staff *) malloc(line * sizeof(struct staff));

    //read staff_info.txt and store all the data in staff_info structure
    read_staff_file(staff_info);

    printf("\n\n");
    printf(" -------------------------------------\n");
    printf("              Login Page              \n");
    printf(" -------------------------------------\n");
    do{
        printf("Please enter your username: ");

        fgets(username, 100, stdin);

        //check if the user's input is blank
        username_status=blank_check(username);

        if(username_status!=0){
            username_status=0;
            //open login.txt using read mode
            FILE* admin_login_file = fopen("admin_login.txt", "r");

            //read login.txt line by line
            while (fgets(admin_login_data, 100, admin_login_file) != NULL) {
                //spilt the lines by " | " and store it in two token
                char* txtUsername = strtok(admin_login_data, " | ");
                char* txtPassword = rstrip(strtok(NULL, " | "));


                //compare if the username is same with the txtUsername in admin file
                if (strcmp(txtUsername, username) == 0) {
                    username_status = 1;
                    check_password(txtPassword,"Admin","No");
                    break;
                }
            }

            fclose(admin_login_file);

            if (username_status != 1) {
                for(int i=0;i<line;i++){
                    //compare if the username is same with the txtUsername in staff file
                    if (strcmp(staff_info[i].username, username) == 0) {
                        username_status = 1;
                        check_password(staff_info[i].password,staff_info[i].staff_position,staff_info[i].staff_id);
                        break;
                    }
                }
            }
            if(username_status ==0){
                // if the username entered by the user cannot be found in admin file and staff file
                printf("Incorrect username. Please try again.\n\n");
            }
        }

    }while(username_status==0);

    //deallocate the dynamic memory block
    free(staff_info);
}

