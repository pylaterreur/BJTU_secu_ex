
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      fprintf(stderr, "%s keyword plaintext\n", *argv);
      return (-1);
    }
  size_t i = 0;
  while (*argv[2])
    {
      if (isalnum(*argv[2]))
	{
	  if (argv[1][i] == '\0')
	    i = 0;
	  char c = (toupper(*argv[2]) - 'A' + toupper(argv[1][i]) - 'A') % 26 + 'A';
	  putchar(c);
	  ++i;
	}
      else
	putchar(*argv[2]);
      ++argv[2];
    }
  putchar('\n');
  return (0);
}
