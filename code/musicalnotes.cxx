#include <iostream>

int main()
{
  std::cout << "Ներմուծեք նոտայի տառը";
  char note;
  std::cin >> note;

  switch( note ) {
    case 'C':
      std::cout << "դո" << endl;
      break;
    case 'D':
      std::cout << "ռե" << endl;
      break;
    case 'E':
      std::cout << "մի" << endl;
      break;
    case 'F':
      std::cout << "ֆա" << endl;
      break;
    case 'G':
      std::cout << "սոլ" << endl;
      break;
    case 'A':
      std::cout << "լա" << endl;
      break;
    case 'B':
      std::cout << "սի" << endl;
      break;
    default:
      std::cerr << note << " տառով նոտա չի նշանակվում։" << std::endl;
  }

  return 0;
}
