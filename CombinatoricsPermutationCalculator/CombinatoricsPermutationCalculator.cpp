#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

static int holder = 6;
static std::vector<int> container;
static int maxForContainer = holder;
static std::vector<int> remainderHolder;
static std::vector<std::unordered_set<int>> spotChecker(maxForContainer);
static int LAST_IMPORTANT_SPOT{ holder - 2 };
#define MAXIMUM_NUMBER_FOR_SPOT (maxForContainer - stage)
#define LAST_ELEMENT remainderHolder.size() - 1
static int counter = 1;
static std::vector<int> vec;

//this is just the permutator program and the power set program copied and pasted, however,
//I modified some of the code consisting of these two implementations such that they can work together
//and produce what I need, which is to do a permutation for a specified sized container.
//the value static int holder sets how many values are in a given set, and then the fuction powerset with the value
//constexpr int upToWhat chooses up to what numbers to use, and what sets are we to perform the permutations on.
//if you're wondering on the two implementations this combinatorics permutation calculator is dependent on,
//please refer to the individual program instantions I made.

void printContainer() {
    for (int i = 0; i < container.size(); i++) {
        if (i == container.size() - 1) {
            std::cout << container[i] << '\t' << counter << '\n';
        }
        else {
            std::cout << container[i] << ", ";
        }
    }
    counter++;
}

void checkAvailability(int stage) {
    for (int i = 0; i < remainderHolder.size(); i++) {
        if (spotChecker[stage].find(remainderHolder[i]) == spotChecker[stage].end()) {
            std::swap(remainderHolder[i], remainderHolder[LAST_ELEMENT]);
            container[stage] = remainderHolder[LAST_ELEMENT];
            remainderHolder.pop_back();
            return;
        }
    }
}

void permuter(int stage) {
    if (stage == LAST_IMPORTANT_SPOT) {
        printContainer();
        std::swap(container[stage], container[stage + 1]);
        printContainer();
        for (int j = 1; j >= 0; j--) {
            remainderHolder.push_back(container[j + stage]);
            container.pop_back();
        }
        return;
    }
    while (spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT) {
        permuter(stage + 1);
        spotChecker[stage].insert(container[stage]);
        remainderHolder.push_back(container[stage]);
        checkAvailability(stage);
        for (int j = 0; j < remainderHolder.size() && spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT; j++) {
            container.push_back(remainderHolder[j]);
        }
        if (spotChecker[stage].size() != MAXIMUM_NUMBER_FOR_SPOT) {
            remainderHolder.clear();
        }
    }
    container.pop_back();
    spotChecker[stage].clear();
}


constexpr int upToWhat = 8;

void powerSet(int i, bool consider) {
    if (consider && i != 0) vec.push_back(i);
    if (vec.size() == holder && consider) {
        container = vec;
        permuter(0);
        remainderHolder.clear();
    }
    if (i == upToWhat) {
        return;
    }
    powerSet(i + 1, true);
    vec.pop_back();
    powerSet(i + 1, false);
}

int main()
{
    powerSet(0, false);
}

