#include <vector>

class Event
{
public:
    // Add a listener to the button click event
    virtual void AddListener(void* listener) = 0;
    // Remove a listener from the button click event
    virtual void RemoveListener(void* listener) = 0;
    // Event
    virtual void OnEvent(std::initializer_list<void*> param) = 0;
};

class CheckEvent : public Event
{
public:
    using Delegate = void(*)(bool);
    std::vector<Delegate> Listners;
    void AddListener(void* listener) {
        puts("214124");
        Listners.push_back(reinterpret_cast<Delegate>(listener));
    }
    void RemoveListener(void* listner) {
        auto it = std::find(Listners.begin(), Listners.end(), listner);
        if (it != Listners.end()) { Listners.erase(it); }
    }
    void OnEvent(std::initializer_list<void*> param) {
        bool* const* checked = (bool* const*)param.begin();
        for (auto listener : Listners) { listener(*checked); }
    }
};

class ClickEvent : public Event
{
public:
    using Delegate = void(*)();
    std::vector<Delegate> Listners;
    void AddListener(void* listener) {
        Listners.push_back(reinterpret_cast<Delegate>(listener));
    }
    void RemoveListener(void* listner) {
        auto it = std::find(Listners.begin(), Listners.end(), listner);
        if (it != Listners.end()) { Listners.erase(it); }
    }
    void OnEvent(std::initializer_list<void*> param) {
        for (auto listener : Listners) { listener(); }
    }
};

class TextEditEvent : public Event
{
public:
    using Delegate = void(*)(char*);
    std::vector<Delegate> Listners;
    void AddListener(void* listener) {
        Listners.push_back(reinterpret_cast<Delegate>(listener));
    }
    void RemoveListener(void* listner) {
        auto it = std::find(Listners.begin(), Listners.end(), listner);
        if (it != Listners.end()) { Listners.erase(it); }
    }
    void OnEvent(std::initializer_list<void*> param) {
        char* const* text = (char* const*)param.begin();
        for (auto listener : Listners) { listener(*text); }
    }
};

class SelectEvent : public Event
{
public:
    using Delegate = void(*)(int, char*);
    std::vector<Delegate> Listners;
    void AddListener(void* listener) {
        Listners.push_back(reinterpret_cast<Delegate>(listener));
    }
    void RemoveListener(void* listner) {
        auto it = std::find(Listners.begin(), Listners.end(), listner);
        if (it != Listners.end()) { Listners.erase(it); }
    }
    void OnEvent(std::initializer_list<void*> param) {
        auto it = param.begin();
        int* const* index = (int* const*)it++;
        char* const* text = (char* const*)it;
        for (auto listener : Listners) { listener(*(int*)index, *text); }
    }
};
