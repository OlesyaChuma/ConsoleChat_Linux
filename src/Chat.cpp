#include "Chat.h"
#include <iostream>
#include <limits>

Chat::Chat() : _storage("data") {
    // При создании объекта чата сразу загружаем состояние из файлов
    loadState();
}

void Chat::loadState() {
    _users = _storage.loadUsers();
    _messages = _storage.loadMessages();
}

void Chat::saveState() {
    _storage.saveUsers(_users);
    _storage.saveMessages(_messages);
}

bool Chat::isLoginTaken(const std::string& login) const {
    for (const auto& user : _users) {
        if (user.getLogin() == login) {
            return true;
        }
    }
    return false;
}

User* Chat::findUserByLogin(const std::string& login) {
    for (auto& user : _users) {
        if (user.getLogin() == login) {
            return &user;
        }
    }
    return nullptr;
}

const User* Chat::findUserByLogin(const std::string& login) const {
    for (const auto& user : _users) {
        if (user.getLogin() == login) {
            return &user;
        }
    }
    return nullptr;
}

void Chat::showWelcome() const {
    std::cout << "\n==============================\n";
    std::cout << "      Console Chat Linux\n";
    std::cout << "==============================\n";
}

void Chat::showGuestMenu() const {
    std::cout << "\n===== ГЛАВНОЕ МЕНЮ =====\n";
    std::cout << "1. Регистрация\n";
    std::cout << "2. Вход\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

void Chat::showUserMenu() const {
    std::cout << "\n===== МЕНЮ ПОЛЬЗОВАТЕЛЯ =====\n";
    std::cout << "1. Показать пользователей\n";
    std::cout << "2. Показать сообщения\n";
    std::cout << "3. Отправить сообщение\n";
    std::cout << "4. Выйти из аккаунта\n";
    std::cout << "0. Завершить программу\n";
    std::cout << "Выберите действие: ";
}

void Chat::registration() {
    std::string name;
    std::string login;
    std::string pass;

    std::cout << "\n=== Регистрация ===\n";

    std::cout << "Введите имя: ";
    std::getline(std::cin, name);

    if (name.empty()) {
        std::cout << "Имя не может быть пустым.\n";
        return;
    }

    std::cout << "Введите логин: ";
    std::getline(std::cin, login);

    if (login.empty()) {
        std::cout << "Логин не может быть пустым.\n";
        return;
    }

    if (isLoginTaken(login)) {
        std::cout << "Пользователь с таким логином уже существует.\n";
        return;
    }

    std::cout << "Введите пароль: ";
    std::getline(std::cin, pass);

    if (pass.empty()) {
        std::cout << "Пароль не может быть пустым.\n";
        return;
    }

    _users.emplace_back(name, login, pass);

    // После регистрации сразу сохраняем обновлённые данные
    saveState();

    std::cout << "Регистрация успешно завершена.\n";
}

bool Chat::login() {
    std::string login;
    std::string pass;

    std::cout << "\n=== Вход ===\n";

    std::cout << "Введите логин: ";
    std::getline(std::cin, login);

    std::cout << "Введите пароль: ";
    std::getline(std::cin, pass);

    User* user = findUserByLogin(login);

    if (user != nullptr && user->getPass() == pass) {
        _currentUser = user;
        std::cout << "Добро пожаловать, " << _currentUser->getName() << "!\n";
        return true;
    }

    std::cout << "Неверный логин или пароль.\n";
    return false;
}

void Chat::logout() {
    _currentUser = nullptr;
    std::cout << "Вы вышли из аккаунта.\n";
}

void Chat::showUsers() const {
    std::cout << "\n=== Список пользователей ===\n";

    if (_users.empty()) {
        std::cout << "Пользователи отсутствуют.\n";
        return;
    }

    for (const auto& user : _users) {
        std::cout << "Имя: " << user.getName()
                  << " | Логин: " << user.getLogin() << '\n';
    }
}

void Chat::showMessages() const {
    std::cout << "\n=== История сообщений ===\n";

    if (_messages.empty()) {
        std::cout << "Сообщений пока нет.\n";
        return;
    }

    bool hasVisibleMessages = false;

    for (const auto& msg : _messages) {
        if (msg.getReceiver() == "all" ||
            (_currentUser && msg.getReceiver() == _currentUser->getLogin()) ||
            (_currentUser && msg.getSender() == _currentUser->getLogin())) {

            hasVisibleMessages = true;

            std::cout << "От: " << msg.getSender()
                      << " | Кому: " << msg.getReceiver() << '\n';
            std::cout << "Текст: " << msg.getText() << "\n\n";
        }
    }

    if (!hasVisibleMessages) {
        std::cout << "Для вас пока нет сообщений.\n";
    }
}

void Chat::sendMessage() {
    if (_currentUser == nullptr) {
        std::cout << "Сначала необходимо войти в систему.\n";
        return;
    }

    std::string receiver;
    std::string text;

    std::cout << "\n=== Отправка сообщения ===\n";
    std::cout << "Введите логин получателя (или all для общего сообщения): ";
    std::getline(std::cin, receiver);

    if (receiver.empty()) {
        std::cout << "Получатель не может быть пустым.\n";
        return;
    }

    if (receiver != "all" && findUserByLogin(receiver) == nullptr) {
        std::cout << "Пользователь с таким логином не найден.\n";
        return;
    }

    std::cout << "Введите текст сообщения: ";
    std::getline(std::cin, text);

    if (text.empty()) {
        std::cout << "Сообщение не может быть пустым.\n";
        return;
    }

    _messages.emplace_back(text, _currentUser->getLogin(), receiver);

    // После отправки сообщения сохраняем историю
    saveState();

    std::cout << "Сообщение отправлено.\n";
}

void Chat::run() {
    showWelcome();

    bool running = true;

    while (running) {
        int choice = -1;

        if (_currentUser == nullptr) {
            showGuestMenu();
        } else {
            showUserMenu();
        }

        std::cin >> choice;

        // Очищаем поток ввода после ввода числа меню
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Нужно ввести число.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (_currentUser == nullptr) {
            switch (choice) {
                case 1:
                    registration();
                    break;
                case 2:
                    login();
                    break;
                case 0:
                    saveState();
                    running = false;
                    break;
                default:
                    std::cout << "Некорректный пункт меню.\n";
                    break;
            }
        } else {
            switch (choice) {
                case 1:
                    showUsers();
                    break;
                case 2:
                    showMessages();
                    break;
                case 3:
                    sendMessage();
                    break;
                case 4:
                    logout();
                    break;
                case 0:
                    saveState();
                    running = false;
                    break;
                default:
                    std::cout << "Некорректный пункт меню.\n";
                    break;
            }
        }
    }

    std::cout << "Работа программы завершена.\n";
}