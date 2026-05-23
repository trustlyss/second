#include "team.hpp"

#include <algorithm>
#include <iomanip>

Player::Player(const std::string& name, int number) : name(name), number(number) {
    if (name.empty())       throw std::invalid_argument("Player name cannot be empty");
    if (number < 1 || number > 99) throw std::invalid_argument("Number must be 1-99");
}

const std::string& Player::getName()   const { return name; }
int                Player::getNumber() const { return number; }

void Player::setName(const std::string& n) {
    if (n.empty()) throw std::invalid_argument("Player name cannot be empty");
    name = n;
}
void Player::setNumber(int n) {
    if (n < 1 || n > 99) throw std::invalid_argument("Number must be 1-99");
    number = n;
}

void Player::print() const {
    std::cout << "  #" << std::setw(2) << number
              << "  " << name << "\n";
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "#" << p.number << " " << p.name;
    return os;
}

Team::Team(const std::string& name) : name(name) {
    if (name.empty()) throw std::invalid_argument("Team name cannot be empty");
}

const std::string& Team::getName()     const { return name; }
int                Team::playerCount() const { return (int)players.size(); }

void Team::addPlayer(const Player& player) {
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.getName() == player.getName(); });
    if (it != players.end())
        throw std::logic_error("Player '" + player.getName() + "' already exists");

    auto numIt = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.getNumber() == player.getNumber(); });
    if (numIt != players.end())
        throw std::logic_error("Number " + std::to_string(player.getNumber()) + " is already taken");

    players.push_back(player);
}

void Team::removePlayer(const std::string& name) {
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.getName() == name; });
    if (it == players.end())
        throw std::logic_error("Player '" + name + "' not found");
    players.erase(it);
}

const Player* Team::findPlayer(const std::string& name) const {
    auto it = std::find_if(players.begin(), players.end(),
        [&](const Player& p) { return p.getName() == name; });
    return it != players.end() ? &(*it) : nullptr;
}

void Team::printAll() const {
    std::cout << "Team: " << name
              << " (" << players.size() << " players)\n";
    std::cout << std::string(30, '-') << "\n";
    if (players.empty()) {
        std::cout << "  (no players)\n";
    } else {
        for (const auto& p : players)
            p.print();
    }
    std::cout << std::string(30, '-') << "\n";
}

std::ostream& operator<<(std::ostream& os, const Team& t) {
    os << "Team{" << t.name << ", " << t.players.size() << " players}";
    return os;
}

int main() {
    Team team("FC Dynamo");

    std::cout << "=== Add players ===\n";
    team.addPlayer(Player("Oleksiy Shevchenko",  1));
    team.addPlayer(Player("Dmytro Kovalenko",    5));
    team.addPlayer(Player("Ivan Petrenko",        9));
    team.addPlayer(Player("Mykola Bondarenko",   11));
    team.addPlayer(Player("Andriy Lysenko",      7));
    team.addPlayer(Player("Vasyl Kravchenko",    3));

    team.printAll();

    std::cout << "\n=== Find player ===\n";
    const Player* found = team.findPlayer("Ivan Petrenko");
    if (found)
        std::cout << "Found: " << *found << "\n";

    std::cout << "\n=== Remove player ===\n";
    team.removePlayer("Dmytro Kovalenko");
    std::cout << "Removed: Dmytro Kovalenko\n\n";
    team.printAll();

    std::cout << "\n=== Duplicate name error ===\n";
    try {
        team.addPlayer(Player("Ivan Petrenko", 22));
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Duplicate number error ===\n";
    try {
        team.addPlayer(Player("New Player", 9));
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Remove non-existent player ===\n";
    try {
        team.removePlayer("Ghost Player");
    } catch (const std::logic_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== operator<< ===\n";
    std::cout << team << "\n";

    return 0;
}