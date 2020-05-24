//
//  Network.cpp
//  QingNianDaXueXi
//
//  Created by Danny on 2020/5/23.
//  Copyright © 2020 Danny. All rights reserved.
//

#include "Network.hpp"
#include<set>
#include<map>
#include<string>
#include<iostream>
#include<sstream>
void Network::refreshUrl()
{
    urls.clear();
    std::string str;
    std::string && sourceCode = this->getSourceCode("http://news.cyol.com/node_67071.htm");
    std::regex pattern("<li><a href=\"(([:]|[0-9]|[a-z]|[A-Z]|[/]|[.])*)\" target=\"_blank\" class=\"transition\">");
    std::regex titlePattern("<h3><a href=\"(([:]|[0-9]|[a-z]|[A-Z]|[/]|[.])*)\" target=\"_blank\">([^<>]*)</a></h3>");
    std::smatch matchResult;
    while(regex_search(sourceCode,matchResult,pattern))
    {
        std::string title,url;
        url = matchResult[1].str();
        regex_search(sourceCode,matchResult,titlePattern);
        title = matchResult[3].str();
        urlFormat(url);
        this->urls.push_back({title,url});
        sourceCode = matchResult.suffix();
    }
    
}
void Network::urlFormat(std::string& url)
{
    if(url.back()=='/')// /
    {
        url+="m.html";
    }
    std::stringstream stream;
    std::regex reg("index");
    std::regex_replace(std::ostreambuf_iterator<char>(stream),url.begin(),url.end(),reg,"m");
    stream>>url;
    url+="?t=1&z=200";
}
std::string Network::getSourceCode(const std::string& url)
{
    std::string sourceCode;
    CURL *curl = curl_easy_init();
    if(!curl){throw NetworkException("Cannot initialize network component!");    }
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&sourceCode);
    CURLcode retCode= curl_easy_perform(curl);
    if(retCode!=CURLE_OK)
    { throw NetworkException("unexpected error occurred!");}
    curl_easy_cleanup(curl);
    return sourceCode;
}
size_t Network::write_callback(char* ptr, size_t size,size_t number,void* to)
{
    std::string *writeTo= (std::string *)to;
    (*writeTo) += ptr;
    return size*number;
}
void Network::urlShowList()
{
    int i = 0;
    for(auto &x : this->urls)
    {
        std::cout<<'['<<i<<']'<<x.first<<std::endl;
        i++;
    }
}
void Network::showAns(std::vector<std::string> ans)
{
    int i = 1;
    for(auto &x:ans)
    {
        std::cout<<i<<'.'<<x<<std::endl;
        i++;
    }
}
std::vector<std::string> Network::getAnswer(int number)
{
    if(number<0||number>=this->urls.size())
    {
        throw NetworkException("Invalid number or need upgrading!");
    }
    if(this->ansBuffer.count(this->urls.at(number).first))
    {
        return ansBuffer.at(this->urls.at(number).first);
    }
    else
    {
        std::regex sectionPattern("<div class=\"section[0-9]*\">(\\s*<div class=.*></div>\\s){1,100}\\s*</div>"),
        selectionPattern("<div class=\"w[0-9][^0-9]*\" data-a=\"([0-9])\" data-b=\"[0-9]*\" data-c='[1-9]'></div>"),
        dragPattern("\\$\\(\"\\.drag[1-9]*_click\"\\)\\.on\\('click',function\\(\\)\\{\\s*if\\(.*");
        std::vector<std::string> sectionAnswer,dragAnwser;
        std::string sourceCode = getSourceCode(this->urls.at(number).second);
        std::string temp= sourceCode;
        std::smatch result,result1;
        while(std::regex_search(sourceCode,result,sectionPattern))
        {
            sourceCode = result.suffix();
            sectionAnswer.push_back("");
            std::string temp = result[0].str();
            int i = 0;
            while(std::regex_search(temp,result1,selectionPattern))
            {
                if(result1[1].str()=="1")sectionAnswer.back()+='A'+i;
                i++;
                temp = result1.suffix();
            }
            if(i == 0||sectionAnswer.back().length()==0)
            {
                sectionAnswer.pop_back();
            }
        }
        sourceCode = temp;
        while(std::regex_search(sourceCode,result,dragPattern))
        {
            sourceCode = result.suffix();
            dragAnwser.push_back(getDragAnwser(result[0]));
        }
        std::vector<std::string>ans = this->merge(temp,sectionAnswer,dragAnwser);
        return ans;
    }
    
}
std::string Network::getDragAnwser(std::string code)
{
    //if(data1.ary2[0]==2 && data1.ary2[1]==3 && data1.ary2[2]==1 && data1.ary2[3]==0){
    std::string ret;
    std::regex reg("==\\s*([0-9])");
    std::smatch match;
    while(std::regex_search(code,match,reg))
    {
        ret += std::to_string(std::stoi(match[1].str())+1);
        code = match.suffix();
    }
    return ret;
}
std::vector<std::string> Network::merge(std::string code,std::vector<std::string>&section , std::vector<std::string> &drag)
{
    //<div class="section1">
    std::vector<std::string> ret;
    std::smatch match;
    std::regex reg("<div class=\"([a-z]*)[1-9]*\">");
    int sec = 0,dra = 0; //  drag or section
    while(std::regex_search(code,match,reg))
    {
        code = match.suffix();
        if(match[1].str()=="section"&&sec<section.size())
        {
            ret.push_back(section.at(sec++));
        }
        else if(match[1].str() == "drag"&&dra<drag.size())
        {
            ret.push_back(drag.at(dra++));
        }
    }
    
    return ret;
}
