#include "GeneticData.h"
#include <iostream>

GeneticData::GeneticData(){

        double x = (std::rand() % 100) + 1;
        force = x;
        unsigned int a = 100/x;
        nb_moves = a;

        unsigned int y = (std::rand() % 5) + 1;
        nb_offspring = y;
        repr_threshold = y*30.;

}

double GeneticData::get_force() const {
        return force;
}

double GeneticData::get_rep_threshold() const {
        return repr_threshold;
}

unsigned int GeneticData::get_nb_offspring() const {
        return nb_offspring;
}

unsigned int GeneticData::get_nb_moves() const {
        return nb_moves;
}