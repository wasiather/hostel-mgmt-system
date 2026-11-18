/* ================================================================
                      HOSTEL MANAGEMENT SYSTEM
 * Wasi Ather Siddiqui (CS26-122) : addStudent, findStudent, findRoom
 * Yasir Ali Junejo (CS26-135)    : admin login, main menu, input validation
 * Haris Ismail (CS26-141)        : file handling, union-based contact storage
 * Muhammad Sharjeel (CS26-131)   : fee and room management
 * ================================================================ */

/* ===== PART 1: HEADERS =====
 * Standard libraries for I/O and string handling. */
#include <stdio.h>
#include <string.h>

/* ===== PART 2: CONSTANTS & CONFIGURATION =====
 * Hostel limits, room/contact/type codes and fixed rent rates. */
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

/* ===== PART 3: ADMIN CREDENTIALS =====
 * Two stored admin accounts used by the login system.
 * Developed by: Yasir Ali Junejo (CS26-135) */
const char *ADMIN_IDS[ADMIN_COUNT]       = { "admin1",     "admin2"     };
const char *ADMIN_PASSWORDS[ADMIN_COUNT] = { "Hostel@123", "Warden@456" };

//Hi guys i am "Sharjeel the CODER"
