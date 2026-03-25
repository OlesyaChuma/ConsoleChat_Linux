#include <iostream>
#include "Chat.h"

int main() {
    try {
        Chat chat;
        chat.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Произошла неизвестная ошибка.\n";
        return 1;
    }

    return 0;
}