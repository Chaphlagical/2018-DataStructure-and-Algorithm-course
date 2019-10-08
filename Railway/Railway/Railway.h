#ifndef __RAILWAY_H
#define __RAILWAY_H

#define MAXSIZE 25
#define INF 147483647



#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

typedef struct railway{
    int**G;
    int**D;
    std::string*city;
    std::string**path;
}railway;

void Create_Graph(int **G);
void Path_Init(railway R);
void Floyd(railway&R);
void Get_city(railway&R);
bool Delete_City(railway&R,std::string city);
int Get_index(railway R,std::string city);
void Reset(railway&R);

#endif // __RAILWAY_H
