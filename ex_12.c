
#include <stdio.h>

int main(void)
{
  /* 0b1001011101 */
  const unsigned int key = 605;
  const unsigned tab[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
  const unsigned tab2[] = {6, 3, 7, 4, 8, 5, 10, 9};
  unsigned int temp = 0, key1 = 0;

  /* PC-1 */
  for (size_t i = 0; i < sizeof(tab) / sizeof(*tab); ++i)
    {
      temp = (temp << 1) | (1 & (key >> (tab[i] - 1)));
    }
  /* Separation and left-shifting */
  {
    /* 31 = 0b11111 */
    const unsigned int temp1 = (temp & 31) << 1, temp2 = ((temp >> 5) & 31) << 1;
    temp = ((temp1 & 31) | temp1 >> 5) | (((temp2 & 31) | temp2 >> 5) << 5);
  }
  /* Selection */
  for (size_t i = 0; i < sizeof(tab2) / sizeof(*tab2); ++i)
    {
      key1 = (key1 << 1) | (1 & (temp >> (tab2[i] - 1)));
    }
  printf("key1 == %d\n", key1);
  return (0);
}
