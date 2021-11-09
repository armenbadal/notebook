#include <iostream>

int main()
{
  std::cout << "Ներմուծեք որևէ ամբողջ թիվ. ";
  int number = 0;
  std::cin >> number;

  if( number % 3 == 0 )
    std::cout << number << "-ը երեքի պատիկ է" << std::endl;

  return 0;
}
