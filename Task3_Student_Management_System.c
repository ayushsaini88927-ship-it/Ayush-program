#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define NAME_SIZE 50
#define COURSE_SIZE 30

typedef struct
{
    int rollNo;
    char name[NAME_SIZE];
    int age;
    char course[COURSE_SIZE];
    float marks;
} Student;

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Clear remaining input */
    }
}

void readLine(char *text, int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}

int rollExists(int rollNo)
{
    FILE *file;
    Student student;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.rollNo == rollNo)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void addStudent(void)
{
    FILE *file;
    Student student;

    printf("\n===== ADD STUDENT =====\n");

    printf("Enter Roll Number: ");
    if (scanf("%d", &student.rollNo) != 1)
    {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (rollExists(student.rollNo))
    {
        printf("A student with this roll number already exists.\n");
        return;
    }

    printf("Enter Name: ");
    readLine(student.name, NAME_SIZE);

    printf("Enter Age: ");
    if (scanf("%d", &student.age) != 1)
    {
        printf("Invalid age.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printf("Enter Course: ");
    readLine(student.course, COURSE_SIZE);

    printf("Enter Marks: ");
    if (scanf("%f", &student.marks) != 1)
    {
        printf("Invalid marks.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (student.marks < 0 || student.marks > 100)
    {
        printf("Marks must be between 0 and 100.\n");
        return;
    }

    file = fopen(FILE_NAME, "ab");

    if (file == NULL)
    {
        printf("Unable to open student data file.\n");
        return;
    }

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);

    printf("Student added successfully.\n");
}

void displayStudents(void)
{
    FILE *file;
    Student student;
    int count = 0;

    printf("\n================ STUDENT RECORDS ================\n");

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    printf("%-8s %-22s %-6s %-18s %-8s\n",
           "Roll No", "Name", "Age", "Course", "Marks");
    printf("-----------------------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        printf("%-8d %-22s %-6d %-18s %-8.2f\n",
               student.rollNo,
               student.name,
               student.age,
               student.course,
               student.marks);
        count++;
    }

    fclose(file);

    if (count == 0)
    {
        printf("No student records found.\n");
    }

    printf("===============================================================\n");
}

void searchStudent(void)
{
    FILE *file;
    Student student;
    int rollNo;
    int found = 0;

    printf("\n===== SEARCH STUDENT =====\n");
    printf("Enter Roll Number to search: ");

    if (scanf("%d", &rollNo) != 1)
    {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.rollNo == rollNo)
        {
            printf("\nStudent Found\n");
            printf("Roll Number : %d\n", student.rollNo);
            printf("Name        : %s\n", student.name);
            printf("Age         : %d\n", student.age);
            printf("Course      : %s\n", student.course);
            printf("Marks       : %.2f\n", student.marks);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Student with Roll Number %d not found.\n", rollNo);
    }
}

void updateStudent(void)
{
    FILE *file;
    Student student;
    int rollNo;
    int found = 0;

    printf("\n===== UPDATE STUDENT =====\n");
    printf("Enter Roll Number to update: ");

    if (scanf("%d", &rollNo) != 1)
    {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    file = fopen(FILE_NAME, "r+b");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.rollNo == rollNo)
        {
            printf("\nCurrent Record:\n");
            printf("Name   : %s\n", student.name);
            printf("Age    : %d\n", student.age);
            printf("Course : %s\n", student.course);
            printf("Marks  : %.2f\n", student.marks);

            printf("\nEnter New Name: ");
            readLine(student.name, NAME_SIZE);

            printf("Enter New Age: ");
            if (scanf("%d", &student.age) != 1)
            {
                printf("Invalid age.\n");
                clearInputBuffer();
                fclose(file);
                return;
            }
            clearInputBuffer();

            printf("Enter New Course: ");
            readLine(student.course, COURSE_SIZE);

            printf("Enter New Marks: ");
            if (scanf("%f", &student.marks) != 1)
            {
                printf("Invalid marks.\n");
                clearInputBuffer();
                fclose(file);
                return;
            }
            clearInputBuffer();

            if (student.marks < 0 || student.marks > 100)
            {
                printf("Marks must be between 0 and 100.\n");
                fclose(file);
                return;
            }

            fseek(file, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&student, sizeof(Student), 1, file);

            found = 1;
            printf("Student record updated successfully.\n");
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Student with Roll Number %d not found.\n", rollNo);
    }
}

void deleteStudent(void)
{
    FILE *file;
    FILE *tempFile;
    Student student;
    int rollNo;
    int found = 0;

    printf("\n===== DELETE STUDENT =====\n");
    printf("Enter Roll Number to delete: ");

    if (scanf("%d", &rollNo) != 1)
    {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No student records found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        printf("Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.rollNo == rollNo)
        {
            found = 1;
            continue;
        }

        fwrite(&student, sizeof(Student), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        if (remove(FILE_NAME) != 0)
        {
            printf("Could not remove old data file.\n");
            remove("temp.dat");
            return;
        }

        if (rename("temp.dat", FILE_NAME) != 0)
        {
            printf("Could not update student data file.\n");
            return;
        }

        printf("Student deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Student with Roll Number %d not found.\n", rollNo);
    }
}

void showMenu(void)
{
    printf("\n\n============================================\n");
    printf("       STUDENT MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
    printf("============================================\n");
    printf("Enter your choice: ");
}

int main(void)
{
    int choice;

    do
    {
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using Student Management System.\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}
