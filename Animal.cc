#include "Animal.h"
#include "GeneticData.h"
#include "Cell.h"

Animal::Animal(Cell* cell_){
        position = cell_;
        genetic_data = GeneticData();
        energy = 100.;
        cell_->addAnimal(this);
}

Animal::Animal(Cell* cell_, GeneticData gd, double health){
        position = cell_;
        genetic_data = gd;
        energy = health;
        cell->addAnimal(this);
}

bool Animal::isAlive() const {
        return (energy<=0.0);
}

double Animal::get_force() const {
        return genetic_data.GeneticData::get_force();
}


double Animal::get_rep_threshold() const {
        return genetic_data.GeneticData::get_rep_threshold();
}

unsigned int Animal::get_nb_moves() const {
        return genetic_data.GeneticData::get_nb_moves();
}

unsigned int Animal::get_nb_offspring() const {
        return genetic_data.GeneticData::get_nb_offspring();
}

std::vector<Animal*> Animal::reproduce(){
        std::vector<Animal*> newborns;
        if(energy>Animal::get_rep_threshold()) {
                double offspringEnergy
                        = (energy-Animal::get_rep_threshold())/Animall::get_nb_offspring();
                for(size_t i(0); i<Animal::get_nb_offspring(); ++i) {
                        Animal* ptr = new Animal(position, genetic_data, offspringEnergy);
                        newborns.pushback(ptr);
                        position->addAnimal(ptr);
                }
                energy = Animal::get_rep_threshold();
        }
        return newborns;
}

void Animal::changeCell(Cell* cell){
        position = cell;
}

std::vector<const unsigned int> move(){
        unsigned int X = position->getX();
        unsigned int Y = position->getY();

        for(size_t i(0); i<get_nb_moves(); ++i) {
                unsigned int depl_x = (std::rand()%3)-1;
                unsigned int depl_y = (std::rand()%3)-1;
                X+=depl_x;
                Y+=depl_y;
                energy+=1.;
        }
        std::vector<const unsigned int> position;
        position.pushback(X);
        position.pushback(Y);

        return position;
}

void Animal::eat() {
        //decreasefood retourne la quantité de food que l'animal mange
        if(position->decreaseFood()=!0) energy+=20.;
}
