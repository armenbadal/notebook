#include <iostream>

int main()
{
  std::cout << "Ներմուծեք որևէ ամբողջ թիվ. ";
  int number = 0;
  std::cin >> number;

  if( number > 0 )
    std::cout << number << "-ը դրական է։" << std::endl;
  else if( number < 0 )
    std::cout << number << "-ը բացասական է։" << std::endl;
  else
    std::cout << "ներմուծված թիվը զրո է։" << std::endl;

  return 0;
}
