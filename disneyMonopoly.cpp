#include <iostream>
#include <string>

using namespace std;

// Each node represents one Disneyland ride
struct RideNode {
    string rideName;
    int price;
    string owner;
    RideNode* next;

    RideNode(string name, int cost) {
        rideName = name;
        price = cost;
        owner = "Unowned";
        next = nullptr;
    }
};

// Circular linked list used as the Disneyland board
class DisneylandBoard {
private:
    RideNode* head;
    RideNode* tail;
    int rideCount;

public:
    DisneylandBoard() {
        head = nullptr;
        tail = nullptr;
        rideCount = 0;
    }

    // Deletes all nodes when the program ends
    ~DisneylandBoard() {
        if (head == nullptr) {
            return;
        }

        // Break the circle before deleting the nodes
        tail->next = nullptr;

        RideNode* current = head;

        while (current != nullptr) {
            RideNode* nextRide = current->next;
            delete current;
            current = nextRide;
        }
    }

    // Adds a ride to the end of the circular linked list
    void addRide(string name, int price) {
        RideNode* newRide = new RideNode(name, price);

        // If this is the first ride
        if (head == nullptr) {
            head = newRide;
            tail = newRide;

            // First node points back to itself
            tail->next = head;
        }
        else {
            // Add new ride after the current tail
            tail->next = newRide;

            // Make new ride the tail
            tail = newRide;

            // Connect the last ride back to the first ride
            tail->next = head;
        }

        rideCount++;
    }

    // Searches for a ride by name
    RideNode* findRide(string name) {
        if (head == nullptr) {
            return nullptr;
        }

        RideNode* current = head;

        do {
            if (current->rideName == name) {
                return current;
            }

            current = current->next;

        } while (current != head);

        return nullptr;
    }

    // Removes a ride from the circular linked list
    bool removeRide(string name) {
        if (head == nullptr) {
            return false;
        }

        RideNode* current = head;
        RideNode* previous = tail;

        do {
            if (current->rideName == name) {

                // If there is only one ride
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else {
                    // Skip over the ride being removed
                    previous->next = current->next;

                    // If removing the first ride
                    if (current == head) {
                        head = current->next;
                    }

                    // If removing the last ride
                    if (current == tail) {
                        tail = previous;
                    }

                    // Keep the list circular
                    tail->next = head;
                }

                delete current;
                rideCount--;

                return true;
            }

            previous = current;
            current = current->next;

        } while (current != head);

        return false;
    }

    // Prints every ride on the board one time
    void printBoard() const {
        if (head == nullptr) {
            cout << "The Disneyland board is empty." << endl;
            return;
        }

        RideNode* current = head;

        do {
            cout << current->rideName
                 << " | Price: $" << current->price
                 << " | Owner: " << current->owner
                 << endl;

            current = current->next;

        } while (current != head);
    }

    // Moves a player around the circular board
    RideNode* move(RideNode* position, int spaces) const {
        if (position == nullptr) {
            return head;
        }

        for (int i = 0; i < spaces; i++) {
            position = position->next;
        }

        return position;
    }

    // Returns the first ride on the board
    RideNode* getStart() const {
        return head;
    }

    // Returns the number of rides
    int size() const {
        return rideCount;
    }
};


// Stores information about each player
struct Player {
    string name;
    int money;
    RideNode* position;
};


// Attempts to buy the ride where the player landed
void tryToBuy(Player& player) {

    RideNode* ride = player.position;

    // Check if someone already owns the ride
    if (ride->owner != "Unowned") {
        cout << "  " << ride->rideName
             << " is already owned by "
             << ride->owner << "." << endl;

        return;
    }

    // Check if the player has enough money
    if (player.money < ride->price) {
        cout << "  " << player.name
             << " does not have enough money to buy "
             << ride->rideName << "." << endl;

        return;
    }

    // Player buys the ride
    ride->owner = player.name;
    player.money -= ride->price;

    cout << "  " << player.name
         << " bought "
         << ride->rideName
         << " for $" << ride->price
         << "." << endl;

    cout << "  " << player.name
         << " has $" << player.money
         << " left." << endl;
}


int main() {

    cout << "========================================" << endl;
    cout << "       DISNEYLAND RIDE MONOPOLY" << endl;
    cout << "========================================" << endl << endl;


    // =========================================
    // PART 1: TEST THE LINKED LIST
    // =========================================

    cout << "LINKED LIST TESTS" << endl;
    cout << "-----------------" << endl;

    DisneylandBoard testBoard;

    // Add three rides to test the add function
    testBoard.addRide("Test Ride A", 50);
    testBoard.addRide("Test Ride B", 75);
    testBoard.addRide("Test Ride C", 100);

    cout << "After adding three rides:" << endl;

    testBoard.printBoard();

    cout << endl;


    // Test the search function
    cout << "Searching for Test Ride B: ";

    if (testBoard.findRide("Test Ride B") != nullptr) {
        cout << "Found" << endl;
    }
    else {
        cout << "Not found" << endl;
    }


    // Test the remove function
    cout << "Removing Test Ride B: ";

    if (testBoard.removeRide("Test Ride B")) {
        cout << "Success" << endl;
    }
    else {
        cout << "Failed" << endl;
    }


    // Print again to prove Test Ride B was removed
    cout << endl;
    cout << "After removal:" << endl;

    testBoard.printBoard();


    // =========================================
    // PART 2: CREATE THE DISNEYLAND BOARD
    // =========================================

    DisneylandBoard board;

    board.addRide("Space Mountain", 100);
    board.addRide("Pirates of the Caribbean", 120);
    board.addRide("Haunted Mansion", 140);
    board.addRide("Indiana Jones Adventure", 160);
    board.addRide("Matterhorn Bobsleds", 180);
    board.addRide("Big Thunder Mountain", 200);
    board.addRide("It's a Small World", 220);
    board.addRide("Star Tours", 240);
    board.addRide("Mickey's Runaway Railroad", 260);
    board.addRide("The Rise of Resistance", 280);


    cout << endl << endl;

    cout << "INITIAL DISNEYLAND BOARD" << endl;
    cout << "-------------------------" << endl;

    board.printBoard();

    cout << endl;

    cout << "Total rides: "
         << board.size()
         << endl << endl;


    // =========================================
    // CREATE THE TWO PLAYERS
    // =========================================

    Player aleyah = {
        "Aleyah",
        1500,
        board.getStart()
    };

    Player jaz = {
        "Jaz",
        1500,
        board.getStart()
    };


    // Both players begin at Space Mountain.
    // These are the fixed movements for the 10 turns.
    int moves[10] = {
        2, 2, 4, 3, 6,
        5, 3, 7, 4, 1
    };


    // =========================================
    // 10 TURN DISNEYLAND MONOPOLY GAME
    // =========================================

    cout << "10 TURN DISNEYLAND MONOPOLY SIMULATION" << endl;
    cout << "--------------------------------------" << endl << endl;


    for (int turn = 0; turn < 10; turn++) {

        // Aleyah goes first.
        // Jaz goes second.
        Player& current =
            (turn % 2 == 0) ? aleyah : jaz;


        // Remember where the player started
        string oldRide = current.position->rideName;


        // Move the player
        current.position =
            board.move(current.position, moves[turn]);


        // Print the player's movement
        cout << "Turn " << turn + 1
             << ": " << current.name
             << " moves " << moves[turn]
             << " spaces from "
             << oldRide
             << " to "
             << current.position->rideName
             << "." << endl;


        // Try to buy the ride
        tryToBuy(current);

        cout << endl;
    }


    // =========================================
    // PRINT THE FINAL BOARD
    // =========================================

    cout << "FINAL DISNEYLAND BOARD" << endl;
    cout << "----------------------" << endl;

    board.printBoard();

    cout << endl;


    // =========================================
    // PRINT FINAL PLAYER INFORMATION
    // =========================================

    cout << "FINAL PLAYER STATUS" << endl;
    cout << "-------------------" << endl;

    cout << aleyah.name
         << " has $" << aleyah.money
         << " and finished at "
         << aleyah.position->rideName
         << "." << endl;


    cout << jaz.name
         << " has $" << jaz.money
         << " and finished at "
         << jaz.position->rideName
         << "." << endl;


    return 0;
}