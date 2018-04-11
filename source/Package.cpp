#include <algorithm>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include "Package.h"

using namespace std;

// custom constructor of Package object
Package::Package(string s) : name(move(s))
{}

// function to ADD new Package with unique name to existing Package
void Package::add(const string &s)
{
    bool isUniq = this->getName() == s ? false : true;

    for(const auto &i : this->childs)
    {
        if(i->getName() == s)
        {
            isUniq = false;
            break;
        }
    }
    if(isUniq)
    {
        Package p(s);
        this->childs.push_back(make_shared<Package>(p));
    }
    else
    {
        cout<<"This name already exists! \n";
    }
}

// function to REMOVE existing Package by its full name without root (path to this Package)
void Package::remove(const string &s)
{
// user input is: remove root_package/package1/package_1_1
// BUT packageController should give to this function ONLY "package1/package_1_1"
// that means that here we only care about vector location (parent) and object to erase
// package controller MUST define the ROOT object for this function
    string packToRemove = s.substr(s.find_last_of('/')+1);
    string path = s.substr(0, s.find_last_of('/'));
    string vecLocation = path.substr(path.find_last_of('/')+1);

    if(packToRemove != vecLocation)
    {
        auto v = this->getChildByName(vecLocation);
        if(v == nullptr)
        {
            cout<<"Element not found!\n";
            return;
        }
        auto r = v->getChildByName(packToRemove);
        if(r == nullptr)
        {
            cout<<"Element not found!\n";
            return;
        }
        auto i = find(v->childs.begin(), v->childs.end(), r);

        if(i != v->childs.end())
            v->childs.erase(i);
        else
            cout<<"Element not found!\n";
    }
    else
    {
        auto r = this->getChildByName(packToRemove);
        if(r == nullptr)
        {
            cout<<"Element not found!\n";
            return;
        }
        auto i = find(this->childs.begin(), this->childs.end(), r);

        if (i != this->childs.end())
            this->childs.erase(i);
        else
            cout<<"Element not found!\n";
    }

}

// function to RECEIVE smart pointer to the child Package by its name
shared_ptr<Package> Package::getChildByName(const string &s) const
{
    // recursive search of selected package
    for(const auto &i : this->childs)
    {
        if(i->name == s)
            return i;
        if(!i->childs.empty())
        {
            auto r = i->getChildByName(s);
            if (r != nullptr)
                return r;
        }
    }
    return nullptr;
}

// function to RECEIVE name of the current Package
string Package::getName() const
{
    return this->name;
}

// function to UPLOAD all child packages names of current Package to std::vector<std::string>
void Package::getChildsNames(vector<string> &v)
{
    // recursively receiving all child packages names
    for(const auto &i : this->childs)
    {
        v.push_back(i->getName());
        i->getChildsNames(v);
    }
}

// function to show cereal which data members to serialize
template <class Archive>
void Package::serialize(Archive & ar)
{
    ar(name, childs);
}

// function to SAVE current Package to the incoming std::stringstream
void Package::savePack(std::stringstream &in)
{
    cereal::BinaryOutputArchive oarchive(in);
    oarchive(name, childs);
}

// function to LOAD data from the incoming std::stringstream to current Package
void Package::loadPack(std::stringstream &out)
{
    cereal::BinaryInputArchive iarchive(out);
    iarchive(name, childs);
}
