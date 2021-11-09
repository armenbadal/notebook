#include <iostream>

int main()
{
  std::cout << "Ներմուծեք որևէ ամբողջ թիվ. ";
  int number = 0;
  std::cin >> number;

  if( (number & 0x01) == 0x01 )
    std::cout << number << "-ը կենտ է։" << std::endl;
  else
    std::cout << number << "-ը զույգ է։" << std::endl;

  return 0;
}
