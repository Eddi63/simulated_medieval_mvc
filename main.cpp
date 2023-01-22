#include <iostream>
#include "Loc.h"
#include "Controller.h"

std::ostream& operator << (std::ostream& output, const Loc& rhs_loc) {
    output << '(' << rhs_loc.x << ", " << rhs_loc.y << ")";
    return output;
}

int main(int argc, char* argv[]) {
    if(argc!=3){
        std::cerr << "wrong number of files given" ;
        std::exit(1);
    }
    std::string castlesfilename = "castles.dat";
    if(castlesfilename.compare(argv[1]) != 0){
        std::cerr << "first file meant to be castles.dat" ;
        std::exit(1);
    }
    std::string farmsfilename = "farms.dat";
    if(farmsfilename.compare(argv[2]) != 0){
        std::cerr << "second file meant to be farms.dat" ;
        std::exit(1);
    }
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(2);
    Controller controller;
    controller.run(argc,argv);
    return 0;
}
