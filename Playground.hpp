/**
 * @file Playground.hpp
 * @brief Playground functions combining smart pointer and move concepts
 */

#ifndef PLAYGROUND_HPP
#define PLAYGROUND_HPP

#include "Entity.hpp"
#include "Resource.hpp"
#include "Scene.hpp"
#include "SmartStack.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace gameengine {

    /**
     * @brief Factory: Create a unique_ptr to a new Entity
     * @return unique_ptr<Entity>
     */
    std::unique_ptr<Entity> createEntity(const std::string& name, double x, double y, int health);

    /**
     * @brief Factory: Create a shared_ptr to a new Resource
     * @return shared_ptr<Resource>
     */
    std::shared_ptr<Resource> createResource(const std::string& name,
                                              const std::string& type,
                                              int sizeBytes);

    /**
     * @brief Transfer an entity from one scene to another
     * @param sourceScene The scene to remove from
     * @param entityIndex Index of the entity in sourceScene
     * @param destScene The scene to add to
     * @throws std::out_of_range if entityIndex is invalid
     */
    void transferEntity(Scene& sourceScene, int entityIndex, Scene& destScene);

    /**
     * @brief Demonstrate weak_ptr expiration
     * @param os The output stream
     * Output must contain:
     *   "false" (when weak_ptr is not expired),
     *   "true" (when expired),
     *   "null" (when lock returns nullptr)
     */
    void demonstrateWeakPtr(std::ostream& os);

    /**
     * @brief Demonstrate move semantics with entities
     * @param os The output stream for status messages
     * Output must contain "Hero" and "Villain" entity names.
     */
    void demonstrateMoveSemantics(std::ostream& os);

    /**
     * @brief Demonstrate shared_ptr reference counting
     * @param os The output stream
     * Output must contain lines with exact format:
     *   "Ref count: 1", "Ref count: 2", "Ref count: 3"
     */
    void demonstrateSharedOwnership(std::ostream& os);

    /**
     * @brief Build a scene with entities and resources, demonstrating all concepts
     * @param os The output stream
     * Output must contain "Level 1" (the scene name).
     */
    void buildGameScene(std::ostream& os);

} // namespace gameengine

#endif // PLAYGROUND_HPP