
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

class EncSystem
{
public:
  EncSystem(unsigned int key, size_t size) : key_(key), size_(size)
  {}

  unsigned int Enc(unsigned int plaintext) const
  {
    return (((plaintext ^ key_) << ((2 << sizeof(key_)) - size_)) >> ((2 << sizeof(key_)) - size_));
  }

private:
  unsigned int key_;
  size_t size_;
};

static void print_bin(unsigned int nb, unsigned int sz)
{
  for (unsigned int i(1); i <= sz; ++i)
    cout << ((nb >> (sz - i)) & 1);
}

int main(void)
{
  unsigned int sz(17);
  EncSystem e(0b01000101111101101, sz);

  {
    const unsigned int plain_text(0b10011110100101010);
    print_bin(plain_text, sz);
    cout << endl;
    const unsigned int cipher(e.Enc(plain_text));
    print_bin(cipher, sz);
    cout << endl;
    print_bin(e.Enc(cipher), sz);
    cout << endl;
  }
}
