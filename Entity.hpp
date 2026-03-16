/**
 * @file Entity.hpp
 * @brief Game entity class with move semantics
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace gameengine {

    class Entity {
    private:
        std::string name;
        int id;
        double x, y;                        // Position
        int health;
        std::vector<std::string> inventory;  // Items carried (a heavyweight resource)
        bool alive;                          // Flag to check if entity is valid (not moved-from)

        static int nextId;                   // Auto-incrementing ID
        static int entityCount;              // Tracks living (non-moved) entities

    public:
        // ============ Constructors ============

        /**
         * @brief Parameterized constructor
         * @param name The entity name
         * @param x X position (default: 0.0)
         * @param y Y position (default: 0.0)
         * @param health Starting health (default: 100, must be > 0)
         * @throws std::invalid_argument if health <= 0
         * Should auto-assign an ID from nextId++.
         * Should set alive = true and increment entityCount.
         * Should print: "Entity created: <name> (ID: <id>)"
         * Must be implemented in Entity.cpp.
         */
        Entity(const std::string& name, double x = 0.0, double y = 0.0, int health = 100);

        /**
         * @brief Move constructor
         * Transfers all resources from other to this.
         * After the move, other should be in a valid but empty state:
         *   name = "", id = -1, x = y = 0, health = 0, inventory cleared, alive = false.
         * Should NOT change entityCount (ownership transfers, not created).
         * Should print: "Entity moved: <name> (ID: <id>)"
         * Must be noexcept.
         */
        Entity(Entity&& other) noexcept;

        /**
         * @brief Move assignment operator
         * Transfers all resources from other to this.
         * Must handle self-assignment.
         * After the move, other should be in a valid but empty state.
         * If the previous value of this was alive, entityCount should be decremented
         * (the old entity is being replaced). The source's alive status transfers to this,
         * and the source becomes not alive. Net effect when both are alive: entityCount decreases by 1.
         * Should print: "Entity move-assigned: <name> (ID: <id>)" (using the NEW name/id after transfer)
         * Must be noexcept.
         */
        Entity& operator=(Entity&& other) noexcept;

        // Delete copy constructor and copy assignment (Entity is move-only)
        Entity(const Entity& other) = delete;
        Entity& operator=(const Entity& other) = delete;

        /**
         * @brief Destructor
         * Should only decrement entityCount if alive is true.
         * Should print: "Entity destroyed: <name> (ID: <id>)" if alive,
         *               "Entity destroyed: [moved-from]" if not alive.
         */
        ~Entity();

        // ============ Getters (inline) ============

        inline std::string getName() const { return name; }
        inline int getId() const { return id; }
        inline double getX() const { return x; }
        inline double getY() const { return y; }
        inline int getHealth() const { return health; }
        inline bool isAlive() const { return alive; }
        inline int getInventorySize() const { return static_cast<int>(inventory.size()); }

        // ============ Setters ============

        /**
         * @brief Set position
         */
        void setPosition(double x, double y);

        /**
         * @brief Take damage (reduces health, min 0)
         * @param amount Damage amount (must be > 0)
         * @throws std::invalid_argument if amount <= 0
         */
        void takeDamage(int amount);

        /**
         * @brief Heal (increases health)
         * @param amount Heal amount (must be > 0)
         * @throws std::invalid_argument if amount <= 0
         */
        void heal(int amount);

        // ============ Inventory ============

        /**
         * @brief Add an item to inventory
         * @param item The item name
         */
        void addItem(const std::string& item);

        /**
         * @brief Add an item using move semantics (rvalue reference)
         * @param item The item name (moved)
         */
        void addItem(std::string&& item);

        /**
         * @brief Check if entity has an item
         */
        bool hasItem(const std::string& item) const;

        /**
         * @brief Get all items as a const reference
         */
        const std::vector<std::string>& getInventory() const;

        // ============ Static ============

        /**
         * @brief Get current entity count
         */
        static int getEntityCount();

        /**
         * @brief Reset the ID counter (nextId) to 0.
         * Does NOT reset entityCount (which tracks living, non-moved-from entities).
         */
        static void resetIdCounter();

        // ============ Utility ============

        /**
         * @brief Get a description string
         * Format: "<name> (ID: <id>) at (<x>, <y>) HP: <health> Items: <count>"
         * x and y should be printed as integers (cast to int).
         */
        std::string toString() const;
    };

} // namespace gameengine

#endif // ENTITY_HPP