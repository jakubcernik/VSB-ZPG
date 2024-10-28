// Observable.h
#pragma once
#include "Observer.h"
#include <vector>

class Observable {

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        for (Observer* observer : observers) {
            observer->onNotify(viewMatrix, projectionMatrix);
        }
    }

private:
    std::vector<Observer*> observers;
};
