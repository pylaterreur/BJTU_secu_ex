
#include <exception>
#include <iostream>
#include <string>
#include <cctype>
#include <boost/bimap.hpp>

using std::cout;
using std::cerr;
using std::endl;

class Playfair
{
  typedef boost::bimap<unsigned int, char> bm_type;
public:
  explicit Playfair(const std::string &keyword)
  {
    unsigned int i(0);
    for (auto e: keyword)
      {
	if (std::isalpha(e))
	  {
	    e = std::toupper(e);
	    if (e == 'J')
	      map_.insert(bm_type::value_type(i, 'I'));
	    else
	      map_.insert(bm_type::value_type(i, e));
	    if (i < map_.size())
	      ++i;
	  }
      }
    for (char c('A'); c <= 'Z'; ++c)
      {
	if (c == 'J')
	  continue ;
	map_.insert(bm_type::value_type(i, c));
	if (i < map_.size())
	  ++i;
      }
  }

  std::string Encrypt(const std::string &plaintext) const
  {
    std::string cipher;
    const auto end_right = map_.right.end();
    const std::string::const_iterator end = plaintext.end();

    (void)plaintext;
    for (std::string::const_iterator c = plaintext.begin(); c != end;)
      {
	char first, second;

	while (c != end && !std::isalpha(*c))
	  ++c;
	if (c == end)
	  break ;
	first = std::toupper(*c++);
	while (c != end && !std::isalpha(*c))
	  ++c;
	second = std::toupper((c == end || std::toupper(*c) == first ? 'x' : *c++));

	if (first == 'J')
	  first = 'I';
	if (second == 'J')
	  second = 'I';

	//	cout << first << second << endl;

	EncryptPair(first, second);

	//	cout << first << second << endl;


	cipher += first;
	cipher += second;
      }
    return (cipher);
  }

private:
  unsigned char tab_[25];
  bm_type map_;

  void EncryptPair(char &first, char &second) const
  {
    unsigned int i1(map_.right.find(first)->second),
      i2(map_.right.find(second)->second);

    if (i1 / 5 == i2 / 5)
      {
	i1 = 5 * (i1 / 5) + (i1 + 1) % 5;
	i2 = 5 * (i2 / 5) + (i2 + 1) % 5;
      }
    else if (i1 % 5 == i2 % 5)
      {
	i1 = 5 * ((i1 / 5 + 1) % 5) + i1 % 5;
	i2 = 5 * ((i2 / 5 + 1) % 5) + i2 % 5;
      }
    else
      {
	unsigned int temp(i1);
	i1 = 5 * (i1 / 5) + i2 % 5;
	i2 = 5 * (i2 / 5) + temp % 5;
      }
    first = map_.left.find(i1)->second;
    second = map_.left.find(i2)->second;
  }
};

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      std::cerr << "usage: " << *argv << " keyword plaintext" << endl;
      return (-1);
    }

  Playfair playfair(argv[1]);

  cout <<
    playfair.Encrypt(argv[2])
       << endl;
}
