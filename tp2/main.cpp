//
// Created by yurei on 12/02/2022.
//

#include "particule.h"

const double delta_t = 0.015;
const double t_end = 468.5;

void calculer_force(const std::set<Particule>& part_init, const Particule& part_to_compute) {
    Vecteur force = Vecteur(0, 0, 0);
    for (const auto& part : part_init) {
        if (!(part == part_to_compute)) {
            Vecteur r = Vecteur(part_to_compute.position->x - part.position->x,
                                part_to_compute.position->y - part.position->y, 0);
            double r3 = pow(pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2), 1.5);
            double k = (part.masse + part_to_compute.masse) / r3;

            force.x = force.x +  k * r.x;
            force.y = force.y +  k * r.y;
            force.z = force.z +  k * r.z;
        }
    }
    *part_to_compute.force = force;
}

void stromer_verlet(const std::set<Particule>& part_init) {
    // initialisation du calcul des forces F
    for (const auto& part : part_init) {
        calculer_force(part_init, part);
    }
    // fin initialisation
    double t = 0;
    while (t < t_end) {
        t += delta_t;
        // MàJ de de la postion des particules et des forces
        std::vector<Vecteur*> old_forces;
        for (auto part_a_modif = part_init.begin(); part_a_modif != part_init.end(); ++part_a_modif++) {
            Particule part = part_a_modif.operator*();
            part.position->x = part.position->x + delta_t * (part.vitesse->x + 0.5 / part.masse * part.force->x * delta_t);
            part.position->y = part.position->y + delta_t * (part.vitesse->y + 0.5 / part.masse * part.force->y * delta_t);

            auto old_f = new Vecteur{part.force->x, part.force->y, 0};
            old_forces.insert(old_forces.begin(), old_f);
        }
        // calcul des forces F
        for (const auto& part : part_init) {
            calculer_force(part_init, part);
        }
        // fin calcul
        auto force_a_modif = old_forces.begin();
        for (auto part_a_modif = part_init.begin(); part_a_modif != part_init.end(); ++part_a_modif++) {
            Vecteur* old_f = force_a_modif.operator*();
            Particule part = part_a_modif.operator*();
            part.vitesse->x = part.vitesse->x + delta_t * 0.5 / part.masse * (part.force->z + old_f->x);
            part.vitesse->y = part.vitesse->y + delta_t * 0.5 / part.masse * (part.force->z + old_f->y);
            ++force_a_modif++;
        }

        for (auto force : old_forces) {
            delete force;
        }
        //todo
        // calcul des quantités dérivées

        // afficher t, x, y
        std::cout << "\n==========================";
        for (auto part_a_modif = part_init.begin(); part_a_modif != part_init.end(); ++part_a_modif++) {
            Particule part = part_a_modif.operator*();
            std::cout << "\n" << part.id << " :\n\t\t t -> " << t << "\n\t\t x -> " << part.position->x << "\n\t\t y ->  "<< part.position->y;
        }
    }
}

int main() {
    std::set<Particule> particule_set;


    auto p = new Particule("Soleil", 1,
                                 new Point(0, 0, 0), new Vecteur(0, 0, 0),
                                 new Vecteur(0, 0, 0), "étoile");
    particule_set.insert(particule_set.end(), *p);

    p = new Particule( "Terre", 3.0e-06, new Point(0, 1, 0),
                  new Vecteur(0, 0, 0), new Vecteur(-1, 0, 0),"planète");
    particule_set.insert(particule_set.end(), *p);

    p = new Particule("Jupiter", 9.55e-04, new Point(0, 5.36, 0),
                  new Vecteur(0, 0, 0), new Vecteur(-0.425, 0, 0), "planète");
    particule_set.insert(particule_set.end(), *p);

    p = new Particule("Haley", 1e-14, new Point(34.75, 0, 0),
                  new Vecteur(0, 0, 0), new Vecteur(0, 0.0296, 0), "planète");
    particule_set.insert(particule_set.end(), *p);

    for (const auto& it : particule_set) {
        it.display();
    }

    stromer_verlet(particule_set);
    for (const auto& it : particule_set) {
        delete it.position;
        delete it.force;
        delete it.vitesse;
    }
}