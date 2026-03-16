/**
 * @file SmartStack.hpp
 * @brief Generic linked-list stack using unique_ptr
 *
 * This is a template class so ALL code is in this header.
 * Students must implement the methods marked with "Must be implemented".
 */

#ifndef SMARTSTACK_HPP
#define SMARTSTACK_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <functional>

namespace gameengine {

    template <typename T>
    class SmartStack {
    private:
        /**
         * @brief Internal node structure
         */
        struct Node {
            T value;
            std::unique_ptr<Node> next;

            /**
             * @brief Construct a node with a copied value
             */
            Node(const T& val, std::unique_ptr<Node> nxt)
            {
                // ====== Must be implemented ======
            }

            /**
             * @brief Construct a node with a moved value
             */
            Node(T&& val, std::unique_ptr<Node> nxt)
            {
                // ====== Must be implemented ======
            }
        };

        std::unique_ptr<Node> topNode;   // Top of the stack
        int count;                        // Number of elements

    public:
        // ============ Constructors ============

        /**
         * @brief Default constructor — empty stack
         */
        SmartStack() {
            // ====== Must be implemented ======
        }

        /**
         * @brief Move constructor
         * Transfers the entire stack from other.
         */
        SmartStack(SmartStack&& other) noexcept {
            // ====== Must be implemented ======
        }

        /**
         * @brief Move assignment operator
         */
        SmartStack& operator=(SmartStack&& other) noexcept {
            // ====== Must be implemented ======
        }

        // Delete copy (unique_ptr can't be copied)
        SmartStack(const SmartStack&) = delete;
        SmartStack& operator=(const SmartStack&) = delete;

        // Destructor is default — unique_ptr chain handles cleanup
        ~SmartStack() = default;

        // ============ Stack Operations ============

        /**
         * @brief Push a value onto the stack (copy)
         * @param value The value to push
         */
        void push(const T& value) {
            // ====== Must be implemented ======
        }

        /**
         * @brief Push a value onto the stack (move)
         * @param value The value to push (moved)
         */
        void push(T&& value) {
            // ====== Must be implemented ======
        }

        /**
         * @brief Pop the top value off the stack
         * @return The value that was on top
         * @throws std::underflow_error if the stack is empty
         */
        T pop() {
            // ====== Must be implemented ======
        }

        /**
         * @brief Access the top value without removing it
         * @return Const reference to the top value
         * @throws std::underflow_error if the stack is empty
         */
        const T& top() const {
            // ====== Must be implemented ======
        }

        /**
         * @brief Access the top value (mutable)
         * @return Reference to the top value
         * @throws std::underflow_error if the stack is empty
         */
        T& top() {
            // ====== Must be implemented ======
        }

        // ============ Getters ============

        /**
         * @brief Get the number of elements
         */
        int size() const {
            return count;
        }

        /**
         * @brief Check if the stack is empty
         */
        bool empty() const {
            return count == 0;
        }

        // ============ Utility ============

        /**
         * @brief Apply a function to each element (top to bottom)
         * @param func The function to apply
         */
        void forEach(std::function<void(const T&)> func) const {
            // ====== Must be implemented ======
        }

        /**
         * @brief Convert stack to string (top to bottom)
         * Format: "[top, ..., bottom]"
         * Empty: "[]"
         */
        std::string toString() const {
            // ====== Must be implemented ======
        }

        /**
         * @brief Clear the stack (remove all elements)
         */
        void clear() {
            // ====== Must be implemented ======
        }
    };

} // namespace gameengine

#endif // SMARTSTACK_HPP