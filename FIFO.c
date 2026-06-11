#include <stdio.h>

int main()
{
    int ps, fs, fault = 0;

    printf("Enter page size and frame size: ");
    scanf("%d %d", &ps, &fs);

    int p[ps], f[fs];

    printf("Enter page reference string:\n");
    for(int i = 0; i < ps; i++)
        scanf("%d", &p[i]);

    // Initialize frames
    for(int i = 0; i < fs; i++)
        f[i] = -1;

    int pos = 0;      // Points to oldest page
    int count = 0;    // Number of filled frames

    for(int i = 0; i < ps; i++)
    {
        int found = 0;

        // Check page hit
        for(int j = 0; j < fs; j++)
        {
            if(p[i] == f[j])
            {
                found = 1;
                break;
            }
        }

        // Page Fault
        if(!found)
        {
            fault++;

            if(count < fs)
            {
                f[count++] = p[i];
            }
            else
            {
                f[pos] = p[i];
                pos = (pos + 1) % fs;
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

    printf("\nTotal Page Faults = %d\n", fault);

    return 0;
}