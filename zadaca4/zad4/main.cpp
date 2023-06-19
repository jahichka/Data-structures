#include<iostream>
#include <ostream>
#include "circularBuffer.hpp"

int main(){
    circularBuffer<int> queue(3);
    queue.push(5);
    std::cout<<queue.front()<<" "<<queue.back()<<std::endl;
    int a=10;
    queue.push(a);
    std::cout<<queue.front()<<" "<<queue.back()<<std::endl;

    if(!queue.empty())
    {
        std::cout<<queue.front()<<" "<<queue.back()<<std::endl;
    }
    queue.pop();
    //std::cout<<queue.front()<<std::endl;
    a=queue.pop();
    std::cout<<a<<std::endl;
    queue.back();    
}