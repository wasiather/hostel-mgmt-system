/* ================================================================
                      HOSTEL MANAGEMENT SYSTEM
 * Wasi Ather Siddiqui (CS26-122) : addStudent, findStudent, findRoom, searchStudent, displayStudent
 * Yasir Ali Junejo (CS26-135)    : admin login, main menu, input validation (read funcs), room initialization
 * Haris Ismail (CS26-141)        : file handling, saveData, report making
 * Muhammad Sharjeel (CS26-131)   : fee, check out and room management system
 * ================================================================ */

/* INDIVIDUAL CONTRIBUTION
( headers, constants, main( ), prototypes & overall corrections are done mutually while sitting together )
Student 1 (Wasi Ather Siddiqui, CS26-122): - Developed the student admission module (addStudent) with duplicate ID checking and room allocation,
implemented the findStudent and findRoom pointer functions, searchStudent and displayStudent, and also prepared the test cases and documentation.
Student 2 (Yasir Ali Junejo, CS26-135): - Developed the admin login system (two admin accounts with a Try again / Exit option),
created the main menu structure and the input validation functions (readNumber, readAmount), roomInitialization, prepared the flowcharts, and conducted integration testing.
Student 3 (Haris Ismail, CS26-141): - Implemented all file handling operations (loadData, saveData, logActivity, exportReport), 
designed the students.txt record format, and handled the union-based contact storage (phone or email).
Student 4 (Muhammad Sharjeel, CS26-131): - Developed the fee and room management functions (payFees, showDefaulters, removeStudent, showRoomStatus),
created the documentation and test cases.
 */

// headers
#include <stdio.h>
#include <string.h>

// constants & configs
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

// prototypes

//main()
int main(){
}

//admin login system YASIR
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
//menu display YASIR
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
//input validation (readnum, readamount) YASIR
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
//room initialize YASIR
char *roomTypeName(int type)
{
    if (type == PREMIUM) 
    {
        return "Premium";
    }
    return "Normal";
}
// LOOKUP FUNCTIONS (findStudent and findRoom) WASI
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
    return NULL;

//admit student addStudent Wasi
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

// display students WASI
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


// search students WASi
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


// check out student SHARJEEL
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
// roomn status SHARJEEL
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
// fee payment SHARJEEL

// fee defaulters SHARJEEL

// file handling, loadData & saveData HARIS

// activityLog HARIS

// report making HARIS
