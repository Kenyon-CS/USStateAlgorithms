#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric>
#include <map>
#include <random>

class State {
public:
    std::string name;
    std::string capital;
    double gdp;
    std::string motto;
    long population;
    std::string flower;
    double size; // in square miles

    State(const std::string& name, const std::string& capital, double gdp, const std::string& motto, 
          long population, const std::string& flower, double size)
        : name(name), capital(capital), gdp(gdp), motto(motto), population(population), 
          flower(flower), size(size) {}
};

// Function to load data from a CSV file
std::vector<State> loadStateData(const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<State> states;
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, capital, motto, flower;
        double gdp, size;
        long population;

        getline(ss, name, ',');
        getline(ss, capital, ',');
        ss >> gdp;
        ss.ignore(); // Skip comma
        getline(ss, motto, ',');
        ss >> population;
        ss.ignore(); // Skip comma
        getline(ss, flower, ',');
        ss >> size;

        states.emplace_back(name, capital, gdp, motto, population, flower, size);
    }
    return states;
}

void demonstrateSorting(std::vector<State>& states) {
    // Sort by state name
    std::sort(states.begin(), states.end(), [](const State& a, const State& b) {
        return a.name < b.name;
    });
    std::cout << "States sorted by name:\n";
    for (const auto& state : states)
        std::cout << state.name << "\n";

    // Sort by population
    std::sort(states.begin(), states.end(), [](const State& a, const State& b) {
        return a.population < b.population;
    });
    std::cout << "\nStates sorted by population:\n";
    for (const auto& state : states)
        std::cout << state.name << ": " << state.population << "\n";

    // Sort by per capita GDP (GDP / Population)
    std::sort(states.begin(), states.end(), [](const State& a, const State& b) {
        return (a.gdp / a.population) > (b.gdp / b.population); // Descending order
    });
    std::cout << "\nStates sorted by per capita GDP:\n";
    for (const auto& state : states)
        std::cout << state.name << ": " << (state.gdp / state.population) << "\n";
}

void demonstratePartition(std::vector<State>& states) {
    // Partition based on population < 2,000,000
    auto it = std::partition(states.begin(), states.end(), [](const State& state) {
        return state.population < 2000000;
    });

    std::vector<State> lessThan2M(states.begin(), it);
    std::vector<State> greaterThan2M(it, states.end());

    std::cout << "\nStates with population less than 2,000,000:\n";
    for (const auto& state : lessThan2M)
        std::cout << state.name << "\n";

    std::cout << "\nStates with population greater than or equal to 2,000,000:\n";
    for (const auto& state : greaterThan2M)
        std::cout << state.name << "\n";
}

void demonstrateSearch(const std::vector<State>& states) {
    std::string keyword;
    std::cout << "\nEnter keyword to search in mottos (type 'exit' to stop): ";
    
    while (true) {
        std::cin >> keyword;
        if (keyword == "exit") break;

        auto it = std::find_if(states.begin(), states.end(), [&](const State& state) {
            return state.motto.find(keyword) != std::string::npos;
        });

        if (it != states.end()) {
            std::cout << "Found in state: " << it->name << "\n";
        } else {
            std::cout << "No state motto contains the word '" << keyword << "'\n";
        }
    }
}

void demonstrateTransform(std::vector<State>& states) {
    std::vector<State> transformedStates = states;

    std::transform(transformedStates.begin(), transformedStates.end(), transformedStates.begin(), [](State state) {
        state.population = static_cast<long>(state.population * 1.2); // Increase population by 20%
        return state;
    });

    std::cout << "\nStates with population increased by 20%:\n";
    for (const auto& state : transformedStates)
        std::cout << state.name << ": " << state.population << "\n";
}

void demonstrateRandomPartition(std::vector<State>& states) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(states.begin(), states.end(), g);

    // 30% random partition
    std::vector<State> partition1(states.begin(), states.begin() + states.size() * 0.3);
    // 40% random partition
    std::vector<State> partition2(states.begin() + states.size() * 0.3, states.begin() + states.size() * 0.7);

    // Display the partitions
    std::cout << "\n30% Random partition:\n";
    for (const auto& state : partition1)
        std::cout << state.name << "\n";

    std::cout << "\n40% Random partition:\n";
    for (const auto& state : partition2)
        std::cout << state.name << "\n";
}

void demonstrateNumericOperations(const std::vector<State>& states) {
    auto totalArea = std::accumulate(states.begin(), states.end(), 0.0, [](double sum, const State& state) {
        return sum + state.size;
    });

    auto totalGDP = std::accumulate(states.begin(), states.end(), 0.0, [](double sum, const State& state) {
        return sum + state.gdp;
    });

    auto totalPopulation = std::accumulate(states.begin(), states.end(), 0L, [](long sum, const State& state) {
        return sum + state.population;
    });

    std::cout << "\nTotal Area: " << totalArea << "\n";
    std::cout << "Total GDP: " << totalGDP << "\n";
    std::cout << "Total Population: " << totalPopulation << "\n";
}

int main() {
    std::vector<State> states = loadStateData("states.csv");

    demonstrateSorting(states);
    demonstratePartition(states);
    demonstrateSearch(states);
    demonstrateTransform(states);
    demonstrateRandomPartition(states);
    demonstrateNumericOperations(states);

    return 0;
}
