/**
 * @file PetSpace.hs
 * @author Franky Liu Jeandre Opperman
 * @brief 
 * @version 0.1
 * @date 2025-09-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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



/**
 * @class UserState
 * @brief Abstract base class for user states in the State pattern
 * 
 * Defines the interface for concrete state classes that handle user behavior
 * based on their current status (Online, Offline, Busy)
 */
class UserState {
public:
    virtual ~UserState() = default;
     /**
     * @brief Handles incoming messages based on current state
     * @param user Pointer to the user receiving the message
     * @param message The message content
     */
    virtual void handleMessage(User* user, const std::string& message) = 0;
     /**
     * @brief Changes the user's state
     * @param user Pointer to the user whose state is changing
     * @param newState Pointer to the new state
     */
    virtual void changeState(User* user, UserState* newState) = 0;
    /**
     * @brief Gets the name of the current state
     * @return String representation of the state name
     */
    virtual std::string getStateName() const = 0;
};


/**
 * @class Online
 * @brief Concrete state representing an online user
 * 
 * When online, users can receive and process messages normally
 */
class Online : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

/**
 * @class Offline
 * @brief Concrete state representing an offline user
 * 
 * When offline, users cannot receive messages
 */

class Offline : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

/**
 * @class Busy
 * @brief Concrete state representing a busy user
 * 
 * When busy, messages are stored but not immediately processed
 */

class Busy : public UserState {
public:
    void handleMessage(User* user, const std::string& message) override;
    void changeState(User* user, UserState* newState) override;
    std::string getStateName() const override;
};

// ============= ITERATOR PATTERN =============
/**
 * @class Iterator
 * @brief Abstract iterator interface for traversing collections
 * 
 * Provides a way to access elements of an aggregate object sequentially
 * without exposing its underlying representation
 */
class Iterator {
public:
    virtual ~Iterator() = default;
    /**
     * @brief Checks if there are more elements to iterate
     * @return true if more elements exist, false otherwise
     */
    virtual bool hasNext() = 0;
    /**
     * @brief Returns the next element in the collection
     * @return The next string element
     */
    virtual std::string next() = 0;
    /**
     * @brief Resets the iterator   to the beginning
     */
    virtual void reset() = 0;
};


/**
 * @class ChatHistoryIterator
 * @brief Concrete iterator for traversing chat history
 * 
 * Implements the Iterator interface to traverse through chat messages
 */
class ChatHistoryIterator : public Iterator {
private:
    std::vector<std::string>* chatHistory;  ///< Pointer to the chat history vector
    int currentIndex; ///< Current position in the iteration
    
public:
 /**
     * @brief Constructs a ChatHistoryIterator
     * @param history Pointer to the chat history vector
     */
    ChatHistoryIterator(std::vector<std::string>* history);
    bool hasNext() override;
    std::string next() override;
    void reset() override;
};

// ============= COMMAND PATTERN =============

/**
 * @class Command
 * @brief Abstract base class for commands in the Command pattern
 * 
 * Encapsulates a request as an object, allowing parameterization and queuing of requests
 */
class Command {
protected:
    ChatRoom* chatRoom;
    User* fromUser;
    std::string message;
    

public:
 /**
     * @brief Constructs a Command
     * @param room Pointer to the chat room
     * @param user Pointer to the user
     * @param msg The message string
     */
    Command(ChatRoom* room, User* user, const std::string& msg);
    virtual ~Command() = default;
    virtual void execute() = 0;
};


/**
 * @class SendMessageCommand
 * @brief Concrete command for sending messages to chat room users
 */
class SendMessageCommand : public Command {
public:
 /**
     * @brief Constructs a SendMessageCommand
     * @param room Pointer to the chat room
     * @param user Pointer to the user
     * @param msg The message string
     */
    SendMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    void execute() override;
};

/**
 * @class LogMessageCommand
 * @brief Concrete command for logging messages to chat history
 */
class LogMessageCommand : public Command {
public:
/**
     * @brief Constructs a LogMessageCommand
     * @param room Pointer to the chat room
     * @param user Pointer to the user
     * @param msg The message string
     */
    
    LogMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    void execute() override;
};

// ============= MEDIATOR PATTERN =============

/**
 * @class ChatRoom
 * @brief Abstract mediator class for managing user interactions
 * 
 * Centralizes communication between users, reducing coupling between them
 */
class ChatRoom {
protected:
    std::vector<User*> users;
    std::vector<std::string> chatHistory;
    
public:
    virtual ~ChatRoom() = default;

      /**
     * @brief Registers a user with the chat room
     * @param user Pointer to the user to register
     */
    virtual void registerUser(User* user) = 0;
      
    /**
     * @brief Removes a user from the chat room
     * @param user Pointer to the user to remove
     */
    virtual void removeUser(User* user) = 0;
    /**
     * @brief Sends a message to all users in the room
     * @param message The message to send
     * @param fromUser Pointer to the user sending the message
     */
    virtual void sendMessage(const std::string& message, User* fromUser) = 0;

     /**
     * @brief Saves a message to the chat history
     * @param message The message to save
     * @param fromUser Pointer to the user who sent the message
     */
    virtual void saveMessage(const std::string& message, User* fromUser) = 0;
    /**
     * @brief Creates an iterator for the chat history
     * @return Pointer to a new Iterator object
     */
    virtual Iterator* createIterator() = 0;

      /**
     * @brief Gets the list of users in the chat room
     * @return Reference to the users vector
     */
    std::vector<User*>& getUsers();
    /**
     * @brief Gets the chat history
     * @return Reference to the chat history vector
     */
    std::vector<std::string>& getChatHistory();
};


/**
 * @class CtrlCat
 * @brief Concrete mediator for the CtrlCat themed chat room
 */
class CtrlCat : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
};
/**
 * @class Dogorithm
 * @brief Concrete mediator for the Dogorithm themed chat room
 */
class Dogorithm : public ChatRoom {
public:
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
};

// ============= USER CLASSES =============
/**
 * @class User
 * @brief Abstract base class for all users in the system
 * 
 * Manages user state, chat room membership, and command execution
 */
class User {
protected:
    std::string name;
    std::vector<ChatRoom*> chatRooms;
    std::list<Command*> commandQueue;
    UserState* currentState;
    // EXTRA :: Admin
    bool isAdmin;  
    
public:
/**
     * @brief Constructs a User
     * @param userName The user's name
     * @param admin Whether the user is an admin (default: false)
     */
     User(const std::string& userName, bool admin = false);
    virtual ~User();
    /**
     * @brief Sends a message to a chat room
     * @param message The message content
     * @param room Pointer to the destination chat room
     */
    
     virtual void send(const std::string& message, ChatRoom* room) = 0;
    /**
     * @brief Receives a message from a chat room
     * @param message The message content
     * @param fromUser Pointer to the user who sent the message
     * @param room Pointer to the chat room
     */
     virtual void receive(const std::string& message, User* fromUser, ChatRoom* room) = 0;
    /**
     * @brief Adds a command to the command queue
     * @param command Pointer to the command to add
     */
    void addCommand(Command* command);
     /**
     * @brief Executes all commands in the queue
     */
    void executeAll();
    /**
     * @brief Sets the user's state
     * @param newState Pointer to the new state
     */
    void setState(UserState* newState);
    /**
     * @brief Gets the user's current state
     * @return Pointer to the current UserState
     */
    UserState* getState() const;
     
    /**
     * @brief Gets the user's name
     * @return The user's name
     */
    std::string getName() const;
     /**
     * @brief Joins a chat room
     * @param room Pointer to the chat room to join
     */
    void joinChatRoom(ChatRoom* room);
    /**
     * @brief Leaves a chat room
     * @param room Pointer to the chat room to leave
     */
    void leaveChatRoom(ChatRoom* room);
     /**
     * @brief Gets the list of chat rooms the user has joined
     * @return Reference to the chat rooms vector
     */
    std::vector<ChatRoom*>& getChatRooms();
    /**
     * @brief Sets the user's admin status
     * @param admin Whether the user should be an admin
     */
    void setAdmin(bool admin);
     /**
     * @brief Gets the user's admin status
     * @return true if user is admin, false otherwise
     */
    bool getAdmin() const;
    /**
     * @brief Creates a new chat room (admin only)
     * @param roomType The type/name of the room to create
     * @return Pointer to the new ChatRoom, or nullptr if not admin
     */
    ChatRoom* createChatRoom(const std::string& roomType);
};

/**
 * @class User1
 * @brief Concrete user implementation
 */
class User1 : public User {
public:
    /**
     * @brief Constructs a User1
     * @param userName The user's name
     */
    User1(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};
/**
 * @class User2
 * @brief Concrete user implementation
 */
class User2 : public User {
public:
    /**
     * @brief Constructs a User2
     * @param userName The user's name
     */
    User2(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};
/**
 * @class User3
 * @brief Concrete user implementation
 */

class User3 : public User {
public:
    /**
     * @brief Constructs a User3
     * @param userName The user's name
     */
    User3(const std::string& userName);
    void send(const std::string& message, ChatRoom* room) override;
    void receive(const std::string& message, User* fromUser, ChatRoom* room) override;
};

// ============= extra : CustomChatRoom CLASSES =============


/**
 * @class CustomChatRoom
 * @brief A customizable chat room with user-defined name
 * 
 * Allows admins to create themed chat rooms with custom names
 */
class CustomChatRoom : public ChatRoom {
private:
    std::string roomName;
    
public:
     /**
     * @brief Constructs a CustomChatRoom
     * @param name The name for the custom room
     */
    CustomChatRoom(const std::string& name);
    void registerUser(User* user) override;
    void removeUser(User* user) override;
    void sendMessage(const std::string& message, User* fromUser) override;
    void saveMessage(const std::string& message, User* fromUser) override;
    Iterator* createIterator() override;
    /**
     * @brief Gets the room's name
     * @return The room name
     */
    std::string getRoomName() const;
};
#endif // PETSPACE_H