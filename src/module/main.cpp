#include <iostream>
#include <string>
#include <sstream>

int add(int x, int y) {
    return x + y;
}

int main() {
    std::string input;
    int x, y;
    while (true) {
        std::cout << "[In]: ";
        std::cin >> input;
        if (input == "quit" || input == "q") {
            break;
        }
        std::stringstream ss(input);
        ss >> x >> y;
        std::cout << "[Out]: " << x << " + " << y << " = " << add(x, y) << std::endl;
    }
    
    return 0;
}