#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Pile {
private:
    std::vector<T> elements;

public:
    void push(const T& element);
    T pop();
    T top() const;
    bool isEmpty() const;
    size_t size() const;
};

template <typename T>
void Pile<T>::push(const T& element) {
    elements.push_back(element);
}

template <typename T>
T Pile<T>::pop() {
    if (elements.empty()) {
        throw std::runtime_error("Erreur: La pile est vide !");
    }
    T topElement = elements.back();
    elements.pop_back();
    return topElement;
}

template <typename T>
T Pile<T>::top() const {
    if (elements.empty()) {
        throw std::runtime_error("Erreur: La pile est vide !");
    }
    return elements.back();
}

template <typename T>
bool Pile<T>::isEmpty() const {
    return elements.empty();
}

template <typename T>
size_t Pile<T>::size() const {
    return elements.size();
}