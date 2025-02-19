#ifndef PARSER_HPP
#define PARSER_HPP
#pragma once
#include <fstream>
#include <string>
#include <vector>
class Parser{
    public:
        Parser(std::string const& stream_name);
        Parser();
        ~Parser() = default;
        void parse_file();
        std::string stream_name();
        std::vector<std::string> buff();
    private:
        std::string sname_;
        std::ifstream graph_file_;
        std::vector<std::string> buff_;
        void slurp_file();
};


#endif // PARSER_HPP
