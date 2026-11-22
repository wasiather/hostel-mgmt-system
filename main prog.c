/*         ================================================================
                             HOSTEL MANAGEMENT SYSTEM
 * Wasi Ather Siddiqui (CS26-122) : addStudent, findStudent, findRoom, searchStudent, displayStudent
 * Yasir Ali Junejo (CS26-135)    : admin login, main menu, input validation (read functions), room initialization
 * Haris Ismail (CS26-141)        : file handling, saveData, report making
 * Muhammad Sharjeel (CS26-131)   : fee, check out and rooms management functions
           ================================================================     */                                               

                    
// Headers
#include <stdio.h>
#include <string.h>

// Constants, Storage & Configurations
#define MAX_ROOMS      10
#define ROOM_CAPACITY  3
#define MAX_STUDENTS   30
#define NAME_LEN       30
#define FIRST_ROOM_NO  101
#define PHONE          1
#define EMAIL          2
#define PREMIUM        1
#define NORMAL         2
#define ADMIN_COUNT    2
#define CRED_LEN       20

const float PREMIUM_RENT = 6000.0;
const float NORMAL_RENT  = 4500.0;

const char *ADMIN_IDS[ADMIN_COUNT]       = { "admin1",     "admin2"     };
const char *ADMIN_PASSWORDS[ADMIN_COUNT] = { "Hostel@123", "Warden@456" };


union Contact {
    char phone[16];
    char email[40];
};

struct Student {
    int           id;
    char          name[NAME_LEN];
    int           age;
    int           roomNo;
    int           contactType;
    union Contact contact;
    float         feeDue;
    float         feePaid;
};

struct Room {
    int   roomNo;
    int   type;
    int   capacity;
    int   occupied;
    float rent;
};

// Prototypes
int  login(void);
void printMenu(void);
int  readNumber(char prompt[], int min, int max);
float readAmount(char prompt[], float min, float max);
char *roomTypeName(int type);

void initRooms(struct Room rooms[]);
void loadData(struct Student students[], int *count, struct Room rooms[]);
void saveData(struct Student students[], int count);
void logActivity(char action[], int id);

struct Student *findStudent(struct Student *list, int count, int id);
struct Room    *findRoom(struct Room *list, int roomNo);

void addStudent(struct Student students[], int *count, struct Room rooms[]);
void displayStudents(struct Student students[], int count, struct Room rooms[]);
void searchStudent(struct Student students[], int count, struct Room rooms[]);
void removeStudent(struct Student students[], int *count, struct Room rooms[]);
void showRoomStatus(struct Room rooms[]);
void payFees(struct Student students[], int count);
void showDefaulters(struct Student students[], int count);
void exportReport(struct Student students[], int count, struct Room rooms[]);
void printContact(struct Student *s);

//Main Function
int main(){
    struct Student students[MAX_STUDENTS];
    struct Room    rooms[MAX_ROOMS];
    int studentCount = 0;
    int choice;

    if (!login()) {
        printf("\n  Exiting program. Goodbye!\n\n");
        return 0;
    }

    loadData(students, &studentCount, rooms);

    printf("\n  Welcome to the Hostel Management System\n");
    printf("  Records loaded: %d student(s)\n", studentCount);

    do {
        printMenu();
        choice = readNumber("  Enter your choice: ", 0, 8);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount, rooms);
                saveData(students, studentCount);
                break;
            case 2:
                displayStudents(students, studentCount, rooms);
                break;
            case 3:
                searchStudent(students, studentCount, rooms);
                break;
            case 4:
                removeStudent(students, &studentCount, rooms);
                saveData(students, studentCount);
                break;
            case 5:
                showRoomStatus(rooms);
                break;
            case 6:
                payFees(students, studentCount);
                saveData(students, studentCount);
                break;
            case 7:
                showDefaulters(students, studentCount);
                break;
            case 8:
                exportReport(students, studentCount, rooms);
                break;
            case 0:
                saveData(students, studentCount);
                printf("\n  Data saved. Goodbye!\n\n");
                break;
            default:
                printf("  Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

/* ADMIN LOGIN SYSTEM
 Developed by: Yasir Ali Junejo*/
int login(void)
{
    char id[CRED_LEN + 1];
    char password[CRED_LEN + 1];
    int i;
    printf("\n  ======== ADMIN LOGIN ========\n");
    while (1) {
        printf("  Admin ID : ");
        scanf("%20s", id);
        printf("  Password : ");
        scanf("%20s", password);
        for (i = 0; i < ADMIN_COUNT; i++) 
        {
            if (strcmp(id, ADMIN_IDS[i]) == 0 && strcmp(password, ADMIN_PASSWORDS[i]) == 0) 
            {
                printf("\n  Login successful. Welcome, %s!\n", id);
                return 1;
            }
        }
        printf("\n  Access denied: incorrect ID or password.\n");
        printf("   1. Try again\n");
        printf("   0. Exit program\n");
        if (readNumber("  Enter your choice: ", 0, 1) == 0) 
        {
            return 0;
        }
        printf("\n");
    }
}
/* MENU DISPLAY
 Developed by: Yasir Ali Junejo */
void printMenu(void)
{
    printf("\n======== HOSTEL MANAGEMENT SYSTEM ========\n");
    printf("1. Admit a student\n");
    printf("2. Display all students\n");
    printf("3. Search student by ID\n");
    printf("4. Check out (remove) a student\n");
    printf("5. Show room status\n");
    printf("6. Pay hostel fees\n");
    printf("7. Show fee defaulters\n");
    printf("8. Export report to text file\n");
    printf("0. Save and exit\n");
    printf("===========================================\n");
}
/* INPUT VALIDATION 
 Developed by: Yasir Ali Junejo */
int readNumber(char prompt[], int min, int max)
{
    int value;

    do {
        printf("%s", prompt);
        scanf("%d", &value);
        if (value < min || value > max) 
        {
            printf("  Invalid input. Enter a number from %d to %d.\n", min, max);
        }
    } while (value < min || value > max);

    return value;
}

float readAmount(char prompt[], float min, float max)
{
    float value;

    do {
        printf("%s", prompt);
        scanf("%f", &value);
        if (value < min || value > max) 
        {
            printf("  Invalid amount. Enter a value from %.2f to %.2f.\n", min, max);
        }
    } while (value < min || value > max);

    return value;
}
/* ROOM INITIALIZATION
Developed by: Yasir Ali Junejo */
char *roomTypeName(int type)
{
    if (type == PREMIUM) 
    {
        return "Premium";
    }
    return "Normal";
}

void initRooms(struct Room rooms[])
{
    int i;

    for (i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNo   = FIRST_ROOM_NO + i;
        rooms[i].capacity = ROOM_CAPACITY;
        rooms[i].occupied = 0;
        if (i < 5) {
            rooms[i].type = PREMIUM;
            rooms[i].rent = PREMIUM_RENT;
        } else {
            rooms[i].type = NORMAL;
            rooms[i].rent = NORMAL_RENT;
        }
    }
}
/* LOOKUP FUNCTIONS
Developed by: Wasi Ather Siddiqui */
struct Student *findStudent(struct Student *list, int count, int id)
{ struct Student *p = list;
    int i;
for (i = 0; i < count; i++) {
    if (p->id == id) {
      return p;    }
        p++;
    }
    return NULL;
}

struct Room *findRoom(struct Room *list, int roomNo)
{ int i;
for (i = 0; i < MAX_ROOMS; i++) {
        if ((list + i)->roomNo == roomNo) {
            return list + i; }
    }
    return NULL; }

/* ADMIT STUDENTS
Developed by: Wasi Ather Siddiqui */
void addStudent(struct Student students[], int *count, struct Room rooms[])
{
    struct Student s;
    struct Room   *room = NULL;
    int roomNo;

    if (*count >= MAX_STUDENTS) {
        printf("\n  Hostel is full. No more admissions possible.\n");
        return;
    }

    printf("\n  --- Admit New Student ---\n");

    s.id = readNumber("  Student ID (1-9999): ", 1, 9999);
    if (findStudent(students, *count, s.id) != NULL) {
        printf("  A student with ID %d already exists.\n", s.id);
        return; }

    printf("  Name (one word, use _ for space): ");
    scanf("%s", s.name);

    s.age = readNumber("  Age (16-60): ", 16, 60);

    s.contactType = readNumber("  Contact type (1 = Phone, 2 = Email): ", 1, 2);
    if (s.contactType == PHONE) {
        printf("  Phone number: ");
        scanf("%s", s.contact.phone);
    } else {
        printf("  Email address: ");
        scanf("%s", s.contact.email);
    }

    showRoomStatus(rooms);

    do {
        roomNo = readNumber("  Choose room number (0 to cancel): ", 0, FIRST_ROOM_NO + MAX_ROOMS - 1);
        if (roomNo == 0) {
            printf("  Admission cancelled.\n");
            return;
        }
        room = findRoom(rooms, roomNo);
        if (room == NULL) {
            printf("  No such room.\n");
        } else if (room->occupied >= room->capacity) {
            printf("  Room %d is full. Choose another.\n", roomNo);
            room = NULL;
        }
    } while (room == NULL);

    s.roomNo  = room->roomNo;
    s.feeDue  = room->rent;
    s.feePaid = 0;
    room->occupied++;

    students[*count] = s;
    (*count)++;

    logActivity("ADMITTED", s.id);
    printf("\n  Student %s admitted to %s room %d. Monthly fee: Rs %.2f\n",
           s.name, roomTypeName(room->type), s.roomNo, s.feeDue);
}

/* Helper: prints a student's contact (phone or email). */
void printContact(struct Student *s)
{
    if (s->contactType == PHONE) {
        printf("Phone: %s", s->contact.phone);
    } else {
        printf("Email: %s", s->contact.email);
    }
}

/* DISPLAY STUDENTS
Developed by: Wasi Ather Siddiqui */
void displayStudents(struct Student students[], int count, struct Room rooms[])
{
  int i;
  struct Room *r;

    if (count == 0) {
        printf("\n  No students are registered.\n");
        return; }

    printf("\n  %-5s %-16s %-4s %-5s %-8s %-10s %-10s\n",
           "ID", "Name", "Age", "Room", "Type", "Due (Rs)", "Paid (Rs)");
    printf("  -------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        r = findRoom(rooms, students[i].roomNo);
        printf("  %-5d %-16s %-4d %-5d %-8s %-10.2f %-10.2f\n",
               students[i].id, students[i].name, students[i].age,
               students[i].roomNo, roomTypeName(r->type),
               students[i].feeDue, students[i].feePaid);
        printf("        ");
        printContact(&students[i]);
        printf("\n");
    }
    printf("\n  Total students: %d\n", count);
}


/* SEARCH STUDENT
Developed by: Wasi Ather Siddiqui */
void searchStudent(struct Student students[], int count, struct Room rooms[])
{
int id = readNumber("\n  Enter student ID to search: ", 1, 9999);
struct Student *s = findStudent(students, count, id);
struct Room *r;

    if (s == NULL) {
        printf("  No student found with ID %d.\n", id);
        return; }

    r = findRoom(rooms, s->roomNo);

    printf("\n  ID       : %d\n", s->id);
    printf("  Name     : %s\n", s->name);
    printf("  Age      : %d\n", s->age);
    printf("  Room     : %d (%s)\n", s->roomNo, roomTypeName(r->type));
    printf("  Contact  : ");
    printContact(s);
    printf("\n  Fee due  : Rs %.2f\n", s->feeDue);
    printf("  Fee paid : Rs %.2f\n", s->feePaid);
    printf("  Status   : %s\n", (s->feePaid >= s->feeDue) ? "Fees cleared" : "Fees pending");
}


/* CHECK OUT STUDENTS
Developed by: Muhammad Sharjeel */
void removeStudent(struct Student students[], int *count, struct Room rooms[])
{
    int id = readNumber("\n  Enter ID of student to check out: ", 1, 9999);
    struct Student *s = findStudent(students, *count, id);
    struct Student *last;
    struct Room *r;

    if (s == NULL) {
        printf("  No student found with ID %d.\n", id);
        return;
    }

    if (s->feePaid < s->feeDue) {
        printf("  Warning: Rs %.2f is still unpaid.\n", s->feeDue - s->feePaid);
        if (readNumber("  Check out anyway? (1 = Yes, 0 = No): ", 0, 1) == 0) {
            printf("  Check-out cancelled.\n");
            return;
        }
    }

    r = findRoom(rooms, s->roomNo);
    if (r != NULL && r->occupied > 0) {
        r->occupied--;
    }

    logActivity("CHECKED_OUT", s->id);

    last = students + (*count) - 1;
    while (s < last) {
        *s = *(s + 1);
        s++;
    }
    (*count)--;

    printf("  Student checked out successfully.\n");
}
/* ROOM STATUS
Developed by: Muhammad Sharjeel */
void showRoomStatus(struct Room rooms[])
{
    int i;

    printf("\n  %-6s %-9s %-9s %-9s %-10s %s\n",
           "Room", "Type", "Capacity", "Occupied", "Rent (Rs)", "Status");
    printf("  -----------------------------------------------------------------\n");

    for (i = 0; i < MAX_ROOMS; i++) {
        printf("  %-6d %-9s %-9d %-9d %-10.2f ",
               rooms[i].roomNo, roomTypeName(rooms[i].type),
               rooms[i].capacity, rooms[i].occupied, rooms[i].rent);

        if (rooms[i].occupied == 0) {
            printf("Empty\n");
        } else if (rooms[i].occupied < rooms[i].capacity) {
            printf("Available (%d bed(s) free)\n", rooms[i].capacity - rooms[i].occupied);
        } else {
            printf("Full\n");
        }
    }

    printf("\n  Premium rooms: Rs %.2f per month    Normal rooms: Rs %.2f per month\n",
           PREMIUM_RENT, NORMAL_RENT);
}
/* FEE PAYMENT
Developed by: Muhammad Sharjeel */
void payFees(struct Student students[], int count)
{
    int id = readNumber("\n  Enter student ID: ", 1, 9999);
    struct Student *s = findStudent(students, count, id);
    float remaining, amount;

    if (s == NULL) {
        printf("  No student found with ID %d.\n", id);
        return;
    }

    remaining = s->feeDue - s->feePaid;
    if (remaining <= 0) {
        printf("  %s has no pending fees.\n", s->name);
        return;
    }

    printf("  %s owes Rs %.2f\n", s->name, remaining);
    amount = readAmount("  Amount to pay: Rs ", 1, remaining);

    s->feePaid = s->feePaid + amount;
    logActivity("FEE_PAID", s->id);

    if (s->feePaid >= s->feeDue) {
        printf("  Payment received. Fees fully cleared.\n");
    } else {
        printf("  Payment received. Remaining: Rs %.2f\n", s->feeDue - s->feePaid);
    }
}
/* FEE DEFAULTERS
Developed by: Muhammad Sharjeel */
void showDefaulters(struct Student students[], int count)
{
    int i, found = 0;
    float pending, totalPending = 0;

    printf("\n  --- Fee Defaulters ---\n");
    for (i = 0; i < count; i++) {
        pending = students[i].feeDue - students[i].feePaid;
        if (pending > 0) {
            printf("  ID %-5d %-16s Room %-4d Pending: Rs %.2f\n",
                   students[i].id, students[i].name, students[i].roomNo, pending);
            totalPending = totalPending + pending;
            found++;
        }
    }

    if (found == 0) {
        printf("  No defaulters. All fees are cleared.\n");
    } else {
        printf("\n  %d defaulter(s), total pending: Rs %.2f\n", found, totalPending);
    }
}
/* FILE HANDLING - LOAD & SAVE DATA
Developed by: Haris Ismail */
void loadData(struct Student students[], int *count, struct Room rooms[])
{
    FILE *fp;
    int i;
    struct Room *r;

    initRooms(rooms);
    *count = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("  (No saved data found. Starting with an empty hostel.)\n");
        return;
    }

    fscanf(fp, "%d", count);
    if (*count > MAX_STUDENTS) {
        *count = MAX_STUDENTS;
    }

    for (i = 0; i < *count; i++) {
        fscanf(fp, "%d %s %d %d %d",
               &students[i].id, students[i].name, &students[i].age,
               &students[i].roomNo, &students[i].contactType);

        if (students[i].contactType == PHONE) {
            fscanf(fp, "%s", students[i].contact.phone);
        } else {
            fscanf(fp, "%s", students[i].contact.email);
        }

        fscanf(fp, "%f %f", &students[i].feeDue, &students[i].feePaid);

        r = findRoom(rooms, students[i].roomNo);
        if (r != NULL) {
            r->occupied++;
        }
    }

    fclose(fp);
}

void saveData(struct Student students[], int count)
{
    FILE *fp = fopen("students.txt", "w");
    int i;

    if (fp == NULL) {
        perror("  Error saving students.txt");
        return;
    }

    fprintf(fp, "%d\n", count);
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %d %d ",
                students[i].id, students[i].name, students[i].age,
                students[i].roomNo, students[i].contactType);

        if (students[i].contactType == PHONE) {
            fprintf(fp, "%s ", students[i].contact.phone);
        } else {
            fprintf(fp, "%s ", students[i].contact.email);
        }

        fprintf(fp, "%.2f %.2f\n", students[i].feeDue, students[i].feePaid);
    }

    fclose(fp);
}


/* ACTIVITY LOG
Developed by: Haris Ismail */
void logActivity(char action[], int id)
{
    FILE *fp = fopen("activity.txt", "a");

    if (fp == NULL) {
        perror("  Error opening activity.txt");
        return;
    }

    fprintf(fp, "%s student ID %d\n", action, id);
    fclose(fp);
}



/* TEXT REPORT MAKING
Developed by: Haris Ismail */
void exportReport(struct Student students[], int count, struct Room rooms[])
{
    FILE *fp = fopen("hostel_report.txt", "w");
    int i;
    int bedsUsed = 0;
    float totalDue = 0, totalPaid = 0;
    struct Room *r;

    if (fp == NULL) {
        perror("  Error creating hostel_report.txt");
        return;
    }

    fputs("========== HOSTEL REPORT ==========\n\n", fp);
    fprintf(fp, "%-5s %-16s %-5s %-8s %-10s %-10s\n",
            "ID", "Name", "Room", "Type", "Due", "Paid");
    fputs("-----------------------------------------------------------\n", fp);

    for (i = 0; i < count; i++) {
        r = findRoom(rooms, students[i].roomNo);
        fprintf(fp, "%-5d %-16s %-5d %-8s %-10.2f %-10.2f\n",
                students[i].id, students[i].name, students[i].roomNo,
                roomTypeName(r->type), students[i].feeDue, students[i].feePaid);
        totalDue  = totalDue + students[i].feeDue;
        totalPaid = totalPaid + students[i].feePaid;
    }

    for (i = 0; i < MAX_ROOMS; i++) {
        bedsUsed = bedsUsed + rooms[i].occupied;
    }

    fprintf(fp, "\nTotal students   : %d\n", count);
    fprintf(fp, "Beds occupied    : %d of %d\n", bedsUsed, MAX_STUDENTS);
    fprintf(fp, "Total fees due   : Rs %.2f\n", totalDue);
    fprintf(fp, "Total fees paid  : Rs %.2f\n", totalPaid);
    fprintf(fp, "Total pending    : Rs %.2f\n", totalDue - totalPaid);

    fclose(fp);
    printf("\n  Report saved to hostel_report.txt\n");
}

