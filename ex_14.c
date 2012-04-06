
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

static char *railfence(const char *str, size_t len, char *buf, size_t railn)
{
  char *p = buf;

  if (railn == 0)
    return (NULL);
  if (railn == 1)
    return (strcpy(buf, str));
  for (unsigned int j = 0; j < railn; ++j)
    {
      unsigned int increment[] = {
	(railn - 1 - j) * 2 ? (railn - 1 - j) * 2 : j * 2,
	j * 2 ? j * 2 : (railn - 1 - j) * 2
      };
      for (unsigned int i = j, sign = 0; i < len;)
	{
	  *buf = str[i];
	  ++buf;
	  i += increment[sign];
	  sign = !sign;
	}
    }
  *buf = '\0';
  return (p);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      fprintf(stderr, "Usage: %s rail plaintext\n", *argv);
      return (EXIT_FAILURE);
    }
  char *str;
  {
    size_t len = strlen(argv[2]);
    str = malloc(len + 1);
    if (str == NULL)
      {
	perror(*argv);
	return (EXIT_FAILURE);
      }
    size_t i = 0;
    while (*argv[2] != '\0')
      {
	if (isalnum(*argv[2]))
	  {
	    str[i] = *argv[2];
	    ++i;
	  }
	argv[2]++;
      }
    str[i] = '\0';
  }
  size_t len = strlen(str);
  char *buf = malloc(len + 1);
  if (buf == NULL)
    {
      perror(*argv);
      return (EXIT_FAILURE);
    }
  errno = 0;
  long int railn = strtol(argv[1], NULL, 10);
  if (errno || railn <= 0)
    {
      fprintf(stderr, "Usage: %s rail plaintext\n", *argv);
      return (EXIT_FAILURE);
    }
  railfence(str, len, buf, railn);
  puts(buf);
  free(str);
  free(buf);
  return (EXIT_SUCCESS);
}
