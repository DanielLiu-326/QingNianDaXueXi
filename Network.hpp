//
//  Network.hpp
//  QingNianDaXueXi
//
//  Created by Danny on 2020/5/23.
//  Copyright © 2020 Danny. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp
#include<vector>
#include<string>
#include<curl/curl.h>
#include<exception>
#include<regex>
#include<map>
struct NetworkException:public std::exception
{
    std::string description;
    NetworkException(const std::string& desc)throw():description(desc)
    {}
    virtual const char * what()const throw()
    {
        return this->description.c_str();
    }
};
class Network
{
public:
    std::vector<std::pair<std::string,std::string>> urls;
    void refreshUrl();
    void urlFormat(std::string& url);
    void urlShowList();
    std::vector<std::string> getAnswer(int number);
    void showAns(std::vector<std::string>);
private:
    std::string getSourceCode(const std::string& url);
    static size_t write_callback(char* ptr, size_t size,size_t number,void* to);
    std::map<std::string,std::vector<std::string>> ansBuffer;
    std::string getDragAnwser(std::string code);
    std::vector<std::string> merge(std::string code,std::vector<std::string>&section , std::vector<std::string> &drag);
};

#endif /* Network_hpp */
