//
// Created by yurei on 10/02/2022.
//
#include <random>
#include <iostream>
#include <chrono>

#include <list>
#include <set>
#include <deque>
#include <utility>
#include <vector>

#ifndef TP2_PARTICULE_H
#define TP2_PARTICULE_H

struct Point {
    double x, y, z;
    Point(double position_x, double position_y, double position_z);
};

Point::Point(double position_x, double position_y, double position_z) {
    x = position_x;
    y = position_y;
    z = position_z;
}

struct Vecteur {
    double x, y, z;
    Vecteur(double vitesse_x, double vitesse_y, double vitesse_z);
    friend Vecteur* operator*(double, Vecteur);
};

Vecteur::Vecteur(double vitesse_x, double vitesse_y, double vitesse_z) {
    x = vitesse_x;
    y = vitesse_y;
    z = vitesse_z;
}

Vecteur * operator* (double k, Vecteur v) {
    return new Vecteur{k * v.x, k * v.y, k * v.z};
}

class Particule {
public :
    struct Point* position;
    double masse;
    struct Vecteur* vitesse;
    std::string id;
    std::string categorie;
    struct Vecteur* force;

    Particule(unsigned int, std::mt19937, std::uniform_real_distribution<double>);
    Particule(std::string, double, Point*, Vecteur*, Vecteur*, std::string);
    void display() const;
    friend bool operator< (const Particule &left, const Particule &right);
    friend bool operator==(const Particule &left, const Particule &right);
};

Particule::Particule(std::string ident, double new_masse, Point *pos, Vecteur *new_force, Vecteur *new_vitesse, std::string cat) {
    id = std::move(ident);
    categorie = std::move(cat);
    masse = new_masse;
    position = pos;
    force = new_force;
    vitesse = new_vitesse;
}
Particule::Particule(unsigned int ident, std::mt19937 mt, std::uniform_real_distribution<double> distribution) {
    id = std::to_string(ident);
    position = new Point(distribution(mt), distribution(mt), distribution(mt));
    vitesse = new Vecteur(distribution(mt), distribution(mt), distribution(mt));
    force = new Vecteur(distribution(mt), distribution(mt), distribution(mt));
    masse = distribution(mt);
    categorie = "unknown";
}
void Particule::display() const {
    std::cout << "id :\t"<< id << "\nmasse :\t" << masse << "\ncategorie :\t" << categorie;
    std::cout << "\nposition :\t"<< position->x << ", " << position->y << ", " << position->z;
    std::cout << "\nvitesse :\t" << vitesse->x << ", " << vitesse->y << ", " << vitesse->z;
    std::cout << "\nforce :\t"<< force->x << ", " << force->y << ", " << force->z << "\n\n";
}

bool operator< (const Particule &left, const Particule &right)
{
    return left.id < right.id;
}

bool operator==(const Particule &left, const Particule &right) {
    return left.id == right.id;
}

#endif //TP2_PARTICULE_H
