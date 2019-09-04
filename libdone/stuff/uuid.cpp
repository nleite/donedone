// most code from: https://lowrey.me/guid-generation-in-c-11/
// build: g++ -arch x86_64 -std=c++1z -o bin/uuid
#include <iostream>
#include <random>
#include <sstream>
#include <string>

unsigned int random_char() {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);
  return dis(gen);
}

std::string generate_hex(const unsigned int len) {
  std::stringstream ss;
  for (auto i = 0; i < len; i++) {
    const auto rc = random_char();
    std::stringstream hexstream;
    hexstream << std::hex << rc;
    auto hex = hexstream.str();
    ss << (hex.length() < 2 ? '0' + hex : hex);
  }
  return ss.str();
}

int main() {
  std::cout << generate_hex(4) << '-' << generate_hex(2) << '-'
            << generate_hex(2) << '-' << generate_hex(2) << '-'
            << generate_hex(6) << std::endl;
}
