#pragma once

#include <memory>
#include <nfd.h>

namespace primitive
{
    class Engine;

    class EditorApplication
    {
    public:
        EditorApplication();
        ~EditorApplication();

        EditorApplication(const EditorApplication&) = delete;
        EditorApplication& operator=(const EditorApplication&) = delete;

        void Run();
    
    private:
        std::unique_ptr<Engine> m_engine;
    };
}