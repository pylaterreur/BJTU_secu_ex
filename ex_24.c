
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

static void substitute(char *str, unsigned int key)
{
  while (*str)
    {
      if (islower(*str))
	*str = (*str + key - 'a') % 26 + 'a';
      else if (isupper(*str))
	*str = (*str + key - 'A') % 26 + 'A';
      ++str;
    }
}

int main(int argc, char *argv[])
{
  (void)argc;
  if (*++argv)
    {
      substitute(*argv, 4);
      puts(*argv);
    }
  return (EXIT_SUCCESS);
}
