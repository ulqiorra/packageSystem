#ifndef PACKAGESYSTEM_PACKAGE_H
#define PACKAGESYSTEM_PACKAGE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <cereal/access.hpp>

// representation of Package
class Package {
public:
    Package() = default;
    explicit Package(std::string);
    ~Package() = default;

    void add(const std::string&);
    void remove(const std::string&);
    std::shared_ptr<Package> getChildByName(const std::string&) const;

    std::string getName() const;
    void getChildsNames(std::vector<std::string>&);

    void savePack(std::stringstream&);
    void loadPack(std::stringstream&);

private:
    std::string name;
    std::vector<std::shared_ptr<Package>> childs;

    friend class cereal::access;

    template <class Archive>
    void serialize(Archive&);
};


#endif //PACKAGESYSTEM_PACKAGE_H
