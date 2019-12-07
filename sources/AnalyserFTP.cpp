// Copyright 2019 CERZAR

#include "../include/AnalyserFTP.h"
#include <utility>

bool CompareByDate(const FinancialFile& file1, const FinancialFile& file2)
{
    if (file1.date.year < file2.date.year)
        return true;
    if (file1.date.year > file2.date.year)
        return false;

    if (file1.date.month < file2.date.month)
        return true;
    if (file1.date.month > file2.date.month)
        return false;

    if (file1.date.day < file2.date.day)
        return true;
    if (file1.date.day > file2.date.day)
        return false;

    return false;
}

std::ostream& operator<< (std::ostream &out, const Date &date)
{
    out << date.year << "-" << date.month << "-" << date.day;

    return out;
}

AnalyserFTP::AnalyserFTP(fs::path path)
{
    this->path_to_ftp = std::move(path);
}

FinancialFile AnalyserFTP::parce_filename(std::string filename)
{
    FinancialFile file;

    file.name = filename;

    file.type = filename.substr(0, filename.find('_'));
    filename = filename.substr(filename.find('_') + 1);

    file.account_number = std::stoi(filename.substr(0, filename.find('_')));
    filename = filename.substr(filename.find('_') + 1);

    file.date.year = std::stoi(filename.substr(0, 4));
    file.date.month = std::stoi(filename.substr(4, 2));
    file.date.day = std::stoi(filename.substr(6, 2));
    filename = filename.substr(8);

    if (filename[0] != '.' || filename.substr(0, 4) == ".old")
        throw std::exception();   // Ignored file with wrong syntax or ".old"

    if (filename.substr(1).find('.') != std::string::npos)
        throw std::exception();

    file.extension = filename;

    return file;
}

void AnalyserFTP::start_passage(const fs::path& path)
{
    for (const fs::directory_entry& dir_iter : fs::directory_iterator{ path })
        if (fs::is_regular_file(dir_iter))
            analyze_file(dir_iter);
        else if (fs::is_directory(dir_iter))
            analyze_dir(dir_iter);

    if (!directories.empty())
        directories.pop_back();
}

void AnalyserFTP::analyze_dir(const fs::path& dir_path)
{
    directories.push_back(dir_path.stem().string());
    start_passage(dir_path);
}

void AnalyserFTP::analyze_file(const fs::path& file_path)
{
    try
    {
        FinancialFile file = parce_filename(file_path.filename().string());
        file.broker = directories[directories.size()-1];

        files.push_back(file);
        account_groups[file.account_number].push_back(file);
    }
    catch (const std::exception&){}
}

void AnalyserFTP::print_all_files()
{
    for (const auto& file : files)
        std::cout << file.broker << " " << file.name << std::endl;
}

void AnalyserFTP::print_account_groups_info()
{
    for (auto group : account_groups)
    {
        std::cout << "broker: " << group.second[0].broker << " ";

        std::cout << "account: ";
        for (int i = 0; i < 8 - group.first; i++)
            std::cout << '0';
        std::cout << group.first << " ";

        std::cout << "files: " << group.second.size() << " ";

        std::cout << "lastdate: " << std::max_element(group.second.begin(),
                group.second.end(), CompareByDate)->date << " ";

        std::cout << std::endl;
    }
}

