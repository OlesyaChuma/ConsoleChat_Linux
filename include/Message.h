#pragma once
#include <string>

// Класс сообщения
class Message {
private:
    std::string _text;      // Текст сообщения
    std::string _sender;    // Логин отправителя
    std::string _receiver;  // Логин получателя или "all"

public:
    Message() = default;

    Message(const std::string& text, const std::string& sender, const std::string& receiver)
        : _text(text), _sender(sender), _receiver(receiver) {}

    // Геттеры
    const std::string& getText() const { return _text; }
    const std::string& getSender() const { return _sender; }
    const std::string& getReceiver() const { return _receiver; }

    // Сеттеры
    void setText(const std::string& text) { _text = text; }
    void setSender(const std::string& sender) { _sender = sender; }
    void setReceiver(const std::string& receiver) { _receiver = receiver; }
};