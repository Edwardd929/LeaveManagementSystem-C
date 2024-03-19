#include "main.h"
#include "function.h"

//read "leave_summary.txt" and store in struct leave_summary *read_leave_summary
void read_leave_summary_file(struct leave_summary *read_leave_summary){
    int line=count_txt_line("leave_summary.txt");

    FILE* leave_summary_text = fopen("leave_summary.txt", "r");

    if (leave_summary_text == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    // Move the file pointer back to the beginning of the file
    rewind(leave_summary_text);

    for (int i = 0; i < line; i++){
        fscanf(leave_summary_text, "%s | annual leave:%d | compassionate leave:%d | emergency leave:%d | maternity leave:%d | medical leave:%d\n",
               read_leave_summary[i].staffID, &read_leave_summary[i].annual_leave, &read_leave_summary[i].compassionate_leave,
               &read_leave_summary[i].emergency_leave, &read_leave_summary[i].maternity_leave, &read_leave_summary[i].medical_leave);
    }
    fclose(leave_summary_text);
}

//read "staff_info.txt" and store in struct staff *read_staff
void read_staff_file(struct staff *read_staff){
    int line=count_txt_line("staff_info.txt");

    FILE* staff_info_text = fopen("staff_info.txt", "r");

    if (staff_info_text == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    // Move the file pointer back to the beginning of the file
    rewind(staff_info_text);

    for (int i = 0; i < line; i++){
        fscanf(staff_info_text, "%s | %[^|] | %s | %s | %s | %s | %[^|] | %[^|] | %s | %s\n",
               read_staff[i].staff_id,read_staff[i].name,read_staff[i].age,
                read_staff[i].email, read_staff[i].contact_number, read_staff[i].staff_position, read_staff[i].department, read_staff[i].job_title,
                read_staff[i].username,read_staff[i].password);
    }
    fclose(staff_info_text);
}

//read "leave_calendar.txt" and store in struct calendar *read_calendar
void read_leave_calendar(struct calendar *read_calendar){
    int line=count_txt_line("leave_calendar.txt");

    FILE* calendar_txt = fopen("leave_calendar.txt", "r");

    if (calendar_txt == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    // Move the file pointer back to the beginning of the file
    rewind(calendar_txt);

    for (int i = 0; i < line; i++){
        fscanf(calendar_txt, "%s | Annual Leave: %d | Compassionate Leave: %d | Emergency Leave: %d | Maternity Leave: %d | Medical Leave: %d\n",
               read_calendar[i].date,&read_calendar[i].annual_leave,
                &read_calendar[i].compassionate_leave,&read_calendar[i].emergency_leave,&read_calendar[i].maternity_leave,
                &read_calendar[i].medical_leave);
    }
    fclose(calendar_txt);
}

//read "department_leave.txt" and store in struct department_leave *read_department_leave
void read_department_file(struct department_leave *read_department_leave){
    int line=count_txt_line("department_leave.txt");

    FILE* department_leave_txt = fopen("department_leave.txt", "r");

    if (department_leave_txt == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    // Move the file pointer back to the beginning of the file
    rewind(department_leave_txt);

    for (int i = 0; i < line; i++){
        fscanf(department_leave_txt, "%[^|] | %s | Annual Leave: %d | Compassionate Leave: %d | Emergency Leave: %d | Maternity Leave: %d | Medical Leave: %d\n",
               read_department_leave[i].department,read_department_leave[i].month, &read_department_leave[i].annual_leave,
               &read_department_leave[i].compassionate_leave,&read_department_leave[i].emergency_leave,
               &read_department_leave[i].maternity_leave,&read_department_leave[i].medical_leave);
    }
    fclose(department_leave_txt);
}

//read "apply_leave.txt" and store in struct leave *read_apply_leave
void read_apply_leave(struct leave *read_apply_leave){
    int line=count_txt_line("apply_leave.txt");

    FILE* apply_leave_txt = fopen("apply_leave.txt", "r");
    if (apply_leave_txt == NULL) {
        printf("Error: Could not open the file.\n");
        return;
    }
    // Move the file pointer back to the beginning of the file
    rewind(apply_leave_txt);

    for (int i = 0; i < line; i++){
        fscanf(apply_leave_txt, "%s | %[^|] | %s | %s | %d | %d | %d | %[^|] | %s\n",
               read_apply_leave[i].staffID,read_apply_leave[i].leave_type,read_apply_leave[i].from,
               read_apply_leave[i].to,&read_apply_leave[i].days,&read_apply_leave[i].first_month_days,&read_apply_leave[i].second_month_days,read_apply_leave[i].reason,read_apply_leave[i].status);
    }
    fclose(apply_leave_txt);
}

//rewrite "leave_summary.txt" by referring to struct leave_summary *modify_leave_summary
void save_leave_summary(struct leave_summary *modify_leave_summary){
    int line=count_txt_line("leave_summary.txt");

    FILE* modify_leave_txt= fopen("leave_summary.txt","w");
    for(int i=0;i<line;i++){
        fprintf(modify_leave_txt,"%s | annual leave:%d | compassionate leave:%d | emergency leave:%d | maternity leave:%d | medical leave:%d\n",
            modify_leave_summary[i].staffID, modify_leave_summary[i].annual_leave, modify_leave_summary[i].compassionate_leave,
            modify_leave_summary[i].emergency_leave, modify_leave_summary[i].maternity_leave, modify_leave_summary[i].medical_leave);
    }
    fclose(modify_leave_txt);
}

//rewrite "leave_calendar.txt" by referring to struct calendar *modify_leave_calendar
void save_leave_calendar(struct calendar *modify_leave_calendar){
    int line=count_txt_line("leave_calendar.txt");

    FILE* modify_calendar_txt= fopen("leave_calendar.txt","w");
    for(int i=0;i<line;i++){
        fprintf(modify_calendar_txt,"%s | Annual Leave: %d | Compassionate Leave: %d | Emergency Leave: %d | Maternity Leave: %d | Medical Leave: %d\n",
                modify_leave_calendar[i].date,modify_leave_calendar[i].annual_leave,
                modify_leave_calendar[i].compassionate_leave,modify_leave_calendar[i].emergency_leave,modify_leave_calendar[i].maternity_leave,
                modify_leave_calendar[i].medical_leave);
    }
    fclose(modify_calendar_txt);
}

//rewrite "department_leave.txt" by referring to struct department_leave *modify_department_leave
void save_leave_department(struct department_leave *modify_department_leave){
    int line=count_txt_line("department_leave.txt");

    FILE* modify_department_txt= fopen("department_leave.txt","w");
    for(int i=0;i<line;i++){
        fprintf(modify_department_txt,"%s| %s | Annual Leave: %d | Compassionate Leave: %d | Emergency Leave: %d | Maternity Leave: %d | Medical Leave: %d\n",
               modify_department_leave[i].department,modify_department_leave[i].month, modify_department_leave[i].annual_leave,
               modify_department_leave[i].compassionate_leave,modify_department_leave [i].emergency_leave,
               modify_department_leave[i].maternity_leave,modify_department_leave[i].medical_leave);
    }
    fclose(modify_department_txt);
}

//rewrite "apply_leave.txt" by referring to struct leave *modify_apply_leave
void save_leave_status(struct leave *modify_apply_leave){
    int line=count_txt_line("apply_leave.txt");

    FILE* modify_status_txt= fopen("apply_leave.txt","w");
    for(int i=0;i<line;i++){
        fprintf(modify_status_txt,"%s | %s| %s | %s | %d | %d | %d | %s| %s\n",
               modify_apply_leave[i].staffID,modify_apply_leave[i].leave_type,modify_apply_leave[i].from,
               modify_apply_leave[i].to,modify_apply_leave[i].days,modify_apply_leave[i].first_month_days,modify_apply_leave[i].second_month_days,
               modify_apply_leave[i].reason,modify_apply_leave[i].status);
    }
    fclose(modify_status_txt);
}
