#include <iostream>

class Material {
public:
    float Ra, Rd, Rs;

    Material(float ra, float rd, float rs) : Ra(ra), Rd(rd), Rs(rs) {}

    void Print() const {
        std::cout << "Material [Ra=" << Ra << ", Rd=" << Rd << ", Rs=" << Rs << "]" << std::endl;
    }
};
