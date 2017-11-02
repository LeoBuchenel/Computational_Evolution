#include "Animal.h"
#include <random>


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
        position->addAnimal(this);
}

bool Animal::isAlive() const {
        return (energy>0.0);
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

double Animal::get_energy() const {
        return energy;
}

std::vector<Animal*> Animal::reproduce(){
        std::vector<Animal*> newborns;
        if(energy>Animal::get_rep_threshold()) {
                double offspringEnergy

                        = (energy-Animal::get_rep_threshold());
                        ///Animal::get_nb_offspring();                       
                for(std::size_t i(0); i<Animal::get_nb_offspring(); ++i) {
                        //Animal* ptr = new Animal(position, genetic_data, offspringEnergy);
                        newborns.push_back(new Animal(position, genetic_data, offspringEnergy));
                }
                energy = 0.5*Animal::get_rep_threshold();
        }
        return newborns;
}

void Animal::changeCell(Cell* cell){
        position = cell;
}

std::vector<unsigned int> Animal::move(){


        int X = position->getX();
        int Y = position->getY();

        for(std::size_t i(0); i<get_nb_moves(); ++i) {
                int depl_x = (rand()%3)-1;
                int depl_y = (rand()%3)-1;
                if(!(X==0 and depl_x < 0))
                        X+=depl_x;
                if(!(Y==0 and depl_y<0))
                        Y+=depl_y;
                energy-=2.;
        }

        std::vector<unsigned int> new_pos;
        new_pos.push_back(X);
        new_pos.push_back(Y);

        return new_pos;
}

void Animal::eat() {
        //decreasefood retourne la quantité de food que l'animal mange
        if(position->decreaseFood()!=0) energy+=20.;
}

unsigned int Animal::getX() const
{
        return position->getX();
}

unsigned int Animal::getY() const
{
        return position->getY();
}

Cell* Animal::get_Position() const{
	return position;
}
