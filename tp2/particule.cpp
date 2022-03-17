//
// Created by yurei on 10/02/2022.
//

#include "particule.h"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int j = 6; j < 10; j++) {
        std::cout << "\nTest for " << pow(2, j) << " particles :\n";
        // using list
        auto start_list = std::chrono::steady_clock::now();
        std::list<Particule> particule_list;
        for (int i=0; i<j; ++i) {
            Particule p = Particule(i, mt, dist);
            particule_list.insert(particule_list.end(), p);
        }
        auto end_list = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_list = end_list - start_list;
        std::cout << "\tList\t--------> elapsed time: "<< elapsed_seconds_list.count()<< "s\n";
        // using set
        auto start_set = std::chrono::steady_clock::now();
        std::set<Particule> particule_set;
        for (int i=0; i<j; ++i) {
            Particule p = Particule(i, mt, dist);
            particule_set.insert(particule_set.begin(), p);
        }
        auto end_set = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_set = end_set - start_set;
        std::cout << "\tSet\t\t--------> elapsed time: "<< elapsed_seconds_set.count()<< "s\n";
        // using deque
        auto start_deque = std::chrono::steady_clock::now();
        std::deque<Particule> particule_deque;
        for (int i=0; i<j; ++i) {
            Particule p = Particule(i, mt, dist);
            particule_deque.insert(particule_deque.end(), p);
        }
        auto end_deque = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_deque = end_deque - start_deque;
        std::cout << "\tDeque\t--------> elapsed time: " << elapsed_seconds_deque.count() << "s\n";
        // using vector
        auto start_vector = std::chrono::steady_clock::now();
        std::vector<Particule> particule_vector;
        for (int i=0; i<j; ++i) {
            Particule p = Particule(i, mt, dist);
            particule_vector.insert(particule_vector.end(), p);
        }
        auto end_vector = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds_vector = end_vector - start_vector;
        std::cout << "\tVector\t--------> elapsed time: "<< elapsed_seconds_vector.count()<< "s\n";
    }

    std::list<Particule> particule_list;
    for (int i=0; i<16; ++i) {
        Particule p = Particule(i, mt, dist);
        particule_list.insert(particule_list.end(), p);
    }
    for (const auto& it : particule_list) {
        it.display();
    }
}
