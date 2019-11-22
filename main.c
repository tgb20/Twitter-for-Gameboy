#include <stdio.h>
#include <gb/gb.h>

void main()
{
    int curPos = 0;
    int i = 0;
    char c = 0;
    char tweet[128]; // Not enough memory for 240 characters
    printf("Welcome to Twitter for Gameboy\n#gameboytwitter\n\n");

    while (TRUE)
    {
        receive_byte();
        while (_io_status == IO_RECEIVING)
            ;
        if (_io_status == IO_IDLE)
        {
            c = (int)_io_in;

            if (c == 8) // char 8 is end tweet
            {
                for (i = 0; i < curPos; i++)
                {
                    printf("%c", tweet[i]);
                }
                curPos = 0;
                printf("\n\n");
            }
            else
            {
                tweet[curPos] = c;
                curPos += 1;
            }
        }
        else
        {
            printf("Error\n");
        }
    }
}