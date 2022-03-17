//
// Created by yurei on 17/02/2022.
//

#include <iostream>
#include <random>
#include <chrono>

#include <list>
#include <set>
#include <deque>
#include <utility>
#include <vector>

#ifndef LAB3_INFRA_PARTICULES_H
#define LAB3_INFRA_PARTICULES_H

//============================= Vecteur
/// Classe Vecteur
class Vecteur {
    double *pCor;

    Vecteur(double x, double y, double z);
    Vecteur(const Vecteur & v);
    friend Vecteur operator + (Vecteur, Vecteur);
    friend Vecteur operator * (Vecteur, Vecteur);
    friend Vecteur operator*(double, Vecteur);
    ~Vecteur();
};

/// Constructeur (x, y, z)
Vecteur::Vecteur(double x, double y, double z) {
    pCor = new double[3];
    pCor[0] = x;
    pCor[1] = y;
    pCor[2] = z;
}

/// Constructeur par copie
Vecteur::Vecteur(const Vecteur &v) {
    pCor = new double [3];
    for (int i = 0; i < 3; ++i) {
        pCor[i] = v.pCor[i];
    }
}
/// Destructeur
Vecteur::~Vecteur() {
    delete [] pCor;
}

/// Addition entre vecteurs
Vecteur Vecteur::operator +(Vecteur v, Vecteur w) {
    return Vecteur(v.pCor[0] + w.pCor[0], v.pCor[1] + w.pCor[1], v.pCor[2] + w.pCor[2]);
}

/// Multiplication terme à terme
Vecteur Vecteur::operator *(Vecteur v, Vecteur w) {
    return Vecteur(v.pCor[0] * w.pCor[0], v.pCor[1] * w.pCor[1], v.pCor[2] * w.pCor[2]);
}

/// Multiplication par un scalaire
Vecteur Vecteur::operator *(double k, Vecteur v) {
    return Vecteur(v.pCor[0] * k, v.pCor[1] * k, v.pCor[2] * k);
}

/// Print d'un vecteur
ostream &operator<<(ostream &out, const Vecteur &v) {
    for (int i = 0; i<2; ++i) {
        std::cout << v.pCor[i] << ", "
    }
    std::cout<< v.pCor[2] << std::endl;
}

//============================= Particules
/// Classe Particule
class Particule {
    Vecteur* position;
    double masse;
    Vecteur* vitesse;
    std::string id;
    std::string categorie;
    Vecteur* force;

    Particule(unsigned int, std::mt19937, std::uniform_real_distribution<double>);
    Particule(std::string, double, Vecteur*, Vecteur*, Vecteur*, std::string);
    friend bool operator< (const Particule &left, const Particule &right);
    friend bool operator==(const Particule &left, const Particule &right);
};

/// Constructeur random
Particule::Particule(unsigned int ident, std::mt19937 mt, std::uniform_real_distribution<double> distribution) {
    id = std::to_string(ident);
    position = new Vecteur(distribution(mt), distribution(mt), distribution(mt));
    vitesse = new Vecteur(distribution(mt), distribution(mt), distribution(mt));
    force = new Vecteur(distribution(mt), distribution(mt), distribution(mt));
    masse = distribution(mt);
    categorie = "unknown";
}

/// Constructeur (id, masse, position, force, vitesse, categorie)
Particule::Particule(std::string ident, double new_masse, Vecteur *pos, Vecteur *new_force, Vecteur *new_vitesse, std::string cat) {
    id = std::move(ident);
    categorie = std::move(cat);
    masse = new_masse;
    position = pos;
    force = new_force;
    vitesse = new_vitesse;
}

/// Opérateur de comparaison
bool operator< (const Particule &left, const Particule &right)
{
    return left.id < right.id;
}

/// Opérateur d'égalité
bool operator==(const Particule &left, const Particule &right) {
    return left.id == right.id;
}

/// Print d'une particule
ostream &operator<<(ostream &out, const Particule &p) {
    std::cout << "id :\t"<< p.id << "\nmasse :\t" << p.masse << "\ncategorie :\t" << p.categorie << std::endl;
    std::cout << "position : \t" << p.position;
    std::cout << "vitesse : \t" << p.vitesse;
    std::cout << "force : \t" << p.force << std::endl;
}

#endif //LAB3_INFRA_PARTICULES_H
