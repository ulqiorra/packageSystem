#include <algorithm>
#include "PackageController.h"

using namespace std;

// custom constructor of PackageController object
PackageController::PackageController()
{
    launchStatus = true;
    showHelp();
}

// function to RECEIVE user input from console
void PackageController::getInput(istream &in)
{
    bool isCommand = false;
    string tmp;
    getline(in, tmp);
    if(!tmp.empty())
    {
        string cmd;
        cmd = tmp.substr(0, tmp.find_first_of(' '));

        for(const auto &i : options)
        {
            if(i.first == cmd)
            {
                isCommand = true;
                this->command = tmp;
                break;
            }
        }
    }

    if(!isCommand)
        cout<<"Unknown command! Try again, please! \n";
}

// function to DEFINE and EXECUTE command from user input
void PackageController::executeCommand()
{
    if(!command.empty())
    {
        string cmd;
        cmd = command.substr(0, command.find_first_of(' '));

        switch(options[cmd])
        {
            default: break;
            case 0: exitSystem();
                    break;
            case 1: createPackage();
                    break;
            case 2: addPackage();
                    break;
            case 3: removePackage();
                    break;
            case 4: printPackage();
                    break;
            case 5: showHelp();
                    break;
        }

        command.clear();
    }
}

// function to EXIT program
void PackageController::exitSystem()
{
    launchStatus = false;
    exit(0);
}

// function to CREATE new Package
void PackageController::createPackage()
{
    bool isUniq = true;
    string name = command.find_first_of(' ')== string::npos ? "" : command.substr(command.find_first_of(' ')+1);
    if(name.find_first_of("\\ /") == string::npos && !name.empty())
    {
        for(const auto &i : packs)
        {
            if(i->getName() == name)
            {
                isUniq = false;
                break;
            }
        }
        if(isUniq)
        {
            Package p(name);
            packs.push_back(make_shared<Package>(p));
        }
        else
            cout<<"This name already exists, try again, please! \n";
    }
    else
        cout<<"Bad name, try again, please! \n";
}

// function to PRINT name of selected Package and names of all its childs
void PackageController::printPackage()
{
    bool found = false;
    string path = command.substr(command.find_first_of(' ')+1);
    string parent = path.substr(0, path.find_first_of('/'));
    string child = path.substr(path.find_last_of('/')+1);

    for(const auto &i : packs)
    {
        if(i->getName() == parent)
        {
            if(path.find_first_of('/') == string::npos)
            {
                found = true;
                cout<<i->getName()<<endl;
                vector<string> childNames;
                i->getChildsNames(childNames);
                for(const auto &j : childNames)
                    cout<<j<<endl;
            }
            else
            {
                auto c = i->getChildByName(child);
                if(c != nullptr)
                {
                    found = true;
                    cout<<c->getName()<<endl;
                    vector<string> childNames;
                    c->getChildsNames(childNames);
                    for(const auto &j : childNames)
                        cout<<j<<endl;
                }
            }
            break;
        }
    }

    if(!found)
        cout<<"Selected package not found! \n";
}

// function to ADD new Package to existing one
void PackageController::addPackage()
{
    bool found = false;
    string input = command.substr(command.find_first_of(' ')+1);
    string pathToParent = input.substr(0, input.find_first_of(' '));
    string childName = input.substr(input.find_first_of(' ')+1);

    if(childName.find_first_of("\\ /") != string::npos || childName.empty() || childName == pathToParent)
    {
        cout<<"Bad new child name, try again, please! \n";
        return;
    }

    string root = pathToParent.substr(0, pathToParent.find_first_of('/'));
    string parent = pathToParent.substr(pathToParent.find_last_of('/')+1);

    for(const auto &i : packs)
    {
        if(i->getName() == root)
        {
            if(pathToParent.find_first_of('/') == string::npos)
            {
                found = true;
                i->add(childName);
            }
            else
            {
                auto c = i->getChildByName(parent);
                if(c != nullptr)
                {
                    found = true;
                    c->add(childName);
                }
            }
            break;
        }
    }

    if(!found)
        cout<<"Selected package not found! \n";
}

// function to REMOVE existing Package by its path, received from user input
void PackageController::removePackage()
{
    bool found = false;
    string path = command.substr(command.find_first_of(' ')+1);
    string root = path.substr(0, path.find_first_of('/'));

    for(auto i = packs.begin(); i != packs.end(); i++)
    {
       if((*i)->getName() == root)
       {
           found = true;
           if(root == path)
           {
               packs.erase(i);
           }
           else
           {
               string pathToVector = path.substr(path.find_first_of('/')+1);
               (*i)->remove(pathToVector);
           }
           break;
       }
    }

    if(!found)
        cout<<"Selected package not found! \n";
}

// function to SHOW help with all available console commands and their examples
void PackageController::showHelp()
{
    cout<<"Welcome to the Package controlling system! \nList of available commands: \n";

    for(const auto &i : options)
    {
        cout<<i.first<<endl;
    }

    cout<<endl<<"Examples: \n"
        <<"create root_pack\n"
        <<"add root_pack pack_1\n"
        <<"add root_pack/pack_1 pack_1_1\n"
        <<"remove root_pack/pack_1/pack_1_1\n"
        <<"print root_pack\n"
        <<"help\n"
        <<"exit\n\n";
}

// function to CHECK status of current PackageController object
bool PackageController::getStatus() const
{
    return this->launchStatus;
}