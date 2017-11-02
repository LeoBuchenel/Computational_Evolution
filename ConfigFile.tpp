#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "ConfigFile.h"

ConfigFile::ConfigFile(const std::string& fileName){
  ifstream file;
  file.open(fileName.c_str());
  if (!file){
    throw "[ConfigFile] Impossible d'ouvrir le fichier " + fileName;
  }
  try{
    std::string lineread;
    while(getline(file, lineread)){
      process(lineread);
    }
    file.close();
  }catch(std::string e){
    file.close();
    throw e;
  }
}

ConfigFile::~ConfigFile(){}

void ConfigFile::printOut(std::string path) const {
  ofstream outputFile(path.c_str());
  if (outputFile.is_open())
  {
    outputFile << toString() << endl;
  }
  outputFile.close();
}

std::string ConfigFile::toString() const {
  std::string strToReturn;

  for (std::map<std::string,std::string>::const_iterator iter = configMap.begin(); iter != configMap.end(); ++iter) {
      strToReturn.append(iter->first);
      strToReturn.append("=");
      strToReturn.append(iter->second);
      strToReturn.append("\n");
  }
  return strToReturn;
}

void ConfigFile::process(const std::string& lineread) {
  size_t commentPosition=trim(lineread).find('%',0);
  if(commentPosition!=0 && trim(lineread).length()>0){
    size_t equalPosition = lineread.find('=',1);
    if(equalPosition==std::string::npos){
      cerr << "Ligne sans '=' : " << lineread << endl;
    }else{
      std::string key = trim(lineread.substr(0,equalPosition));
      std::string value = trim(lineread.substr(equalPosition+1,lineread.length()));
      std::map<std::string, std::string>::const_iterator val = configMap.find(key);
      if (val != configMap.end()) {
        configMap.erase(key);
      }
      configMap.insert( std::pair<std::string, std::string>(key,value) );
    }
  }
}

template<typename T> T ConfigFile::get(const std::string& key) const{
   std::map<std::string, std::string>::const_iterator val = configMap.find(key);
   if ( val != configMap.end() ) {
     T out;
     istringstream iss(val->second);
     iss >> out;
     cout << "\t" << key << "=" << out << endl;
     return out;
   }else{
     std::string msg = "[ConfigFile] Le parametre suivant est manquant : ";
     throw msg+ key;
   }
 }

 template<> bool ConfigFile::get<bool>(const std::string& key) const{
  istringstream iss(configMap.find(key)->second);
  bool result(false);
  iss >> result;
  if (iss.fail()){
    iss.clear();
    iss >> boolalpha >> result;
  }
    return result;
}

std::string ConfigFile::trim(std::string str)
{ // Remove tabs and spaces at the beginning and end of a string
    size_t first = str.find_first_not_of(" \t");
    if(first==std::string::npos)
      return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last-first+1));
}
