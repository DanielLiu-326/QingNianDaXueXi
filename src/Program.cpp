//
//  Program.cpp
//  QingNianDaXueXi
//
//  Created by Danny on 2020/5/24.
//  Copyright © 2020 Danny. All rights reserved.
//

#include "Program.hpp"
void  Program::showMenu()
{
    using namespace std;
    std::cout<<"====MainMenu===="<<std::endl
    <<"1.get answer"<<std::endl
    <<"2.show list"<<std::endl
    <<"3.refresh urls"<<std::endl
    <<"4.EXIT"<<std::endl;
}
void Program::showList(Network& network)
{
    network.urlShowList();
}
void Program::getAnswer(Network& network)
{
    int input;
    network.urlShowList();
    std::cout<<"input:";
    std::cin>>input;
    network.showAns(network.getAnswer(input));
}
void Program::refreshList(Network&network)
{
    network.refreshUrl();
    std::cout<<"Done"<<std::endl;
}
