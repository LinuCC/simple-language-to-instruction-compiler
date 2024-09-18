#include <iostream>
#include <thread>

int main(int argc, char **argv) {
  std::cout << "hello world!" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));
  return 0;
}
