// Copyright 2019 CERZAR

#include <iostream>
#include "../include/AnalyserFTP.h"
#define path_to_ftp "/home/cezar/CERZAR/workspace/labs/lab-04-boost-filesystem/misc/ftp"

int main(int argc, char *argv[]){
    boost::filesystem::path path = ".";
    if (argc > 1) {
        path = argv[1];
    }
    AnalyserFTP analyzer(path_to_ftp);
    analyzer.start_passage(path_to_ftp);

    std::cout << std::endl;
    std::cout << "\tALL FILES" << std::endl;
    std::cout << "______________________________________" << std::endl;
    analyzer.print_all_files();
    std::cout << std::endl << std::endl;

    std::cout << "\tACCOUNT GROUPS INFO" << std::endl;
    std::cout << "_________________________________________________________________" << std::endl;
    analyzer.print_account_groups_info();
    std::cout << std::endl << std::endl;
    return 0;
}
