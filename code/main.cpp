#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

// size
const int grid_size_x = 60;
const int grid_size_y = 20;

// chars
const char filled_char = '#'; 
const char empty_char = '-';

// game state settings
const int initial_count = 10;
const int tick_rate = 100;


bool running = true;
char grid[grid_size_y][grid_size_x];

std::default_random_engine generator((unsigned int) time(0));
std::uniform_int_distribution<int> distribution(1,100/initial_count);

void populate_grid(){
    for(int y = 0; y < grid_size_y; y++){
        for(int x = 0; x < grid_size_x; x++){

            int dice_roll = distribution(generator);  
                                                      
            if(dice_roll == 1){
                grid[y][x] = filled_char;
            }
            else{
            grid[y][x] =empty_char;
            }
        }
    }
}

void print_grid(){
    for (int y = 0; y < grid_size_y; y++){
        for(char chara : grid[y]){
            std::cout << chara;
        }
        std::cout << "\n";

    }
}

int count_neighbors(int y, int x){
    int neighbor_count = 0;

    // left
    if(grid[y][x-1] == filled_char){
        neighbor_count ++;
    }
    // right
    if(grid[y][x+1] == filled_char){
        neighbor_count ++;
    }
    //top
    if(grid[y+1][x] == filled_char){
        neighbor_count ++;
    }
    //down
    if(grid[y-1][x] == filled_char){
        neighbor_count ++;
    }
    // top right
    if(grid[y+1][x+1] == filled_char){
        neighbor_count ++;
    }
    // top left
    if(grid[y+1][x-1] == filled_char){
        neighbor_count ++;
    }
    // bottom left
    if(grid[y-1][x-1] == filled_char){
        neighbor_count ++;
    }
    // bottom right
    if(grid[y-1][x+1] == filled_char){
        neighbor_count ++;
    }

    return neighbor_count;

}

void update_grid(){
    for(int y = 0; y < grid_size_y; y++){
        for(int x = 0; x < grid_size_x; x++){
           // check neighbors to see if value should change 
           
            
           int neighbor_count = count_neighbors(y,x);

           if(neighbor_count < 2){
               grid[y][x] = empty_char;
           }
           else if(neighbor_count == 3){
               grid[y][x] = filled_char;
           }
           else if(neighbor_count > 3){
               grid[y][x] = empty_char;
           }
      }
    }
}

void clear(){
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout << "\033[2J;" << "\033[1;1H";
#elif defined (__APPLE__)
    std::cout << "\033[2J;" << "\033[1;1H";
#endif
}

int main(){
    // sleep line too long
    using namespace std::this_thread;
    using namespace std::chrono;
    
    populate_grid();

    while(running){

        clear();
        update_grid();
        print_grid();

        sleep_for(milliseconds(tick_rate));


    } 
}
