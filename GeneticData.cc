#include "GeneticData.h"
#include <iostream>

GeneticData::GeneticData(){

        unsigned int x = (std::rand() % 4) + 1;
        nb_moves = x;
        force = 100./x;

		//nb_moves = 1;
		//force = 100;
		
        unsigned int y = (std::rand() % 5) + 1;
        nb_offspring = y;
        repr_threshold = 100./y;

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
