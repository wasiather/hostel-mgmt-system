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

//menu display YASIR

//input validation (readnum, readamount) YASIR

//room initialize YASIR

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

//admit studennt addStudent Wasi
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

// search students WASI

// check out student SHARJEEL

// roomn status SHARJEEL

// fee payment SHARJEEL

// fee defaulters SHARJEEL

// file handling, loadData & saveData HARIS

// activityLog HARIS

// report making HARIS
