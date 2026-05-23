#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Player {
public:
    Player(const std::string& name, int number);

    const std::string& getName()   const;
    int                getNumber() const;

    void setName(const std::string& name);
    void setNumber(int number);

    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);

private:
    std::string name;
    int         number;
};


class Team {
public:
    explicit Team(const std::string& name);

    const std::string& getName()        const;
    int                playerCount()    const;

    void addPlayer(const Player& player);
    void removePlayer(const std::string& name);

    const Player* findPlayer(const std::string& name) const;

    void printAll() const;

    friend std::ostream& operator<<(std::ostream& os, const Team& t);

private:
    std::string         name;
    std::vector<Player> players;
};