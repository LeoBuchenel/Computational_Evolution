#include "Animal.h"
#include "ConfigFile.tpp"
#include "Ecosystem.h"
#include "Grid.h"
#include "Cell.h"
#include "GeneticData.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// LES POINTS VONT DE 0 à L

using namespace std;

int main(int argc, char *argv[]) {

        string inputPath("configuration.in"); // Fichier d'input par defaut
        if (argc > 1) // Fichier d'input specifie par l'utilisateur ("./Exercice5
                      // config_perso.in")
                inputPath = argv[1];

        ConfigFile configFile(inputPath); // Les parametres sont lus et stockes dans
                                          // une "map" de strings.

        for (int i(2); i < argc; ++i) // Input complementaires ("./Exercice5
                                      // config_perso.in input_scan=[valeur]")
                configFile.process(argv[i]);

        unsigned int L = configFile.get<unsigned int>("L");
        unsigned int nb_plants = configFile.get<unsigned int>("plants");
        unsigned int nb_animals = configFile.get<unsigned int>("animals");
        unsigned int tfin = configFile.get<unsigned int>("tfin");

        string animalForm = configFile.get<string>("Animal zone");
        unsigned int AnimalParam1 = configFile.get<unsigned int>("Animal zone parameter 1");
        unsigned int AnimalParam2 = configFile.get<unsigned int>("Animal zone parameter 2");
        unsigned int AnimalParam3 = configFile.get<unsigned int>("Animal zone parameter 3");
        unsigned int AnimalParam4 = configFile.get<unsigned int>("Animal zone parameter 4");

        string plantForm = configFile.get<string>("Plant zone");
        unsigned int PlantParam1 = configFile.get<unsigned int>("Plant zone parameter 1");
        unsigned int PlantParam2 = configFile.get<unsigned int>("Plant zone parameter 2");
        unsigned int PlantParam3 = configFile.get<unsigned int>("Plant zone parameter 3");
        unsigned int PlantParam4 = configFile.get<unsigned int>("Plant zone parameter 4");

        // creer l'ecosysteme
        srand(time(NULL));

        Grid grid(L);

        Zone animalZone = grid.getZone(animalForm, AnimalParam1, AnimalParam2, AnimalParam3, AnimalParam4);
        Zone plantZone = grid.getZone(plantForm, PlantParam1, PlantParam2, PlantParam3, PlantParam4);


        Ecosystem ecosystem(&grid, animalZone, plantZone, nb_animals, nb_plants);

        ofstream write_AnimalX, write_AnimalY, write_Plant, write_SystemParam, write_AnimalParam;
        write_AnimalX.open("animal_x.out");
        write_AnimalY.open("animal_y.out");
        write_Plant.open("plant.out");
        write_SystemParam.open("system_param.out");
        write_AnimalParam.open("animal_param.out");


        for(size_t t(0); t<=tfin; ++t) {
                ecosystem.iteration(write_AnimalX,write_AnimalY, write_Plant, write_SystemParam);
        }
		ecosystem.write(write_AnimalX, write_AnimalY, write_Plant, write_SystemParam);
		ecosystem.write_AnimalParam(write_AnimalParam);
		
        write_AnimalX.close();
        write_AnimalY.close();
        write_Plant.close();
        write_SystemParam.close();
        write_AnimalParam.close();





        return 0;
}
