#include "../include/parser/parser.hpp"
#include <iostream>
Parser::Parser()
{
    
}

Parser::Parser(std::string const& stream_name)
:
    sname_{stream_name}
{
    //graph_file_.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{ 
        graph_file_.open(sname_);
        if (!graph_file_.is_open()) {
            std::cerr << "Could not open file: " << sname_ << '\n';
            throw std::runtime_error("File not opened");
        }
    } catch(std::ios_base::failure& e) {
        std::cerr << e.what()  << '\n';
        throw;
    }
}
void Parser::slurp_file()
{
    std::string line;
    while (std::getline(graph_file_, line)) {
        buff_.push_back(line);
    }
    for (auto const& line : buff_) {
        std::cout << line << '\n';
    }
}
void Parser::parse_file()
{
    slurp_file();
}
std::string Parser::stream_name()
{
    return sname_;
}
std::vector<std::string> Parser::buff()
{
    return buff_;
}

