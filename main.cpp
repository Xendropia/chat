#include <iostream>
#include "chat.h"
#include "chat.cpp"

int main() {

    Chat<std::string> chat;
    User<std::string> *currentUser = nullptr;

    while (true) {
        std::cout << "1. Registration\n"
                     "2. Login\n"
                     "3. Logout\n"
                     "4. Private Message\n"
                     "5. Global Message\n"
                     "6. Exit\n\n";
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    std::string username, password, name;
                    std::cout << "Enter username: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;
                    std::cout << "Enter name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);

                    try {
                        chat.registerUser(username, password, name);
                        std::cout << "Registration successful.\n";
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 2: {
                    std::string username, password;
                    std::cout << "Enter username: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;

                    currentUser = chat.loginUser(username, password);

                    if (currentUser) {
                    } else {
                        std::cout << "Invalid username or password.\n";
                    }
                    break;
                }
                case 3:
                    currentUser = nullptr;
                    std::cout << "Logout successful.\n";
                    break;
                case 4: {
                    if (currentUser) {
                        std::string receiverUsername, message;
                        std::cout << "Enter recipient username: ";
                        std::cin >> receiverUsername;
                        std::cout << "Enter message: ";
                        std::cin.ignore();
                        std::getline(std::cin, message);

                        for (auto &user: chat.getUsers())
                            if (user.getUsername() == receiverUsername) {
                                chat.sendMessage(*currentUser, const_cast<User<std::string> &>(user), message);
                                std::cout << "Message sent to " << user.getName() << ".\n";
                                break;
                            }

                    } else {
                        std::cout << "You need to log in first.\n\n";
                    }
                    break;
                }
                case 5: {
                    if (currentUser) {
                        std::string message;
                        std::cout << "Enter global message: ";
                        std::cin.ignore();
                        std::getline(std::cin, message);
                        chat.broadcastMessage(*currentUser, message);
                        std::cout << "Global message sent.\n";
                    } else {
                        std::cout << "You need to log in first.\n";
                    }
                    break;
                }
                case 6:
                    return 0;
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}