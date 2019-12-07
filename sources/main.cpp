// Copyright 2019 CERZAR

#include <iostream>
#include "../include/AnalyserFTP.h"
#include <boost/filesystem.hpp>
#define p "../misc/ftp"

int main(int argc, char *argv[]){
    boost::filesystem::path path = ".";
    if (argc > 1) {
        path = argv[1];
    }
    AnalyserFTP analyzer(p);
    analyzer.start_passage(p);

    std::cout << std::endl;
    std::cout << "\tALL FILES" << std::endl;
    std::cout << "______________________________________" << std::endl;
    analyzer.print_all_files();
    std::cout << std::endl << std::endl;

    std::cout << "\tACCOUNT GROUPS INFO" << std::endl;
    for (int i = 0; i < 66; i++)
        std::cout << "_";
    std::cout << std::endl;
    analyzer.print_account_groups_info();
    std::cout << std::endl << std::endl;
    return 0;
}
