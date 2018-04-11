#ifndef PACKAGESYSTEM_PACKAGECONTROLLER_H
#define PACKAGESYSTEM_PACKAGECONTROLLER_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Package.h"

// representation of PackageController
class PackageController {
public:
    explicit PackageController();
    ~PackageController() = default;

    void getInput(std::istream&);
    void executeCommand();

    bool getStatus() const;

private:
    bool launchStatus = false;
    std::string command;
    std::vector<std::shared_ptr<Package>> packs;
    std::map<std::string, int> options = {
            {"exit", 0},        //0 exit console
            {"create", 1},      //1 create package
            {"add", 2},         //2 add package
            {"remove", 3},      //3 remove package
            {"print", 4},       //4 print package's name and all its childs names
            {"help", 5}         //5 show help
    };

    void exitSystem();
    void createPackage();
    void printPackage();
    void addPackage();
    void removePackage();
    void showHelp();
};


#endif //PACKAGESYSTEM_PACKAGECONTROLLER_H
