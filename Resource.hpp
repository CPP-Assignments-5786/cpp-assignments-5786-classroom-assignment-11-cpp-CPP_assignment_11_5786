/**
 * @file Resource.hpp
 * @brief Shared resource class using shared_ptr
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include <memory>
#include <iostream>

namespace gameengine {

    class Resource {
    private:
        std::string name;
        std::string type;       // "texture", "sound", "shader", etc.
        int sizeBytes;          // Size in bytes
        bool loaded;            // Whether the resource is loaded in memory

        static int resourceCount;

    public:
        // ============ Constructor ============

        /**
         * @brief Parameterized constructor
         * @param name Resource name
         * @param type Resource type
         * @param sizeBytes Size in bytes (must be > 0)
         * @throws std::invalid_argument if sizeBytes <= 0
         * Should set loaded = true and increment resourceCount.
         * Should print: "Resource loaded: <name> (<type>, <sizeBytes> bytes)"
         */
        Resource(const std::string& name, const std::string& type, int sizeBytes);

        // Delete copy (resources are managed via shared_ptr)
        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

        // Delete move (resources don't move, they're shared)
        Resource(Resource&&) = delete;
        Resource& operator=(Resource&&) = delete;

        /**
         * @brief Destructor
         * Should decrement resourceCount.
         * Should print: "Resource unloaded: <name>"
         */
        ~Resource();

        // ============ Getters (inline) ============

        inline std::string getName() const { return name; }
        inline std::string getType() const { return type; }
        inline int getSizeBytes() const { return sizeBytes; }
        inline bool isLoaded() const { return loaded; }

        // ============ Static ============

        /**
         * @brief Get current resource count
         */
        static int getResourceCount();

        // ============ Factory ============

        /**
         * @brief Create a shared resource (factory method)
         * @return shared_ptr to the new resource
         */
        static std::shared_ptr<Resource> create(const std::string& name,
                                                 const std::string& type,
                                                 int sizeBytes);

        // ============ Utility ============

        /**
         * @brief Get a description string
         * Format: "<name> (<type>, <sizeBytes> bytes)"
         */
        std::string toString() const;
    };

} // namespace gameengine

#endif // RESOURCE_HPP