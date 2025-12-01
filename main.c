#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- CONSTANTS & DEFINITIONS --- 
#define MAX_STUDENTS 100 
#define NAME_LENGTH 50 
#define FILE_NAME "class_data.txt" 
// --- DATA STRUCTURES --- 
// struct: Used to bundle related data (ID, Name, Marks) into a single unit. 
typedef struct { 
int id; 
char name[NAME_LENGTH]; 
int attendance_days; // Total days present 
float marks;         
// Final marks (e.g., out of 100) 
} Student; 
// --- GLOBAL VARIABLES --- 
// We use a global array for simplicity in this introductory level. 
Student class_list[MAX_STUDENTS]; 
int student_count = 0; // Tracks how many students are currently in the list 
// --- FUNCTION PROTOTYPES --- 
// Declaring functions before main() lets the compiler know they exist. 
void addStudent(); 
void markAttendance(); 
void enterMarks(); 
void displayReport(); 
void saveToFile(); 
void loadFromFile(); 
void clearInputBuffer(); 
 
// --- MAIN FUNCTION --- 
int main() { 
    int choice; 
 
    // Load existing data immediately when the program starts 
    loadFromFile(); 
 
    printf("\n=== STUDENT ATTENDANCE & MARKS MANAGER ===\n"); 
    printf("Welcome! Loaded %d students from file.\n", student_count); 
 
    do { 
        // Simple CLI Menu 
        printf("\n--- MAIN MENU ---\n"); 
        printf("1. Add New Student\n"); 
        printf("2. Mark Attendance\n"); 
        printf("3. Enter/Update Marks\n"); 
        printf("4. Display Class Report\n"); 
        printf("5. Save & Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        clearInputBuffer(); // Fixes skipping issues with scanf and strings 
 
        switch(choice) { 
            case 1: addStudent(); break; 
            case 2: markAttendance(); break; 
            case 3: enterMarks(); break; 
            case 4: displayReport(); break; 
            case 5:  
                saveToFile();  
                printf("Data saved. Exiting... Goodbye!\n"); 
                break; 
            default: printf("Invalid choice! Please try again.\n"); 
        } 
 
    } while (choice != 5); 
 
    return 0; 
} 

// --- FUNCTION IMPLEMENTATIONS --- 
 
/* 
 * Function: addStudent 
 * Purpose: Adds a new student to the global array. 
 * Concepts: Array indexing, struct assignment, string input. 
 */ 
void addStudent() { 
    if (student_count >= MAX_STUDENTS) { 
        printf("Error: Class is full! Cannot add more students.\n"); 
        return; 
    } 
 
    Student new_student; 
 
    // Auto-generate ID based on count (Simple logic: 1, 2, 3...) 
    new_student.id = student_count + 1;  
 
    printf("Enter Student Name: "); 
    // fgets is safer than scanf for strings with spaces 
    fgets(new_student.name, NAME_LENGTH, stdin); 
    // Remove the newline character added by fgets 
    new_student.name[strcspn(new_student.name, "\n")] = 0; 
 
    // Initialize default values 
    new_student.attendance_days = 0; 
    new_student.marks = 0.0; 
 
    // Store in the global array 
    class_list[student_count] = new_student; 
    student_count++; 
 
    printf("Student '%s' added successfully with ID %d.\n", 
new_student.name, new_student.id); 
} 
 
/* 
 * Function: markAttendance 
 * Purpose: Increments the attendance count for a specific student. 
 * Concepts: Loops (Linear Search), Conditions. 
 */ 
void markAttendance() { 
    int id, found = 0; 
     
    printf("Enter Student ID to mark present: "); 
    scanf("%d", &id); 
 
    // Loop through the array to find the student 
    for (int i = 0; i < student_count; i++) { 
        if (class_list[i].id == id) { 
            class_list[i].attendance_days++; 
            printf("Attendance marked for %s. Total Days: %d\n",  
                   class_list[i].name, class_list[i].attendance_days); 
            found = 1; 
            break; // Stop looping once found 
        } 
    } 
 
    if (!found) { 
        printf("Error: Student with ID %d not found.\n", id); 
    } 
} 
 
/* 
 * Function: enterMarks 
 * Purpose: Updates the marks for a specific student. 
 */ 
void enterMarks() { 
    int id, found = 0; 
     
    printf("Enter Student ID to enter marks: "); 
    scanf("%d", &id); 
 
    for (int i = 0; i < student_count; i++) { 
        if (class_list[i].id == id) { 
            printf("Current Marks: %.2f\n", class_list[i].marks); 
            printf("Enter New Marks: "); 
            scanf("%f", &class_list[i].marks); 
            printf("Marks updated for %s.\n", class_list[i].name); 
            found = 1; 
            break; 
        } 
    } 
 
    if (!found) { 
        printf("Error: Student with ID %d not found.\n", id); 
    } 
} 
 
/* 
 * Function: displayReport 
 * Purpose: Prints a formatted table of all students. 
 * Concepts: Formatting output with printf. 
 */ 
void displayReport() { 
    if (student_count == 0) { 
        printf("No data to display.\n"); 
        return; 
    } 
 
    printf("\n%-5s %-25s %-12s %-10s\n", "ID", "Name", "Attendance", 
"Marks"); 
    
printf("------------------------------------------------------\n"); 
 
    for (int i = 0; i < student_count; i++) { 
        printf("%-5d %-25s %-12d %-10.2f\n",  
               class_list[i].id,  
               class_list[i].name,  
               class_list[i].attendance_days,  
               class_list[i].marks); 
    } 
    
printf("------------------------------------------------------\n"); 
} 
 
/* 
 * Function: saveToFile 
 * Purpose: Writes the array data to a text file so it persists. 
 * Concepts: File I/O (fopen, fprintf, fclose). 
 */ 
void saveToFile() { 
    FILE *file = fopen(FILE_NAME, "w"); // Open for Writing ("w") 
     
    if (file == NULL) { 
        printf("Error: Could not save to file!\n"); 
        return; 
    } 
 
    // First line: Save the total count so we know how many to read later 
    fprintf(file, "%d\n", student_count); 
 
    // Write each student's data 
    for (int i = 0; i < student_count; i++) { 
        // Using a delimiter (comma or newline) makes reading easier 
        fprintf(file, "%d\n", class_list[i].id); 
        fprintf(file, "%s\n", class_list[i].name); 
        fprintf(file, "%d\n", class_list[i].attendance_days); 
        fprintf(file, "%f\n", class_list[i].marks); 
    } 
 
    fclose(file); 
    printf("Data saved to %s.\n", FILE_NAME); 
} 
 
/* 
 * Function: loadFromFile 
 * Purpose: Reads data from the text file into the array. 
 * Concepts: File I/O (fopen, fscanf, fclose). 
 */ 
void loadFromFile() { 
    FILE *file = fopen(FILE_NAME, "r"); // Open for Reading ("r") 
 
    if (file == NULL) { 
        printf("No previous data found. Starting fresh.\n"); 
        return; 
    } 
 
    // Read the total count first 
    fscanf(file, "%d", &student_count); 
     
    // Clear buffer after reading the integer, so fgets works for the name below 
    fgetc(file);  
 
    for (int i = 0; i < student_count; i++) { 
        fscanf(file, "%d", &class_list[i].id); 
        fgetc(file); // consume newline after ID 
         
        // Reading string with spaces from file 
        fgets(class_list[i].name, NAME_LENGTH, file); 
        class_list[i].name[strcspn(class_list[i].name, "\n")] = 0; // Remove newline 
         
        fscanf(file, "%d", &class_list[i].attendance_days); 
        fscanf(file, "%f", &class_list[i].marks); 
        fgetc(file); // consume newline after marks 
    } 
 
    fclose(file); 
} 
 
/* 
 * Function: clearInputBuffer 
 * Purpose: Clears the 'stdin' buffer to prevent scanning errors. 
 * Crucial when mixing scanf (for numbers) and fgets (for strings). 
 */ 
void clearInputBuffer() { 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
} 
