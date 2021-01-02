#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mutex>
#include <functional>
#include <type_traits>


static std::once_flag GLFW_INITIALIZATION;
static std::once_flag GLFW_TERMINATION;


/// @class GLFWWindow
/// @brief Handle GLFW window creation boilerplate with low-cost C++ abstractions.
class GLFWWindow
{
// Type definitions.
public:
    /// @struct Initializer
    /// @brief  Track GLFW initialization data in one place.
    struct Initializer
    {
        unsigned int width;
        unsigned int height;
        const char *title;
    };

    /// @enum  KeyInput
    /// @brief Namespaced enum class to map to GLFW macros.
    enum class KeyInput
    {
        release = GLFW_RELEASE,
        press = GLFW_PRESS,
        repeat = GLFW_REPEAT
    };

// Data members.
private:
    GLFWwindow *mWindow;

// Construction and destruction.
public:
    GLFWWindow(const Initializer &info)
        : mWindow{createWindow(info)}
    {
    }

    /// This class is intended to be overridden.
    /// Ensure destructor is virtual.
    virtual ~GLFWWindow()
    {
        std::call_once(GLFW_TERMINATION, glfwTerminate);
    }

// Member functions.
public:
    /// @fn    getKeyPress
    /// @brief Pass-through to glfwGetKey with compile-time argument checking.
    template<int GlfwKeyType>
    KeyInput getKeyPress() const
    {
        constexpr auto value = std::integral_constant<int, GlfwKeyType>::value;
        static_assert((value >= -1));
        static_assert((value <= GLFW_KEY_LAST));
        return static_cast<KeyInput>(glfwGetKey(mWindow, value));
    }

    /// @fn    setShouldClose
    /// @brief Sets GLFW flag for window to close.
    void setShouldClose() noexcept
    {
        glfwSetWindowShouldClose(mWindow, true);
    }

    /// @fn    getShouldClose
    /// @brief Sets GLFW flag for window to close.
    bool getShouldClose() const noexcept
    {
        return glfwWindowShouldClose(mWindow);
    }

    /// @fn    get
    /// @brief Return the associated raw GLFW window pointer.
    ///
    /// In situations where the C++ GLFWWindow abstraction does not have functionality provided in the C API,
    /// permit interaction with the C API directly.
    constexpr GLFWwindow *get() const noexcept
    {
        return mWindow;
    };

// Static functions.
public:
    /// @fn createWindow
    ///
    /// GLFW window creation boilerplate tied to OpenGL version 3.3.
    static GLFWwindow *createWindow(const Initializer &info) noexcept
    {
        std::call_once(GLFW_INITIALIZATION, glfwInit);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return glfwCreateWindow(info.width, info.height, info.title, nullptr, nullptr);
    }

};
