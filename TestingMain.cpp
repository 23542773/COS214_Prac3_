//u24673898
//u23542773

#include "PetSpace.h"
#include <iostream>
#include <cassert>

void testStatePattern() {
    std::cout << "\n=== TESTING STATE PATTERN ===" << std::endl;
    
    // Create user and test initial state
    User1* user = new User1("TestUser");
    std::cout << "Initial state: " << user->getState()->getStateName() << std::endl;
    
    // Test Online state
    std::cout << "\n--- Testing Online State ---" << std::endl;
    user->getState()->handleMessage(user, "Hello while online");
    
    // Change to Offline state
    std::cout << "\n--- Testing Offline State ---" << std::endl;
    UserState* offlineState = new Offline();
    user->getState()->changeState(user, offlineState);
    user->getState()->handleMessage(user, "Hello while offline");
    
    // Change to Busy state
    std::cout << "\n--- Testing Busy State ---" << std::endl;
    UserState* busyState = new Busy();
    user->getState()->changeState(user, busyState);
    user->getState()->handleMessage(user, "Hello while busy");
    
    // Change back to Online
    std::cout << "\n--- Changing back to Online ---" << std::endl;
    UserState* onlineState = new Online();
    user->getState()->changeState(user, onlineState);
    user->getState()->handleMessage(user, "Hello online again");
    
    delete user;
    std::cout << "State Pattern Test Completed!\n" << std::endl;
}

void testIteratorPattern() {
    std::cout << "\n=== TESTING ITERATOR PATTERN ===" << std::endl;
    
    // Create chat room and users
    CtrlCat* room = new CtrlCat();
    User1* user1 = new User1("Alice");
    User2* user2 = new User2("Bob");
    
    // Join room and send messages
    user1->joinChatRoom(room);
    user2->joinChatRoom(room);
    
    user1->send("First message", room);
    user2->send("Second message", room);
    user1->send("Third message", room);
    
    // Test iterator
    std::cout << "\n--- Testing Chat History Iterator ---" << std::endl;
    Iterator* iterator = room->createIterator();
    
    std::cout << "Iterating through chat history:" << std::endl;
    while (iterator->hasNext()) {
        std::cout << "- " << iterator->next() << std::endl;
    }
    
    // Test reset functionality
    std::cout << "\n--- Testing Iterator Reset ---" << std::endl;
    iterator->reset();
    std::cout << "After reset, first message: " << iterator->next() << std::endl;
    
    // Test hasNext when empty
    std::cout << "Has more messages: " << (iterator->hasNext() ? "Yes" : "No") << std::endl;
    
    delete iterator;
    delete user1;
    delete user2;
    delete room;
    std::cout << "Iterator Pattern Test Completed!\n" << std::endl;
}

void testCommandPattern() {
    std::cout << "\n=== TESTING COMMAND PATTERN ===" << std::endl;
    
    // Create room and users
    Dogorithm* room = new Dogorithm();
    User1* sender = new User1("CommandSender");
    User2* receiver = new User2("CommandReceiver");
    
    sender->joinChatRoom(room);
    receiver->joinChatRoom(room);
    
    std::cout << "\n--- Testing Command Execution ---" << std::endl;
    
    // Test individual commands
    std::cout << "Creating individual commands:" << std::endl;
    Command* sendCmd = new SendMessageCommand(room, sender, "Test send command");
    Command* logCmd = new LogMessageCommand(room, sender, "Test log command");
    
    std::cout << "Executing send command:" << std::endl;
    sendCmd->execute();
    
    std::cout << "Executing log command:" << std::endl;
    logCmd->execute();
    
    // Test command queue through user send
    std::cout << "\n--- Testing Command Queue ---" << std::endl;
    sender->send("Message via command queue", room);
    
    // Test multiple commands
    std::cout << "\n--- Testing Multiple Commands ---" << std::endl;
    sender->addCommand(new SendMessageCommand(room, sender, "Queued message 1"));
    sender->addCommand(new LogMessageCommand(room, sender, "Queued message 1"));
    sender->addCommand(new SendMessageCommand(room, sender, "Queued message 2"));
    sender->addCommand(new LogMessageCommand(room, sender, "Queued message 2"));
    
    std::cout << "Executing all queued commands:" << std::endl;
    sender->executeAll();
    
    delete sendCmd;
    delete logCmd;
    delete sender;
    delete receiver;
    delete room;
    std::cout << "Command Pattern Test Completed!\n" << std::endl;
}

void testMediatorPattern() {
    std::cout << "\n=== TESTING MEDIATOR PATTERN ===" << std::endl;
    
    // Create different types of chat rooms
    CtrlCat* ctrlCatRoom = new CtrlCat();
    Dogorithm* dogorithmRoom = new Dogorithm();
    
    // Create users
    User1* user1 = new User1("Alice");
    User2* user2 = new User2("Bob");
    User3* user3 = new User3("Charlie");
    
    std::cout << "\n--- Testing CtrlCat Room ---" << std::endl;
    user1->joinChatRoom(ctrlCatRoom);
    user2->joinChatRoom(ctrlCatRoom);
    
    user1->send("Hello from CtrlCat!", ctrlCatRoom);
    user2->send("Hi Alice!", ctrlCatRoom);
    
    std::cout << "\n--- Testing Dogorithm Room ---" << std::endl;
    user2->joinChatRoom(dogorithmRoom);
    user3->joinChatRoom(dogorithmRoom);
    
    user2->send("Hello from Dogorithm!", dogorithmRoom);
    user3->send("Woof woof!", dogorithmRoom);
    
    std::cout << "\n--- Testing Multi-room User ---" << std::endl;
    user2->send("I'm in both rooms!", ctrlCatRoom);
    user2->send("Speaking in Dogorithm now", dogorithmRoom);
    
    std::cout << "\n--- Testing User Removal ---" << std::endl;
    user1->leaveChatRoom(ctrlCatRoom);
    user2->send("Alice left the room", ctrlCatRoom);
    
    delete user1;
    delete user2;
    delete user3;
    delete ctrlCatRoom;
    delete dogorithmRoom;
    std::cout << "Mediator Pattern Test Completed!\n" << std::endl;
}

void testAdminFunctionality() {
    std::cout << "\n=== TESTING ADMIN FUNCTIONALITY ===" << std::endl;
    
    // Create regular user and admin
    User1* regularUser = new User1("RegularUser");
    User1* admin = new User1("AdminUser");
    admin->setAdmin(true);
    
    std::cout << "\n--- Testing Permission Control ---" << std::endl;
    ChatRoom* failedRoom = regularUser->createChatRoom("ShouldFail");
    assert(failedRoom == nullptr);
    
    std::cout << "\n--- Testing Admin Room Creation ---" << std::endl;
    ChatRoom* customRoom1 = admin->createChatRoom("GamingLounge");
    ChatRoom* customRoom2 = admin->createChatRoom("StudyGroup");
    ChatRoom* customRoom3 = admin->createChatRoom("MusicFans");
    
    std::cout << "\n--- Testing Custom Rooms ---" << std::endl;
    User2* user1 = new User2("Gamer");
    User3* user2 = new User3("Student");
    
    user1->joinChatRoom(customRoom1);
    user2->joinChatRoom(customRoom2);
    admin->joinChatRoom(customRoom1);
    admin->joinChatRoom(customRoom2);
    
    user1->send("Love this gaming room!", customRoom1);
    user2->send("Perfect for studying!", customRoom2);
    admin->send("Admin checking in!", customRoom1);
    
    delete regularUser;
    delete admin;
    delete user1;
    delete user2;
    delete customRoom1;
    delete customRoom2;
    delete customRoom3;
    std::cout << "Admin Functionality Test Completed!\n" << std::endl;
}

void testIntegratedScenario() {
    std::cout << "\n=== TESTING INTEGRATED SCENARIO ===" << std::endl;
    
    // Create admin and regular users
    User1* admin = new User1("SuperAdmin");
    admin->setAdmin(true);
    
    User1* alice = new User1("Alice");
    User2* bob = new User2("Bob");
    User3* charlie = new User3("Charlie");
    
    // Admin creates custom rooms
    ChatRoom* techRoom = admin->createChatRoom("TechTalk");
    ChatRoom* casualRoom = admin->createChatRoom("CasualChat");
    
    // Users join rooms
    alice->joinChatRoom(techRoom);
    bob->joinChatRoom(techRoom);
    bob->joinChatRoom(casualRoom);
    charlie->joinChatRoom(casualRoom);
    admin->joinChatRoom(techRoom);
    
    std::cout << "\n--- Multi-room Conversation ---" << std::endl;
    alice->send("Anyone know about design patterns?", techRoom);
    bob->send("Yes! We're using them right now!", techRoom);
    
    // Bob switches context to casual room
    bob->send("Hey Charlie, how's it going?", casualRoom);
    charlie->send("Great! This system is cool!", casualRoom);
    
    std::cout << "\n--- Testing State Changes During Conversation ---" << std::endl;
    UserState* busyState = new Busy();
    alice->setState(busyState);
    
    bob->send("Alice, are you there?", techRoom);
    
    UserState* onlineState = new Online();
    alice->setState(onlineState);
    bob->send("Alice, welcome back!", techRoom);
    
    std::cout << "\n--- Testing Chat History ---" << std::endl;
    Iterator* techIterator = techRoom->createIterator();
    std::cout << "TechTalk history:" << std::endl;
    while (techIterator->hasNext()) {
        std::cout << "  " << techIterator->next() << std::endl;
    }
    
    Iterator* casualIterator = casualRoom->createIterator();
    std::cout << "CasualChat history:" << std::endl;
    while (casualIterator->hasNext()) {
        std::cout << "  " << casualIterator->next() << std::endl;
    }
    
    // Cleanup
    delete techIterator;
    delete casualIterator;
    delete alice;
    delete bob;
    delete charlie;
    delete admin;
    delete techRoom;
    delete casualRoom;
    
    std::cout << "Integrated Scenario Test Completed!\n" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    PETSPACE DESIGN PATTERNS TESTING   " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Test each pattern individually
    testStatePattern();
    testIteratorPattern();
    testCommandPattern();
    testMediatorPattern();
    
    // Test admin functionality
    testAdminFunctionality();
    
    // Test integrated scenario
    testIntegratedScenario();
    
    std::cout << "========================================" << std::endl;
    std::cout << "         ALL TESTS COMPLETED!          " << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}