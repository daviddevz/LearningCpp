/*
The Challenge: The Smart Network Packet Processor
Scenario: You are writing a simulation for a network router. This router receives
"Packets" (simulated data).

1. Packets have a header that must be decoded using bitwise operators.

2. Packets must be owned by a processing queue (cannot be copied, only moved).

3. Packets might need to be shared with multiple "Logger" or "Audit" systems.

You need a "Cache" that holds a reference to a packet but knows if the packet has been deleted.

Your Task Requirements
1. Bitwise Operations & Data Types: Create a struct called PacketHeader. It should have a single
uint16_t field called flags. Implement methods (or standalone functions) to parse this integer
using bitwise operators to extract:

    a. Version (First 3 bits): A number from 0-7.

    b. Type (Next 4 bits): An ID from 0-15.

    c. Encrypted (8th bit): A boolean (0 or 1).

2. Object Lifetime & Unique Pointers: Create a class called Packet.

    a. It should contain a PacketHeader and a std::string for the payload.

    b. Constraint: The Packet class should report when it is created and destroyed
    (print to console in constructor and destructor).

    c. Create a function generatePacket() that returns a std::unique_ptr<Packet>. This simulates a
    factory creating a packet that must be moved, not copied.

3. Shared & Weak Pointers (The Core Logic):

    a. Create a container (like std::vector) that holds std::shared_ptr<Packet>. This represents
    your "Active Processing" list.

    b. Create a global or separate std::weak_ptr<Packet> variable called last_packet_cache.

The Logic Loop:

1. Generate a unique packet.

2. Promote it to a shared_ptr and add it to your "Active" list.

3. Assign this packet to the last_packet_cache (weak pointer).

4. Demonstrate accessing the packet via the weak_ptr (you must check if it expired first using .lock()).

5. Clear the "Active" list (destroying the shared pointers).

6. Try to access the last_packet_cache again. It should now be expired/dangling.
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// --- BITWISE OPERATIONS ---
// 16-bit Flags Layout:
// [0-2] Version (3 bits)
// [3-6] Type (4 bits)
// [7]   IsEncrypted (1 bit)
struct PacketHeader {
    uint16_t flags;

    PacketHeader(uint16_t f) : flags(f) {}

    int getVersion() const {
        // TODO: Return first 3 bits
        int mask = (1 << 2 | 1 << 1 | 1); //0b111
        int result = flags & mask;
        return result;
    }

    int getType() const {
        // TODO: Return next 4 bits
        int flags = flags >> 3;
        int mask = (1 << 3 | 1 << 2 | 1 << 1 | 1); //0b1111
        int result = flags & mask;
        return result;
    }

    bool isEncrypted() const {
        // TODO: Return the 8th bit
        int flag = flags >> 7; 
        int mask = 1; //0b1
        int result = flag & mask;
        return result;
    }
};

// --- CLASS & OBJECT LIFETIME ---
class Packet {
public:
    PacketHeader header;
    std::string payload;

    Packet(uint16_t f, std::string p) : header(f), payload(p) {
        std::cout << "Packet Created: " << payload << "\n";
    }

    ~Packet() {
        std::cout << "Packet Destroyed: " << payload << "\n";
    }
};

// --- FUNCTIONS & SMART POINTERS ---
std::unique_ptr<Packet> createPacket(uint16_t flags, std::string name) {
    // TODO: Create and return a unique_ptr
    std::unique_ptr<Packet> packet = std::make_unique<Packet>(flags, name);
    return packet;
}

int main() {
    // 1. Bitwise Test
    // Create a header with specific bits set and verify your getVersion/getType functions work.
    uint16_t rawData = 0b0000000010111011; // Example binary
    PacketHeader h(rawData);

    std::cout<<"Test getVersion: "<< (1<<1 | 1) <<"\n";
    std::cout<<"getVersion Result: "<< h.getVersion() <<"\n";

    std::cout<<"Test getType: "<< (1<<2 | 1<<1 | 1) <<"\n";
    std::cout<<"getType Result: "<< h.getType() <<"\n";

    // Print the decoded values...
    std::cout<<"Decoded values: "<<h.isEncrypted() <<"\n";

    // 2. Memory Model & Pointer Test
    std::vector<std::shared_ptr<Packet>> activeProcessors;
    std::weak_ptr<Packet> monitor;

    {
        std::cout << "--- Scope Start ---\n";
        // TODO:
        // A. Call createPacket to get a unique_ptr
        std::unique_ptr<Packet> packet = createPacket(rawData, "Hello World");
        // B. Move/Convert it into a shared_ptr and push to activeProcessors
        std::shared_ptr<Packet> sharedPacket = std::move(packet);
        activeProcessors.push_back(sharedPacket);
        // C. Set 'monitor' to point to this packet
        monitor = *(activeProcessors.end()-1);
        // D. Use 'monitor.lock()' to print the packet payload ONLY if it exists
        if (monitor.lock() != nullptr){
            std::cout<<"Payload: "<<(monitor.lock())->payload <<"\n";
        }
    } // End of scope

    std::cout << "--- Scope End ---\n";

    // TODO: 
    // Clear activeProcessors.
    activeProcessors.clear();
    // Try to use 'monitor.lock()' again. It should fail (return null).
    if(monitor.lock() == nullptr){
        std::cout<<"Failed\n";
    }
    return 0;
}