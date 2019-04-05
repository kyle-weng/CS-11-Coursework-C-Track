/*
 * Given a year from an input file, calculates and returns the date on which
 * Easter falls in that year. Output is printed to a text file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Given a year, calculates the date on which Easter falls in that year.
 * argument: year - the year
 * returns: an integer representing the date on which Easter falls. If it is
 *          negative, that date is in March. If positive, it is in April.
 */

int calculate_Easter_date(int year) {
    int goldenYear;        /* golden year in the 19 - year Metonic cycle */
    int century;           /* the century the year belongs to */
    int skippedLeapYears;  /* leap years skipped */
    int correctionFactor;  /* accounts for the fact that the moon doesn't
                              orbit the earth exactly 235 times in 19 years */
    int day;               /* March ((-day) mod 7 + 7) is a Sunday */
    int epact;             /* specifies when a full moon occurs */
    int fullMoon;          /* this day in March is a calendar full moon */
    int finalDate;         /* final date, which is ultimately returned */

    /*
     * The allowable years are in the range 1582 to 39999; if the input is
     * outside of this range, the calculate_Easter_date function should return
     * 0.
     */
    if ((year < 1582) || (year > 39999)) {
        return 0;
    }

    goldenYear = (year % 19) + 1; /* golden year in the 19 - year
                                     Metonic cycle */

    century = (year / 100) + 1; /* the century the year belongs to */

    skippedLeapYears = ((3 * century) / 4) - 12; /* leap years skipped */

    correctionFactor = (((8 * century) + 5) / 25) - 5; /* accounts for the fact
        that the moon doesn't orbit the earth exactly 235 times in 19 years */

    day = ((5 * year) / 4) - skippedLeapYears - 10; /* March ((-day) mod 7 + 7)
                                                       is a Sunday */

    epact = ((11 * goldenYear) + 20 + correctionFactor - skippedLeapYears) % 30;
        /* specifies when a full moon occurs */

    if ((epact == 25 && goldenYear > 11) || epact == 24) {
        epact++;
    }
    
    fullMoon = 44 - epact; /* this day in March is a calendar full moon */
    if (fullMoon < 21) {
        fullMoon = fullMoon + 30;
    }

    fullMoon = fullMoon + 7 - ((day + fullMoon) % 7);
        /* a Sunday after full moon */

    if (fullMoon > 31) {
        finalDate = fullMoon - 31;
    }
    else {
        finalDate = -1 * fullMoon;
    }
    return finalDate;
}

int main(void) {
    int year;
    int returnDate;
    int yearDummy;

    while(1) {
        yearDummy = scanf("%d", &year);
        if (yearDummy == EOF) {
            break;
        }
        returnDate = calculate_Easter_date(year);
        if (returnDate == 0) {
            fprintf(stderr, "Range error: method returned 0.\n");
        }
        else if (returnDate > 0) {
            printf("%d - %s %d\n", year, "April", returnDate);
        }
        else if (returnDate < 0) {
            returnDate *= -1;
            printf("%d - %s %d\n", year, "March", returnDate);
        }
    }
    return 0;
}
