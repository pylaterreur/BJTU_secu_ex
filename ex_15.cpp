
#include <cstdlib>
#include <string>
#include <map>
#include <iostream>
#include <cctype>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      std::cerr << "Usage: " << *argv << " keyword plaintext" << endl;
      return (-1);
    }
  // let's say that argv[1] contains the keyword written in a nice way!
  std::map<char, std::string> m;
  for (size_t i(0); *argv[2]; ++argv[2])
    {
      if (!std::isalnum(*argv[2]))
	continue ;
      if (argv[1][i] == '\0')
	i = 0;
      m[argv[1][i]] += std::toupper(*argv[2]);
      ++i;
    }
  for (auto e: m)
    cout << e.second;
  cout << endl;
}
