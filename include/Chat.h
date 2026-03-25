#pragma once

#include <vector>
#include <string>
#include "User.h"
#include "Message.h"
#include "FileStorage.h"

// Основной класс чата
class Chat {
private:
    std::vector<User> _users;           // Зарегистрированные пользователи
    std::vector<Message> _messages;     // История сообщений
    FileStorage _storage;               // Работа с файлами
    User* _currentUser = nullptr;       // Текущий авторизованный пользователь

    bool isLoginTaken(const std::string& login) const;
    User* findUserByLogin(const std::string& login);
    const User* findUserByLogin(const std::string& login) const;

    void showWelcome() const;
    void showGuestMenu() const;
    void showUserMenu() const;

public:
    Chat();

    void loadState();
    void saveState();

    void registration();
    bool login();
    void logout();

    void showUsers() const;
    void showMessages() const;
    void sendMessage();

    void run();
};