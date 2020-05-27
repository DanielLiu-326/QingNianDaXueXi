//
//  main.cpp
//  QingNianDaXueXi
//
//  Created by Danny on 2020/5/23.
//  Copyright © 2020 Danny. All rights reserved.
//

#include <iostream>
#include"Network.hpp"
#include"Program.hpp"
int main(int argc, const char * argv[]) {
    // insert code here...
    Network network;
    network.refreshUrl();
    int input ;
    while(true)
    {
        Program::showMenu();
        std::cin>>input;
        try {
            switch (input) {
                case 1:
                {
                    Program::getAnswer(network);
                }break;
                case 2:
                {
                    Program::showList(network);
                }break;
                case 3:
                {
                    Program::refreshList(network);
                }break;
                case 4:
                {
                    exit(0);
                }break;
                default:
                    std::cout<<"No selection of "<<input<<std::endl;
                    break;
        }
        }catch(std::exception & exc)
        {
            std::cout<<"***error***:"<<exc.what()<<std::endl;
        }
    }
    network.urlShowList();
    network.showAns(network.getAnswer(0));
    return 0;
}
