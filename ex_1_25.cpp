#include "Sales_item.h"
#include <iostream>

int main() {
  Sales_item total;

  if (std::cin >> total) {
    Sales_item current;
    while (std::cin >> total) {
      if (current.isbn() == total.isbn()) {
        current += total;
      } else {
        std::cout << total << std::endl;
        current = total;
      }
    }
    std::cout << total << std::endl;
  } else {
    std::cout << "No data?!" << std::endl;
    return -1;
  }

  return 0;
}
