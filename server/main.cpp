#include <iostream>
#include <regex>

#include <server.h>

int main(int, char **)
{
    // std::regex rgx("[^\\d]+");
    // std::string string_to_split = "2    0   ";
    // std::sregex_token_iterator iter(string_to_split.begin(),
    //                                 string_to_split.end(),
    //                                 rgx,
    //                                 -1);
    // std::sregex_token_iterator end;
    // for (; iter != end; ++iter)
    //     std::cout << *iter << '\n';
    Server server{Server::TCP};
    server.start(8080);
    server.run();
 //   server.close();
}
