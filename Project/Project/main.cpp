#include <iostream>
#include <stdlib.h>
#include<string.h>
#include <mysql.h>
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN

int queryStudent()
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }
    printf("Connected MySQL successful! \n");

    mysql_query(&mysql, "set names gbk");
   

    int id;
    printf("Please enter the student number you are looking for:：");
    scanf("%d", &id);
    // Query data in database
    sprintf(query_str, "select * from student where id=%d",id);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return -1;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return -1;
    }
    rows = mysql_num_rows(res);

    fields = mysql_num_fields(res);

    while ((row = mysql_fetch_row(res))) {
        for (i = 0; i < fields; i++) {
            printf("%s\t", row[i]);
        }
        printf("\n");
    }

    mysql_close(&mysql);
    if (rows != 0)
    {
        return 1;
    }
    else
    {
        printf("The student ID queried does not exist, the query failed!\n");
        return -1;
    }
}

int haveStudent(int id)
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return -1;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return -1;
    }

    mysql_query(&mysql, "set names gbk");

    sprintf(query_str, "select * from student where id=%d", id);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return -1;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return -1;
    }
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    mysql_close(&mysql);
    if (rows != 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void addStudent()
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            insert_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return;
    }

    /** Attempt to establish a connection to the MySQL database engine running on the host
     * localhost is the host for the database connection
     * root is mysql username
     * 123456 is the password of mysql
     * zhang is the database name to connect to
     * followed by default parameters
     */
    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return;
    }
    printf("Connected MySQL successful! \n");

    // Insert data into the table
    int id; // ID
    char name[50]; //Name
    int age; // Age
    char classroom[50]; // Classroom
    printf("Please add information: \n");
    printf("Please enter student number: ");
    scanf("%d", &id);
    int temp = haveStudent(id);
    if (temp == 1)
    {
        printf("The student number exists, the addition failed!\n");
        return;
    }
    printf("Please type in your name: ");
    scanf("%s", name);
    printf("Please enter age: ");
    scanf("%d", &age);
    printf("Please enter classroom: ");
    scanf("%s", classroom);
    // Insert data into the table, the data is written as a variable
    sprintf(insert_str, "insert into student values ('%d', '%s', '%d', '%s')", id, name, age, classroom);
    rc = mysql_real_query(&mysql, insert_str, strlen(insert_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }

    sprintf(insert_str, "select * from student");
    rc = mysql_real_query(&mysql, insert_str, strlen(insert_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return;
    }


    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    printf("Added successfully！\n");

    mysql_close(&mysql);
    return;
}

void deleteStudent()
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return;
    }
    printf("Connected MySQL successful! \n");
    int id;
    printf("Please enter the student ID you want to delete: ");
    scanf("%d", &id);
    int temp = haveStudent(id);
    if (temp == -1)
    {
        printf("The student ID does not exist, the deletion failed!\n");
        return;
    }
    // Delete data, delete the data whose name is FFFF in the table
    sprintf(query_str, "delete from student where id = %d",id);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }

    sprintf(query_str, "select * from student");
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return;
    }
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    printf("successfully deleted!\n");

    mysql_close(&mysql);
    return;
}

void updateStudent()
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return;
    }

    int id; // ID
    char name[50]; // Name
    int age; // Age
    char classroom[50]; // Classroom
    printf("Please add information:\n");
    printf("Please enter student number: ");
    scanf("%d", &id);
    int temp = haveStudent(id);
    if (temp == -1)
    {
        printf("The student ID does not exist, the modification failed!\n");
        return;
    }
    printf("Please type in your name:");
    scanf("%s", name);
    printf("Please enter age:");
    scanf("%d", &age);
    printf("Please enter classroom: ");
    scanf("%s", classroom);

    sprintf(query_str, "UPDATE student SET name = %s, age = %d, classroom = %s WHERE id = %d; ",name,age,classroom,id);
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }

    sprintf(query_str, "select * from student");
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return;
    }
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    printf("Successfully updated\n");

    mysql_close(&mysql);
    return;
}

void showStudent()
{
    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return;
    }
    printf("Connected MySQL successful! \n");

    if (mysql_set_character_set(&mysql, "gbk")) {
        fprintf(stderr, "Error, %s/n", mysql_error(&mysql));
    }


    // Query data in database
    sprintf(query_str, "select * from student");
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return;
    }
    rows = mysql_num_rows(res);
    printf("The total rows is: %d\n", rows);
    fields = mysql_num_fields(res);
    printf("The total fields is: %d\n", fields);
    while ((row = mysql_fetch_row(res))) {
        for (i = 0; i < fields; i++) {
            printf("%s\t", row[i]);
        }
        printf("\n");
    }

    mysql_close(&mysql);
    return;
}

void saveStudent()
{
    FILE* file;
    if ((file = fopen("student.txt", "w")) == NULL)
    {
        printf("File open failed!");
        return;
    }

    MYSQL           mysql;
    MYSQL_RES* res = NULL;
    MYSQL_ROW       row;
    char            query_str[200];
    int             rc, i, fields;
    int             rows;

    // Allocate and initialize MYSQL objects
    if (mysql_init(&mysql) == NULL)
    {
        printf("mysql_init(): %s\n", mysql_error(&mysql));
        return;
    }

    if (mysql_real_connect(&mysql, "localhost", "root", "12345678", "sys", 0, NULL, 0) == NULL)
    {
        printf("mysql_real_connect(): %s\n", mysql_error(&mysql));
        return;
    }
    printf("Connected MySQL successful! \n");

    if (mysql_set_character_set(&mysql, "gbk")) {
        fprintf(stderr, "Error, %s/n", mysql_error(&mysql));
    }


    // Query data in database
    sprintf(query_str, "select * from student");
    rc = mysql_real_query(&mysql, query_str, strlen(query_str));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(&mysql));
        return;
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(&mysql));
        return;
    }
    rows = mysql_num_rows(res);
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (i = 0; i < fields; i++) {
            fprintf(file, "%s\t", row[i]);
        }
        fprintf(file, "\n");
    }

    mysql_close(&mysql);
    fclose(file);
    printf("File saved successfully!\n");
    return;
}

void menu()
{
    printf("\t\t------------------------\n");
    printf("\t\t       Information Management System\n");
    printf("\t\t      1.MySQL add information\n");
    printf("\t\t      2.MySQL delete information\n");
    printf("\t\t      3.MySQL modification information\n");
    printf("\t\t      4.MySQL query information\n");
    printf("\t\t      5.MySQL browsing information\n");
    printf("\t\t      6.MySQL table information export file\n");
    printf("\t\t      7.Open html+js file\n");
    printf("\t\t      0.Exit System\n");
    printf("\t\t------------------------\n");
    printf("Please enter your choice: \n");
}

// Open html+js file
void openHtmlAndJs()
{
    std::string path = "index.html";
    ShellExecute(NULL, TEXT("open"), TEXT("index.html"), NULL, NULL, SW_SHOWNORMAL);

}


int main()
{
    int chioce;
    while (1)
    {
        menu();
        scanf("%d", &chioce);
        switch (chioce)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            queryStudent();
            break;
        case 5:
            showStudent();
            break;
        case 6:
            saveStudent();
            break;
        case 7:
            openHtmlAndJs();
            break;
        case 0:
            printf("Welcome to use next time!\n");
            exit(0);
        default:
            printf("The input is incorrect, please try again!\n");
            break;
        }

    }
    return 0;
}