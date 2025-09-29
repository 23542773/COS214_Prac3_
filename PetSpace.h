#ifndef PETSPACE_H
#define PETSPACE_H

#include <string>
#include <vector>
#include <list>

// Forward declarations
class User;
class ChatRoom;
class Command;
class UserState;
class Iterator;

// ============= STATE PATTERN =============
class UserState {
public:
    virtual ~UserState() = default;
    virtual void handleMessage(User* user, const std::string& message) = 0;
    virtual void changeState(User* user, UserState* newState) = 0;
    virtual std::string getStateName() const = 0;
};

class Online : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

class Offline : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

class Busy : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

// ============= ITERATOR PATTERN =============
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual std::string next() = 0;
    virtual void reset() = 0;
};

class ChatHistoryIterator : public Iterator {
private:
    std::vector<std::string>* chatHistory;
    int currentIndex;
    
public:
    ChatHistoryIterator(std::vector<std::string>* history);
    bool hasNext() override;
    std::string next() override;
    void reset() override;
};

// ============= COMMAND PATTERN =============
class Command {
protected:
    ChatRoom* chatRoom;
    User* fromUser;
    std::string message;
    
public:
    Command(ChatRoom* room, User* user, const std::string& msg);
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class SendMessageCommand : public Command {
public:
    SendMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    void execute() override;
};

class LogMessageCommand : public Command {
public:
    LogMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    void execute() override;
};

// ============= MEDIATOR PATTERN =============
class ChatRoom {
protected:
    std::vector<User*> users;
    std::vector<std::string> chatHistory;
    
public:
    virtual ~ChatRoom() = default;
    virtual void registerUser(User* user) = 0;
    virtual void removeUser(User* user) = 0;
    virtual void sendMessage(const std::string& message, User* fromUser) = 0;
    virtual void saveMessage(const std::string& message, User* fromUser) = 0;
    virtual Iterator* createIterator() = 0;
    std::vector<User*>& getUsers();
    std::vector<std::string>& getChatHistory();
};

class CtrlCat : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
};

class Dogorithm : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
};

// ============= USER CLASSES =============
class User {
protected:
    std::string name;
    std::vector<ChatRoom*> chatRooms;
    std::list<Command*> commandQueue;
    UserState* currentState;
    // EXTRA :: Admin
    bool isAdmin;  
    
public:
     User(const std::string& userName, bool admin = false);
    virtual ~User();
    
    virtual void send(const std::string& message, ChatRoom* room) = 0;
    virtual void receive(const std::string& message, User* fromUser, ChatRoom* room) = 0;
    
    void addCommand(Command* command);
    void executeAll();
    void setState(UserState* newState);
    UserState* getState() const;
    std::string getName() const;
    void joinChatRoom(ChatRoom* room);
    void leaveChatRoom(ChatRoom* room);
    std::vector<ChatRoom*>& getChatRooms();

    void setAdmin(bool admin);
    bool getAdmin() const;
    ChatRoom* createChatRoom(const std::string& roomType);
};

class User1 : public User {
public:
    User1(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};

class User2 : public User {
public:
    User2(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};

class User3 : public User {
public:
    User3(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};

// ============= extra : CustomChatRoom CLASSES =============

class CustomChatRoom : public ChatRoom {
private:
    std::string roomName;
    
public:
    CustomChatRoom(const std::string& name);
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
    std::string getRoomName() const;
};
#endif // PETSPACE_H