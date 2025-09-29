/**
 * @file PetSpace.cpp
 * @author Franky Liu Jeandre Opperman
 * @brief 
 * @version 0.1
 * @date 2025-09-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "PetSpace.h"
#include <iostream>
#include <algorithm>

// ============= STATE PATTERN IMPLEMENTATIONS =============

/**
 * @brief Handles message reception when user is online
 * @param user Pointer to the user receiving the message
 * @param message The message content
 */
void Online::handleMessage(User* user, const std::string& message) {
    std::cout<<user->getName() << " [Online] received: "<<message <<std::endl;
}

/**
 * @brief Changes user state from online to another state
 * @param user Pointer to the user
 * @param newState Pointer to the new state
 */
void Online::changeState(User* user, UserState* newState) {
    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}

/**
 * @brief Returns the state name
 * @return String "Online"
 */
std::string Online::getStateName() const {
    return "Online";
}

// Offline State

/**
 * @brief Handles message reception when user is offline (cannot receive)
 * @param user Pointer to the user
 * @param message The message content (unused)
 */
void Offline::handleMessage(User* user, const std::string& message) {
    (void)message; // Silence unused parameter warning
    std::cout << user->getName() << " [Offline] cannot receive messages. " << std::endl;
}


/**
 * @brief Changes user state from offline to another state
 * @param user Pointer to the user
 * @param newState Pointer to the new state
 */
void Offline::changeState(User* user, UserState* newState) {
    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}


/**
 * @brief Returns the state name
 * @return String "Offline"
 */
std::string Offline::getStateName() const {
    return "Offline";
}

// Busy State

/**
 * @brief Handles message reception when user is busy (message stored)
 * @param user Pointer to the user
 * @param message The message content
 */
void Busy::handleMessage(User* user, const std::string& message) {
    std::cout<<user->getName() << " [Busy] unavailable. Message stored: " << message <<std::endl;
}


/**
 * @brief Changes user state from busy to another state
 * @param user Pointer to the user
 * @param newState Pointer to the new state
 */
void Busy::changeState(User* user, UserState* newState) {
    user->setState(newState);
    std::cout<< user->getName() <<"'s state changed to "<<newState->getStateName()<< std::endl;
}

/**
 * @brief Returns the state name
 * @return String "Busy"
 */
std::string Busy::getStateName() const {
    return "Busy";
}

// ============= ITERATOR PATTERN IMPLEMENTATIONS =============

/**
 * @brief Constructs a ChatHistoryIterator
 * @param history Pointer to the vector of chat messages
 */
ChatHistoryIterator::ChatHistoryIterator(std::vector<std::string>* history)
    : chatHistory(history), currentIndex(0){}
   
/**
 * @brief Checks if there are more messages to iterate
 * @return true if more messages exist, false otherwise
 */
bool ChatHistoryIterator::hasNext() {
    return chatHistory && currentIndex < static_cast<int>(chatHistory->size());
}

/**
 * @brief Returns the next message in the chat history
 * @return The next message string, or empty string if none
 */
std::string ChatHistoryIterator::next() {
    if (!hasNext())
    {
        return"";
    }
    return (*chatHistory)[currentIndex++];
}

/**
 * @brief Resets the iterator to the beginning
 */
void ChatHistoryIterator::reset() {
    currentIndex = 0;
}

// ============= COMMAND PATTERN IMPLEMENTATIONS =============

/**
 * @brief Constructs a Command object
 * @param room Pointer to the chat room
 * @param user Pointer to the user initiating the command
 * @param msg The message content
 */
Command::Command(ChatRoom* room, User* user, const std::string& msg) 
    : chatRoom(room), fromUser(user), message(msg) {
}

/**
 * @brief Constructs a SendMessageCommand
 * @param room Pointer to the chat room
 * @param user Pointer to the user sending the message
 * @param msg The message to send
 */
SendMessageCommand::SendMessageCommand(ChatRoom* room, User* user, const std::string& msg) 
    : Command(room, user, msg) {
}

/**
 * @brief Executes the send message command
 * 
 * Sends the message to all users in the chat room via the mediator
 */
void SendMessageCommand::execute() {
    if (chatRoom && fromUser) {
        chatRoom->sendMessage(message, fromUser);
    }
}

/**
 * @brief Constructs a LogMessageCommand
 * @param room Pointer to the chat room
 * @param user Pointer to the user whose message is being logged
 * @param msg The message to log
 */
LogMessageCommand::LogMessageCommand(ChatRoom* room, User* user, const std::string& msg) 
    : Command(room, user, msg) {
}

/**
 * @brief Executes the log message command
 * 
 * Saves the message to the chat room's history
 */
void LogMessageCommand::execute() {
    if (chatRoom && fromUser) {
        chatRoom->saveMessage(message, fromUser);
    }
}

// ============= MEDIATOR PATTERN IMPLEMENTATIONS =============

/**
 * @brief Gets the list of users in the chat room
 * @return Reference to the users vector
 */
std::vector<User*>& ChatRoom::getUsers() {
   return users;
}

/**
 * @brief Gets the chat history
 * @return Reference to the chat history vector
 */
std::vector<std::string>& ChatRoom::getChatHistory() {
    return chatHistory;
}

// CtrlCat Implementation

/**
 * @brief Registers a user with the CtrlCat room
 * @param user Pointer to the user to register
 * 
 * Prevents duplicate registrations
 */
void CtrlCat::registerUser(User* user) {
      if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined CtrlCat room!" << std::endl;
    }
}

/**
 * @brief Removes a user from the CtrlCat room
 * @param user Pointer to the user to remove
 */
void CtrlCat::removeUser(User* user) {
     auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left CtrlCat room!" << std::endl;
    }
}

/**
 * @brief Sends a message to all users in the CtrlCat room
 * @param message The message content
 * @param fromUser Pointer to the user sending the message
 * 
 * Message is delivered to all users except the sender
 */
void CtrlCat::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[CtrlCat] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

/**
 * @brief Saves a message to the CtrlCat room's history
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 */
void CtrlCat::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[CtrlCat] Message saved to history: " << fullMessage << std::endl;
}


/**
 * @brief Creates an iterator for the CtrlCat room's chat history
 * @return Pointer to a new ChatHistoryIterator
 */
Iterator* CtrlCat::createIterator() {
   return new ChatHistoryIterator(&chatHistory);
}

// Dogorithm Implementation

/**
 * @brief Registers a user with the Dogorithm room
 * @param user Pointer to the user to register
 * 
 * Prevents duplicate registrations
 */
void Dogorithm::registerUser(User* user) {
    if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined Dogorithm room!" << std::endl;
    }
}

/**
 * @brief Removes a user from the Dogorithm room
 * @param user Pointer to the user to remove
 */
void Dogorithm::removeUser(User* user) {
      auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left Dogorithm room!" << std::endl;
    }
}


/**
 * @brief Sends a message to all users in the Dogorithm room
 * @param message The message content
 * @param fromUser Pointer to the user sending the message
 * 
 * Message is delivered to all users except the sender
 */
void Dogorithm::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[Dogorithm] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}


/**
 * @brief Saves a message to the Dogorithm room's history
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 */
void Dogorithm::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[Dogorithm] Message saved to history: " << fullMessage << std::endl;
}

/**
 * @brief Creates an iterator for the Dogorithm room's chat history
 * @return Pointer to a new ChatHistoryIterator
 */
Iterator* Dogorithm::createIterator() {
    return new ChatHistoryIterator(&chatHistory);
}

// ============= USER CLASS IMPLEMENTATIONS =============

/**
 * @brief Constructs a User
 * @param userName The user's display name
 * @param admin Whether the user has admin privileges
 * 
 * Initializes user with Online state by default
 */
User::User(const std::string& userName, bool admin) : name(userName), currentState(new Online()), isAdmin(admin) {
    if (isAdmin) {
        std::cout << userName << " created as Admin user!" << std::endl;
    }
}
/**
 * @brief Destructs the User
 * 
 * Cleans up state and all queued commands
 */
User::~User() {
    delete currentState;
    for (Command* command : commandQueue) {
        delete command;
    }
}

/**
 * @brief Adds a command to the command queue
 * @param command Pointer to the command to add
 */
void User::addCommand(Command* command) {
    if (command) {
        commandQueue.push_back(command);
    }
}


/**
 * @brief Executes all commands in the queue
 * 
 * Executes each command sequentially, then clears and deletes them
 */
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


/**
 * @brief Sets the user's state
 * @param newState Pointer to the new state
 * 
 * Deletes the old state and replaces it with the new one
 */
void User::setState(UserState* newState) {
    if (currentState) {
        delete currentState;
    }
    currentState = newState;
}

/**
 * @brief Gets the user's current state
 * @return Pointer to the current UserState
 */
UserState* User::getState() const {
    return currentState;
}

/**
 * @brief Gets the user's name
 * @return The user's name string
 */
std::string User::getName() const {
    return name;
}

/**
 * @brief Joins a chat room
 * @param room Pointer to the chat room to join
 * 
 * Prevents joining the same room twice
 */
void User::joinChatRoom(ChatRoom* room) {
    if (room && std::find(chatRooms.begin(), chatRooms.end(), room) == chatRooms.end()) {
        chatRooms.push_back(room);
        room->registerUser(this);
    }
}

/**
 * @brief Leaves a chat room
 * @param room Pointer to the chat room to leave
 */
void User::leaveChatRoom(ChatRoom* room) {
    auto it = std::find(chatRooms.begin(), chatRooms.end(), room);
    if (it != chatRooms.end()) {
        chatRooms.erase(it);
        room->removeUser(this);
    }
}

/**
 * @brief Gets the list of chat rooms the user has joined
 * @return Reference to the chat rooms vector
 */
std::vector<ChatRoom*>& User::getChatRooms() {
    return chatRooms;
}

// User1 Implementation

/**
 * @brief Constructs a User1
 * @param userName The user's name
 */
User1::User1(const std::string& userName) : User(userName, false) {
}


/**
 * @brief Sends a message to a chat room
 * @param message The message content
 * @param room Pointer to the destination chat room
 * 
 * Creates SendMessageCommand and LogMessageCommand, then executes them
 */
void User1::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}

/**
 * @brief Receives a message from the chat room
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 * @param room Pointer to the chat room (unused)
 * 
 * Delegates message handling to the current state
 */
void User1::receive(const std::string& message, User* fromUser, ChatRoom*) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// User2 Implementation

/**
 * @brief Constructs a User2
 * @param userName The user's name
 */
User2::User2(const std::string& userName) : User(userName, false) {
}


/**
 * @brief Sends a message to a chat room
 * @param message The message content
 * @param room Pointer to the destination chat room
 * 
 * Creates SendMessageCommand and LogMessageCommand, then executes them
 */
void User2::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}

/**
 * @brief Receives a message from the chat room
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 * @param room Pointer to the chat room (unused)
 * 
 * Delegates message handling to the current state
 */
void User2::receive(const std::string& message, User* fromUser, ChatRoom*) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// User3 Implementation

/**
 * @brief Constructs a User3
 * @param userName The user's name
 */
User3::User3(const std::string& userName) : User(userName, false) {
}

/**
 * @brief Sends a message to a chat room
 * @param message The message content
 * @param room Pointer to the destination chat room
 * 
 * Creates SendMessageCommand and LogMessageCommand, then executes them
 */
void User3::send(const std::string& message, ChatRoom* room) {
    if (room) {
        // Create commands for sending and logging message
        addCommand(new SendMessageCommand(room, this, message));
        addCommand(new LogMessageCommand(room, this, message));
        
        // Execute all commands
        executeAll();
    }
}

/**
 * @brief Receives a message from the chat room
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 * @param room Pointer to the chat room (unused)
 * 
 * Delegates message handling to the current state
 */
void User3::receive(const std::string& message, User* fromUser, ChatRoom*) {
    if (currentState && fromUser) {
        currentState->handleMessage(this, message);
    }
}

// ============= ADMIN IMPLEMENTATIONS =============

/**
 * @brief Sets the user's admin status
 * @param admin true to grant admin privileges, false to revoke
 */
void User::setAdmin(bool admin) {
    isAdmin = admin;
    if (admin) {
        std::cout << name << " has been granted admin privileges!" << std::endl;
    }
}

/**
 * @brief Gets the user's admin status
 * @return true if user is admin, false otherwise
 */
bool User::getAdmin() const {
    return isAdmin;
}

/**
 * @brief Creates a custom chat room (admin only)
 * @param roomType The name/type of the room to create
 * @return Pointer to the new CustomChatRoom, or nullptr if user lacks permissions
 * 
 * Only users with admin privileges can create chat rooms
 */
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

/**
 * @brief Constructs a CustomChatRoom
 * @param name The custom name for the room
 */
CustomChatRoom::CustomChatRoom(const std::string& name) : roomName(name) {
}


/**
 * @brief Registers a user with the custom chat room
 * @param user Pointer to the user to register
 * 
 * Prevents duplicate registrations
 */
void CustomChatRoom::registerUser(User* user) {
    if (user && std::find(users.begin(), users.end(), user) == users.end()) {
        users.push_back(user);
        std::cout << user->getName() << " joined " << roomName << " room!" << std::endl;
    }
}


/**
 * @brief Removes a user from the custom chat room
 * @param user Pointer to the user to remove
 */
void CustomChatRoom::removeUser(User* user) {
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        std::cout << user->getName() << " left " << roomName << " room!" << std::endl;
    }
}

/**
 * @brief Sends a message to all users in the custom chat room
 * @param message The message content
 * @param fromUser Pointer to the user sending the message
 * 
 * Message is delivered to all users except the sender
 */
void CustomChatRoom::sendMessage(const std::string& message, User* fromUser) {
    std::cout << "[" << roomName << "] " << fromUser->getName() << ": " << message << std::endl;
    for (User* user : users) {
        if (user != fromUser) {
            user->receive(message, fromUser, this);
        }
    }
}

/**
 * @brief Saves a message to the custom chat room's history
 * @param message The message content
 * @param fromUser Pointer to the user who sent the message
 */
void CustomChatRoom::saveMessage(const std::string& message, User* fromUser) {
    std::string fullMessage = fromUser->getName() + ": " + message;
    chatHistory.push_back(fullMessage);
    std::cout << "[" << roomName << "] Message saved to history: " << fullMessage << std::endl;
}

/**
 * @brief Creates an iterator for the custom chat room's history
 * @return Pointer to a new ChatHistoryIterator
 */
Iterator* CustomChatRoom::createIterator() {
    return new ChatHistoryIterator(&chatHistory);
}

/**
 * @brief Gets the room's name
 * @return The custom room name string
 */
std::string CustomChatRoom::getRoomName() const {
    return roomName;
}