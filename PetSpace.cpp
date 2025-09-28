
#include "PetSpace.h"
#include <iostream>
#include <algorithm>

// ============= STATE PATTERN IMPLEMENTATIONS =============

// Online State
void Online::handleMessage(User* user, const std::string& message) {

    std::cout<<user->getName() << " [Online] received: "<<message <<std::endl;
}

void Online::changeState(User* user, UserState* newState) {

    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}

std::string Online::getStateName() const {
    
    return "Online";
}

// Offline State
void Offline::handleMessage(User* user, const std::string& message) {
    std::cout<<user->getName() << " [Offline] cannot receive messages. " <<std::endl;
}

void Offline::changeState(User* user, UserState* newState) {
    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}

std::string Offline::getStateName() const {
    
    return "Offline";
}

// Busy State
void Busy::handleMessage(User* user, const std::string& message) {
    std::cout<<user->getName() << " [Busy] unavailable. Message stored: " << message <<std::endl;
}

void Busy::changeState(User* user, UserState* newState) {
    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}

std::string Busy::getStateName() const {
   
    return "Busy";
}

// ============= ITERATOR PATTERN IMPLEMENTATIONS =============

ChatHistoryIterator::ChatHistoryIterator(std::vector<std::string>* history)
    : chatHistory(history), currentIndex(0){}

bool ChatHistoryIterator::hasNext() {
    
    return chatHistory && currentIndex < static_cast<int>(chatHistory->size());
}

std::string ChatHistoryIterator::next() {
    
    if (!hasNext())
    {
        return"";
    }
    
    return (*chatHistory)[currentIndex++];
}

void ChatHistoryIterator::reset() {
    currentIndex = 0;
}

// ============= COMMAND PATTERN IMPLEMENTATIONS =============

Command::Command(ChatRoom* room, User* user, const std::string& msg) 
    : chatRoom(room), fromUser(user), message(msg) {
}

void SendMessageCommand::execute() {
    if (chatRoom && fromUser) {
        chatRoom->sendMessage(message, fromUser);
    }
}

void LogMessageCommand::execute() {
    if (chatRoom && fromUser) {
        chatRoom->saveMessage(message, fromUser);
    }
}
LogMessageCommand::LogMessageCommand(ChatRoom* room, User* user, const std::string& msg) 
    : Command(room, user, msg) {
}

void LogMessageCommand::execute() {
    if (chatRoom && fromUser) {
        chatRoom->saveMessage(message, fromUser);
    }
}

// ============= MEDIATOR PATTERN IMPLEMENTATIONS =============

std::vector<User*>& ChatRoom::getUsers() {
   return users;
}

std::vector<std::string>& ChatRoom::getChatHistory() {
    return chatHistory;
}

// CtrlCat Implementation
void CtrlCat::registerUser(User* user) {
      if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined CtrlCat room!" << std::endl;
    }
}

void CtrlCat::removeUser(User* user) {
     auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left CtrlCat room!" << std::endl;
    }
}

void CtrlCat::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[CtrlCat] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

void CtrlCat::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[CtrlCat] Message saved to history: " << fullMessage << std::endl;
}

Iterator* CtrlCat::createIterator() {
   return new ChatHistoryIterator(&chatHistory);
}

// Dogorithm Implementation
void Dogorithm::registerUser(User* user) {
    if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined Dogorithm room!" << std::endl;
    }
}

void Dogorithm::removeUser(User* user) {
      auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left Dogorithm room!" << std::endl;
    }
}

void Dogorithm::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[Dogorithm] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

void Dogorithm::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[Dogorithm] Message saved to history: " << fullMessage << std::endl;
}

Iterator* Dogorithm::createIterator() {
    return new ChatHistoryIterator(&chatHistory);
}

// ============= USER CLASS IMPLEMENTATIONS =============

User::User(const std::string& userName, bool admin) : name(userName), isAdmin(admin), currentState(new Online()) {
    if (isAdmin) {
        std::cout << userName << " created as Admin user!" << std::endl;
    }
}

User::~User() {
    delete currentState;
    for (Command* command : commandQueue) {
        delete command;
    }
}

void User::addCommand(Command* command) {
    if (command) {
        commandQueue.push_back(command);
    }
}

void User::executeAll() {
    for (Command* command : commandQueue) {
        if (command) {
            command->execute();
        }
    }
    // Clear executed commands
    for (Command* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
}

void User::setState(UserState* newState) {
    if (currentState) {
        delete currentState;
    }
    currentState = newState;
}

UserState* User::getState() const {
    return currentState;
}

std::string User::getName() const {
    return name;
}

void User::joinChatRoom(ChatRoom* room) {
    if (room && std::find(chatRooms.begin(), chatRooms.end(), room) == chatRooms.end()) {
        chatRooms.push_back(room);
        room->registerUser(this);
    }
}

void User::leaveChatRoom(ChatRoom* room) {
    auto it = std::find(chatRooms.begin(), chatRooms.end(), room);
    if (it != chatRooms.end()) {
        chatRooms.erase(it);
        room->removeUser(this);
    }
}

std::vector<ChatRoom*>& User::getChatRooms() {
    return chatRooms;
}

// User1 Implementation
User1::User1(const std::string& userName) : User(userName, false) {
}

void User1::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}

void User1::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// User2 Implementation
User2::User2(const std::string& userName) : User(userName, false) {
}

void User2::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}

void User2::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// User3 Implementation
User3::User3(const std::string& userName) : User(userName, false) {
}

void User3::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}


void User3::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// ============= ADMIN IMPLEMENTATIONS =============

void User::setAdmin(bool admin) {
    isAdmin = admin;
    if (admin) {
        std::cout << name << " has been granted admin privileges!" << std::endl;
    }
}

bool User::getAdmin() const {
    return isAdmin;
}

ChatRoom* User::createChatRoom(const std::string& roomType) {
    if (!isAdmin) {
        std::cout << name << " does not have permission to create chat rooms!" << std::endl;
        return nullptr;
    }
    
    std::cout << "Chat room created by admin" << std::endl;
    
    // Create a custom room with any name
    return new CustomChatRoom(roomType);
}

// ============= Custom CLASS IMPLEMENTATIONS =============
CustomChatRoom::CustomChatRoom(const std::string& name) : roomName(name) {
}

void CustomChatRoom::registerUser(User* user) {
    if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined " << roomName << " room!" << std::endl;
    }
}

void CustomChatRoom::removeUser(User* user) {
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left " << roomName << " room!" << std::endl;
    }
}

void CustomChatRoom::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[" << roomName << "] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

void CustomChatRoom::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[" << roomName << "] Message saved to history: " << fullMessage << std::endl;
}

Iterator* CustomChatRoom::createIterator() {
    return new ChatHistoryIterator(&chatHistory);
}

std::string CustomChatRoom::getRoomName() const {
    return roomName;
}
