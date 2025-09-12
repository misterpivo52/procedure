#include <stdio.h>
#include <stdlib.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysInMonth[month - 1];
}


int getFirstDayOfMonth(int month, int year) {
    //Zeller's algorithm
    if (month < 3) {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;

    int dayOfWeek = (1 + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    return (dayOfWeek + 5) % 7;
}

void printCalendar(int month, int year) {
    const char* monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("\n");
    printf("     %s %d\n", monthNames[month - 1], year);
    printf(" Su Mo Tu We Th Fr Sa\n");
    printf("____________________\n");

    int firstDay = getFirstDayOfMonth(month, year);
    int daysInMonth = getDaysInMonth(month, year);

    for (int i = 0; i < firstDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= daysInMonth; day++) {
        printf("%3d", day);

        if ((day + firstDay) % 7 == 0) {
            printf("\n");
        }
    }

    if ((daysInMonth + firstDay) % 7 != 0) {
        printf("\n");
    }
    printf("\n");
}

int main() {
    int month = 9;
    int year = 2024;

    printf("Calendar for a specific date:\n");
    printCalendar(month, year);

    //input
    printf("Enter month (1-12): ");
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        printf("Invalid month! Please enter a number between 1 and 12.\n");
        return 1;
    }

    printf("Enter year: ");
    if (scanf("%d", &year) != 1 || year < 1) {
        printf("Invalid year! Please enter a positive number.\n");
        return 1;
    }

    printf("\nCalendar for user input:\n");
    printCalendar(month, year);

    return 0;
}