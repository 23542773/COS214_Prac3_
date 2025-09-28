
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

Command::Command(ChatRoom* room, User* user, const std::string& msg) {
    // TODO: Initialize command
}

SendMessageCommand::SendMessageCommand(ChatRoom* room, User* user, const std::string& msg) 
    : Command(room, user, msg) {
    // TODO: Initialize send message command
}

void SendMessageCommand::execute() {
    // TODO: Execute send message command
}

LogMessageCommand::LogMessageCommand(ChatRoom* room, User* user, const std::string& msg) 
    : Command(room, user, msg) {
    // TODO: Initialize log message command
}

void LogMessageCommand::execute() {
    // TODO: Execute log message command
}

// ============= MEDIATOR PATTERN IMPLEMENTATIONS =============

std::vector<User*>& ChatRoom::getUsers() {
    // TODO: Return users vector
    return users;
}

std::vector<std::string>& ChatRoom::getChatHistory() {
    // TODO: Return chat history
    return chatHistory;
}

// CtrlCat Implementation
void CtrlCat::registerUser(User* user) {
    // TODO: Register user in CtrlCat room
}

void CtrlCat::removeUser(User* user) {
    // TODO: Remove user from CtrlCat room
}

void CtrlCat::sendMessage(const std::string& message, User* fromUser) {
    // TODO: Send message to all users in CtrlCat
}

void CtrlCat::saveMessage(const std::string& message, User* fromUser) {
    // TODO: Save message to CtrlCat history
}

Iterator* CtrlCat::createIterator() {
    // TODO: Create and return iterator for CtrlCat
    return nullptr;
}

// Dogorithm Implementation
void Dogorithm::registerUser(User* user) {
    // TODO: Register user in Dogorithm room
}

void Dogorithm::removeUser(User* user) {
    // TODO: Remove user from Dogorithm room
}

void Dogorithm::sendMessage(const std::string& message, User* fromUser) {
    // TODO: Send message to all users in Dogorithm
}

void Dogorithm::saveMessage(const std::string& message, User* fromUser) {
    // TODO: Save message to Dogorithm history
}

Iterator* Dogorithm::createIterator() {
    // TODO: Create and return iterator for Dogorithm
    return nullptr;
}

// ============= USER CLASS IMPLEMENTATIONS =============

User::User(const std::string& userName) {
    // TODO: Initialize user
}

User::~User() {
    // TODO: Clean up user resources
}

void User::addCommand(Command* command) {
    // TODO: Add command to queue
}

void User::executeAll() {
    // TODO: Execute all commands in queue
}

void User::setState(UserState* newState) {
    // TODO: Set user state
}

UserState* User::getState() const {
    // TODO: Return current state
    return nullptr;
}

std::string User::getName() const {
    // TODO: Return user name
    return "";
}

void User::joinChatRoom(ChatRoom* room) {
    // TODO: Join chat room
}

void User::leaveChatRoom(ChatRoom* room) {
    // TODO: Leave chat room
}

std::vector<ChatRoom*>& User::getChatRooms() {
    // TODO: Return chat rooms
    return chatRooms;
}

// User1 Implementation
User1::User1(const std::string& userName) : User(userName) {
    // TODO: Initialize User1
}

void User1::send(const std::string& message, ChatRoom* room) {
    // TODO: Implement User1 send behavior
}

void User1::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    // TODO: Implement User1 receive behavior
}

// User2 Implementation
User2::User2(const std::string& userName) : User(userName) {
    // TODO: Initialize User2
}

void User2::send(const std::string& message, ChatRoom* room) {
    // TODO: Implement User2 send behavior
}

void User2::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    // TODO: Implement User2 receive behavior
}

// User3 Implementation
User3::User3(const std::string& userName) : User(userName) {
    // TODO: Initialize User3
}

void User3::send(const std::string& message, ChatRoom* room) {
    // TODO: Implement User3 send behavior
}

void User3::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    // TODO: Implement User3 receive behavior
}