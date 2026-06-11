#include <stdio.h>

int main()
{
    int ps, fs, faults = 0;

    printf("Enter number of pages and frames: ");
    scanf("%d %d", &ps, &fs);

    int p[ps], f[fs], recent[fs];

    printf("Enter page reference string:\n");
    for(int i = 0; i < ps; i++)
        scanf("%d", &p[i]);

    // Initialize frames
    for(int i = 0; i < fs; i++)
    {
        f[i] = -1;
        recent[i] = -1;
    }

    int count = 0;

    for(int i = 0; i < ps; i++)
    {
        int found = 0;

        // Check for page hit
        for(int j = 0; j < fs; j++)
        {
            if(f[j] == p[i])
            {
                found = 1;
                recent[j] = i;     // Update recent use
                break;
            }
        }

        // Page Fault
        if(!found)
        {
            faults++;

            // Empty frame available
            if(count < fs)
            {
                f[count] = p[i];
                recent[count] = i;
                count++;
            }
            else
            {
                // Find least recently used page
                int min = recent[0];
                int pos = 0;

                for(int j = 1; j < fs; j++)
                {
                    if(recent[j] < min)
                    {
                        min = recent[j];
                        pos = j;
                    }
                }

                f[pos] = p[i];
                recent[pos] = i;
            }
        }

        // Display frames
        printf("Page %d -> ", p[i]);

        for(int j = 0; j < fs; j++)
        {
            if(f[j] != -1)
                printf("%d ", f[j]);
        }

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}