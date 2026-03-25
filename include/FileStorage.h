#pragma once

#include <vector>
#include <filesystem>
#include "User.h"
#include "Message.h"

// Класс для работы с файлами:
// - создание каталога и файлов
// - установка прав доступа
// - сохранение и загрузка пользователей и сообщений
class FileStorage {
private:
    std::filesystem::path _dataDir;      // Каталог хранения данных
    std::filesystem::path _usersFile;    // Файл пользователей
    std::filesystem::path _messagesFile; // Файл сообщений

    // Подготовка каталога и файлов
    void ensureStorage();

public:
    explicit FileStorage(const std::filesystem::path& dataDir = "data");

    void saveUsers(const std::vector<User>& users) const;
    void saveMessages(const std::vector<Message>& messages) const;

    std::vector<User> loadUsers() const;
    std::vector<Message> loadMessages() const;
};