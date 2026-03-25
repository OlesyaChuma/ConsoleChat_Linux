#include "FileStorage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

FileStorage::FileStorage(const fs::path& dataDir)
    : _dataDir(dataDir),
      _usersFile(_dataDir / "users.txt"),
      _messagesFile(_dataDir / "messages.txt") {
    ensureStorage();
}

void FileStorage::ensureStorage() {
    // Если каталога для данных нет — создаём его
    if (!fs::exists(_dataDir)) {
        fs::create_directories(_dataDir);
    }

    // Права на каталог:
    // только владелец может читать, писать и заходить в него
    fs::permissions(
        _dataDir,
        fs::perms::owner_all,
        fs::perm_options::replace
    );

    // Если файла пользователей нет — создаём его
    if (!fs::exists(_usersFile)) {
        std::ofstream out(_usersFile);
        out.close();
    }

    // Если файла сообщений нет — создаём его
    if (!fs::exists(_messagesFile)) {
        std::ofstream out(_messagesFile);
        out.close();
    }

    // Права на users.txt:
    // только владелец может читать и записывать
    fs::permissions(
        _usersFile,
        fs::perms::owner_read | fs::perms::owner_write,
        fs::perm_options::replace
    );

    // Права на messages.txt:
    // только владелец может читать и записывать
    fs::permissions(
        _messagesFile,
        fs::perms::owner_read | fs::perms::owner_write,
        fs::perm_options::replace
    );
}

void FileStorage::saveUsers(const std::vector<User>& users) const {
    std::ofstream out(_usersFile, std::ios::trunc);

    if (!out.is_open()) {
        throw std::runtime_error("Не удалось открыть users.txt для записи");
    }

    // Формат хранения:
    // name|login|password
    for (const auto& user : users) {
        out << user.getName() << '|'
            << user.getLogin() << '|'
            << user.getPass() << '\n';
    }
}

void FileStorage::saveMessages(const std::vector<Message>& messages) const {
    std::ofstream out(_messagesFile, std::ios::trunc);

    if (!out.is_open()) {
        throw std::runtime_error("Не удалось открыть messages.txt для записи");
    }

    // Формат хранения:
    // text|sender|receiver
    for (const auto& message : messages) {
        out << message.getText() << '|'
            << message.getSender() << '|'
            << message.getReceiver() << '\n';
    }
}

std::vector<User> FileStorage::loadUsers() const {
    std::vector<User> users;
    std::ifstream in(_usersFile);

    if (!in.is_open()) {
        return users;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string name;
        std::string login;
        std::string pass;

        std::getline(ss, name, '|');
        std::getline(ss, login, '|');
        std::getline(ss, pass, '|');

        if (!name.empty() && !login.empty()) {
            users.emplace_back(name, login, pass);
        }
    }

    return users;
}

std::vector<Message> FileStorage::loadMessages() const {
    std::vector<Message> messages;
    std::ifstream in(_messagesFile);

    if (!in.is_open()) {
        return messages;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string text;
        std::string sender;
        std::string receiver;

        std::getline(ss, text, '|');
        std::getline(ss, sender, '|');
        std::getline(ss, receiver, '|');

        if (!text.empty()) {
            messages.emplace_back(text, sender, receiver);
        }
    }

    return messages;
}