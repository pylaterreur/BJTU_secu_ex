
#include <stdio.h>

static inline void ex_18_f(const char *str)
{
  for (; *str; ++str)
    {
      if (isalpha(*str))
	printf("0x%04x", *str >> 4 | *str << 4);
      else
	putchar(*str);
    }
  putchar('\n');
}

int main(void)
{
  ex_18_f("I am a HACKER");
}
