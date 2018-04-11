#ifndef PACKAGESYSTEM_PACKAGE_H
#define PACKAGESYSTEM_PACKAGE_H

#include <string>
#include <vector>
#include <memory>

// representation of Package
class Package {
public:
    explicit Package(std::string);
    ~Package() = default;

    void add(const std::string&);
    void remove(const std::string&);
    std::shared_ptr<Package> getChildByName(const std::string&) const;

    std::string getName() const;
    void getChildsNames(std::vector<std::string>&);

private:
    std::string name;
    std::vector<std::shared_ptr<Package>> childs;
};


#endif //PACKAGESYSTEM_PACKAGE_H
