//
//  Program.hpp
//  QingNianDaXueXi
//
//  Created by Danny on 2020/5/24.
//  Copyright © 2020 Danny. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp
#include"Network.hpp"
#include <iostream>
// 1. show list  2.get answer  3. refresh 
class Program
{
public:
    static void  showMenu();
    static void showList(Network& network);
    static void getAnswer(Network & network);
    static void refreshList(Network& network);
    
private:
};
#endif /* Program_hpp */
