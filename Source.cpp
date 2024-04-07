#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define d 256

void search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0, t = 0;
	int h = 1;

	// The value of h would be pow(d, M - 1) % q
	for (i = 0; i < M - 1; i++)
		h = (h*d) % q;
	// Caculate the hash value of pattern and first window of text
	for (i = 0; i < M; i++)
	{
		p = (d*p + pat[i]) % q;
		t = (d*t + txt[i]) % q;
	}

	for (i = 0; i <= N - M; i++)
	{
		// Check the hash values of current window of text
		// and pattern, if the hash values match then only
		// check for characters one by one
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (txt[i + j] != pat[j])
					break;
			}

			if (j == M)
				printf("Patterns found at index %d \n", i);
		}
		// Caculate hash value for next window of text: remove
		// leading ditgit and add trailing digit
		if (i < N - M)
		{
			t = (d*(t - txt[i] * h) + txt[i + M]) % q;
			// We might get negative value of t, converting it 
			// to positive
			if (t < 0)
				t = (t + q);
		}
	}
}

void main()
{
	char txt[6] = "ABDCB";
	char pat[3] = "DC";
	int q = 11;
	search(pat, txt, q);
	system("pause>0");
}