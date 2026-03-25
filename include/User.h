#pragma once
#include <string>

// Класс пользователя чата
class User {
private:
    std::string _name;   // Имя пользователя
    std::string _login;  // Логин пользователя
    std::string _pass;   // Пароль пользователя

public:
    User() = default;

    User(const std::string& name, const std::string& login, const std::string& pass)
        : _name(name), _login(login), _pass(pass) {}

    // Геттеры
    const std::string& getName() const { return _name; }
    const std::string& getLogin() const { return _login; }
    const std::string& getPass() const { return _pass; }

    // Сеттеры
    void setName(const std::string& name) { _name = name; }
    void setLogin(const std::string& login) { _login = login; }
    void setPass(const std::string& pass) { _pass = pass; }
};