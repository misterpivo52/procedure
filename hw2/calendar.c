#include <stdio.h>

int getDaysInMonth(int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

int getFirstDay(int month) {
    int firstDays[] = {3, 6, 6, 2, 4, 0, 2, 5, 1, 3, 6, 1};
    return firstDays[month - 1];
}

void printCalendar(int month) {
    char* months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};

    printf("\n    %s 2025\n", months[month - 1]);
    printf("Su Mo Tu We Th Fr Sa\n");
    printf("--------------------\n");

    int firstDay = getFirstDay(month);
    int days = getDaysInMonth(month);

    for (int i = 0; i < firstDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);

        if ((day + firstDay) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int main() {
    int month;

    printf("Enter month (1-12): ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("Wrong month!\n");
        return 1;
    }

    printCalendar(month);

    return 0;
}