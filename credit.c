#include <stdio.h>

int find_sum(int temporary);
void check(int sum, int header, int counter, long number);

int main(void)
{
    // asking user for number
    long number;
    printf("Insert your credit card number: ");
    scanf("%ld", &number);    

    // variables declaration

    int counter = 0;
    // keeps count of the number of digits
    int sum = 0;
    // keeps track of the sum of the digits according to Luhn's algorithm
    int header;
    // registers the first two digits of the card
    int temporary;
    // temporarily registers the current number that is being used to calculate the sum

    // first check for INVALID card
    if (number > 5599999999999999 || number < 4000000000000)
    {
        printf("INVALID\n");
        return 0;
    }
    // exectuting algorithm on all the numbers until the first two
    while (number > 99)
    {
        // algorithm for odd numbers
        temporary = number % 10;
        sum += temporary;
        counter ++;
        number = (number - temporary) / 10;

        if (number < 100)
        {
            break;
        }

        // algorithm for even numbers
        temporary = (number % 10) * 2;
        sum += find_sum(temporary);
        counter ++;
        number = (number - (temporary / 2)) / 10;
    }

    // registers the first two numbers
    header = number;

    // algorithm for the first two numbers, the order depending on if the card has even or odd number of digits
    if (counter % 2 == 0)
    {
        temporary = number % 10;
        sum += temporary;
        counter ++;
        number = (number - temporary) / 10;
        temporary = number * 2;
        sum += find_sum(temporary);
    }
    else
    {
        temporary = (number % 10) * 2;
        sum += find_sum(temporary);
        counter++;
        number = (number - (temporary / 2)) / 10;
        sum += number;
    }
    counter++;

    // final check with all the data
    check(sum, header, counter, number);
}

int find_sum(int temporary)
{
    int sum = 0;
    if (temporary > 9)
    {
        switch (temporary)
        {
            case 10:
                sum += 1;
                break;
            case 12:
                sum += 3;
                break;
            case 14:
                sum += 5;
                break;
            case 16:
                sum += 7;
                break;
            case 18:
                sum += 9;
                break;
        }
    }
    else
    {
        sum += temporary;
    }
    return sum;
}

void check(int sum, int header, int counter, long number)
{
    if (sum % 10 == 0)
    {
        if ((header == 34 || header == 37) && counter == 15)
        {
            printf("AMEX\n");
        }
        else if (header < 56 && header > 50 && counter == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (number == 4 && (counter == 13 || counter == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}