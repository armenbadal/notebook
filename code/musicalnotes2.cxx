#include <iostream>
#include <string>

int main()
{
  std::cout << "Ներմուծեք նոտայի տառը. ";
  char note;
  std::cin >> note;

  std::string name;
  switch( note ) {
    case 'C':
    case 'c':
      name = "դո";
      break;
    case 'D':
    case 'd':
      name = "ռե";
      break;
    case 'E':
    case 'e':
      name = "մի";
      break;
    case 'F':
    case 'f':
      name = "ֆա";
      break;
    case 'G':
    case 'g':
      name = "սոլ";
      break;
    case 'A':
    case 'a':
      name = "լա";
      break;
    case 'B':
    case 'b':
      name = "սի";
      break;
    default:
      std::cerr << "Այդպիսի նոտա չկա։" << std::endl;
  }

  if( !name.empty() )
    std::cout << name << std::endl;

  return 0;
}
