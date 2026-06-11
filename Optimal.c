#include <stdio.h>

int main()
{
    int ps, fs, fault = 0;

    printf("Enter number of pages and frames: ");
    scanf("%d %d", &ps, &fs);

    int p[ps], f[fs];

    printf("Enter page reference string:\n");
    for(int i = 0; i < ps; i++)
        scanf("%d", &p[i]);

    // Initialize frames as empty
    for(int i = 0; i < fs; i++)
        f[i] = -1;

    int count = 0;

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

            // Empty frame available
            if(count < fs)
            {
                f[count++] = p[i];
            }
            else
            {
                int farthest = -1;
                int pos = -1;

                // Find page used farthest in future
                for(int j = 0; j < fs; j++)
                {
                    int foundFuture = 0;

                    for(int k = i + 1; k < ps; k++)
                    {
                        if(f[j] == p[k])
                        {
                            foundFuture = 1;

                            if(k > farthest)
                            {
                                farthest = k;
                                pos = j;
                            }
                            break;
                        }
                    }

                    // Page never used again
                    if(foundFuture == 0)
                    {
                        pos = j;
                        break;
                    }
                }

                f[pos] = p[i];
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