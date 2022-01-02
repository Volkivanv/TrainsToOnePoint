#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>

std::mutex trains_mtx;

void trainGo(char trainLit, int time){
    for(int i = time; i > 0; i--) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    trains_mtx.lock();
    std::string command;
    std::cout<<"Train "<<trainLit<<" arrived"<<std::endl;
    while (command!="depart") {
        std::cout << "input 'depart'" << std::endl;
        std::cin >> command;
    }
    trains_mtx.unlock();

}

int main() {
    constexpr int n = 3;
    std::vector<int>trainsTime(n);
    std::vector<std::thread>trains;
    std::cout << "Input way time" << std::endl;
    for(int i = 0; i<trainsTime.size();i++){
        char c = 'A'+i;
        std::cout<<"Train "<< c <<" : ";
        std::cin>>trainsTime[i];
    }

    for(int i = 0; i<trainsTime.size();i++){
        char c = 'A'+i;
        trains.emplace_back(trainGo,c,trainsTime[i]);
    }

    for(int i = 0; i<trains.size();i++){
        trains[i].join();
    }
    return 0;
}
