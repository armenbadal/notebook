#include <array>
#include <iostream>
#include <string>

int main()
{
  using namespace std;

  const array<string, 8> planets{
    "Փայլածու",  // Մերկուրի
    "Արուսյակ",  // Վեներա
    "Երկիր",
    "Հրատ",      // Մարս
    "Լուսնթագ",  // Յուպիտեր
    "Երեւակ",    // Սատուրն
    "Ուրան",
    "Նեպտուն"
  };

  cout << "Ներմուծեք մոլորակի համարը. ";
  int index = 0;
  cin >> index;

  if( index >= 1 && index <= 8 )
    cout << index << " համարով մոլորակը "
         << planets[index-1] << "ն է" << endl;
  else
    cout << index << " համարով մոլորակ չկա։" << endl;

  return 0;
}
