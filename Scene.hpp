/**
 * @file Scene.hpp
 * @brief Scene class using unique_ptr, shared_ptr, and weak_ptr
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Entity.hpp"
#include "Resource.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace gameengine {

    class Scene {
    private:
        std::string sceneName;

        // Entities are OWNED by the scene (unique_ptr — exclusive ownership)
        std::vector<std::unique_ptr<Entity>> entities;

        // Resources are SHARED between scenes (shared_ptr — shared ownership)
        std::vector<std::shared_ptr<Resource>> resources;

        // Observers watch a resource without owning it (weak_ptr)
        // Maps observer name → weak_ptr to a resource
        std::map<std::string, std::weak_ptr<Resource>> observers;

    public:
        // ============ Constructor ============

        /**
         * @brief Constructor
         * @param name The scene name
         */
        explicit Scene(const std::string& name);

        // Scenes are movable but not copyable
        Scene(Scene&& other) noexcept = default;
        Scene& operator=(Scene&& other) noexcept = default;
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

        ~Scene() = default;

        // ============ Entity Management (unique_ptr) ============

        /**
         * @brief Create an entity in the scene
         * @param name Entity name
         * @param x X position
         * @param y Y position
         * @param health Starting health
         * @return Raw pointer to the entity (non-owning)
         */
        Entity* createEntity(const std::string& name, double x = 0.0,
                             double y = 0.0, int health = 100);

        /**
         * @brief Add an existing entity by moving it into the scene
         * @param entity The unique_ptr to move in
         */
        void addEntity(std::unique_ptr<Entity> entity);

        /**
         * @brief Remove an entity by index and return it (transfer ownership out)
         * @param index The index (0-based)
         * @return The unique_ptr to the removed entity
         * @throws std::out_of_range if index is out of bounds (negative or >= count)
         */
        std::unique_ptr<Entity> removeEntity(int index);

        /**
         * @brief Get a non-owning pointer to an entity by index
         * @param index The index
         * @return Raw pointer to the entity
         * @throws std::out_of_range if index is out of bounds (negative or >= count)
         */
        Entity* getEntity(int index) const;

        /**
         * @brief Find an entity by name
         * @param name The entity name
         * @return Raw pointer, or nullptr if not found
         */
        Entity* findEntity(const std::string& name) const;

        /**
         * @brief Get number of entities
         */
        int getEntityCount() const;

        // ============ Resource Management (shared_ptr) ============

        /**
         * @brief Add a shared resource to the scene
         * @param resource The shared_ptr to add
         */
        void addResource(std::shared_ptr<Resource> resource);

        /**
         * @brief Get a shared_ptr to a resource by index
         * @param index The index
         * @return shared_ptr to the resource
         * @throws std::out_of_range if index is out of bounds (negative or >= count)
         */
        std::shared_ptr<Resource> getResource(int index) const;

        /**
         * @brief Find a resource by name
         * @param name The resource name
         * @return shared_ptr (empty if not found)
         */
        std::shared_ptr<Resource> findResource(const std::string& name) const;

        /**
         * @brief Get the number of resources
         */
        int getResourceCount() const;

        /**
         * @brief Get the reference count of a resource at index
         * @param index The index
         * @return The reference count
         * @throws std::out_of_range if index is out of bounds
         */
        long getResourceRefCount(int index) const;

        // ============ Observer Management (weak_ptr) ============

        /**
         * @brief Register a weak observer for a resource
         * @param observerName A name for this observer
         * @param resource The resource to observe
         */
        void addObserver(const std::string& observerName,
                         std::shared_ptr<Resource> resource);

        /**
         * @brief Check if an observed resource is still alive
         * @param observerName The observer name
         * @return true if the resource is still alive
         * @throws std::invalid_argument if observer doesn't exist
         */
        bool isObservedResourceAlive(const std::string& observerName) const;

        /**
         * @brief Get a shared_ptr from a weak observer (lock)
         * @param observerName The observer name
         * @return shared_ptr (may be empty if resource expired)
         * @throws std::invalid_argument if observer doesn't exist
         */
        std::shared_ptr<Resource> lockObservedResource(
            const std::string& observerName) const;

        /**
         * @brief Get number of observers
         */
        int getObserverCount() const;

        // ============ Utility ============

        /**
         * @brief Get the scene name
         */
        std::string getName() const;

        /**
         * @brief Print scene summary to a stream
         * @param os The output stream
         */
        void printSummary(std::ostream& os) const;
    };

} // namespace gameengine

#endif // SCENE_HPP