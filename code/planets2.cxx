#include <iostream>
#include <string>
#include <vector>

int main()
{
  using namespace std;

  vector<string> planets;
  planets.push_back("Փայլածու");  // Մերկուրի
  planets.push_back("Արուսյակ");  // Վեներա
  planets.push_back("Երկիր");
  planets.push_back("Հրատ");      // Մարս
  planets.push_back("Լուսնթագ");  // Յուպիտեր
  planets.push_back("Երեւակ");    // Սատուրն
  planets.push_back("Ուրան");
  planets.push_back("Նեպտուն");

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
