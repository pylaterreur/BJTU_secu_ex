
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  if (*++argv != nullptr)
    {
      typedef std::function<char (char)> typefunc;

      std::string str(*argv);
      std::vector<typefunc> toto = {
	([](unsigned char c){ return (c & 127); }),
	([](unsigned char c){ return (c | 127); }),
	([](unsigned char c){ return (c ^ 127); })
	//	,([](unsigned char c){ return (c); })
      };
      for_each(toto.begin(), toto.end(), [&str](const typefunc &t) { for_each(str.begin(), str.end(), [&t](unsigned char c){ cout << t(c);}); cout << endl; });
    }
}
