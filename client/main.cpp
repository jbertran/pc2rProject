#include <iostream>
#include <cstdlib>
#include "client.h"
#include "tools.h"
#include "../pc2rGUI/gui.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "Usage: client <host> <port>" << std::endl;
    std::exit;
  }
  
}
