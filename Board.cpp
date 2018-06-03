/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <ctime>
#include "Board.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>
#pragma once
using namespace std;

ostream& operator<<(ostream& out,const Board& board){
    out<<"";
 for(int i=0;i<board.size;i++){
        for(int j=0;j<board.size;j++){
           out << board.board[i][j].get_node(); 
        }
        out << "" <<endl;
    }
    return out;

}



Node& Board::operator[](const list<int> list){
    int a=list.front(),b=list.back();
    if(a<0 || a>=size || b<0 || b>=size){
        IllegalCoordinateException ex(a,b);
        throw ex;
    }
    return this->board[a][b];
}

Node& Board::operator[](const Coordinate& c) const{
    int a = c.getRow(), b = c.getCol();

    if (a < size && b < size)
        return board[a][b];
    else
    {
        IllegalCoordinateException ex(a,b);
        throw ex;
    }
}

Node& Node::operator=(char c)
{
   if(c=='X' || c=='O' || c=='.'){
        this->cell = c;
        return *this;
   }
    else{
       IllegalCharException ex(c);
        throw ex;
    }
 
}


Node::operator char()const{
    return cell;
}

Board& Board::operator=(char c){
    if (c=='.') {
        for (int j = 0; j < size; ++j) {
            for (int i = 0; i < size; ++i) {
                board[i][j] = '.';
            }
        }
    }
    else{
       IllegalCharException ex(c);
        throw ex; 
    }
    return *this;
}

Board& Board::operator=(const Board &b){
    if (this==&b)
        return *this;
    if (b.size!=size) {
        for (int i = 0; i < size; i++)
            delete[] board[i];
        delete [] board;

        size = b.size;
        board = new Node*[b.size];
        for (int i = 0; i < size; i++) 
            board[i] = new Node [size];
    }
    for (int i=0; i < size; ++i){
        for(int j=0 ;j < size ; j++){
            board[i][j]= Node{b.board[i][j].get_node()};
        }
    }
    return *this;
}

string Board::draw(int num){
   // string c_time = to_string(ms.count());
    string temp=to_string(num*size);
    string name= "board_"+temp+".ppm";
    ofstream imageFile(name, ios::out | ios::binary);
    
    imageFile << "P6" << endl << num <<" " << num << endl << 255 << endl;
    
    RGB image[num*num];
    double calc=num/size;
    double calc2= calc/size;


     for (int j = 0; j < num; ++j)  {  
        for (int i = 0; i < num; ++i) { 
            image[num*j+i].red = (0);
            image[num*j+i].green = (0);
            image[num*j+i].blue = (0);

        }
    }

    for(int k=0;k<num;){
           for(int j=calc;j<num;){
             image[num*j+k].red = (255);
             image[num*j+k].green = (255);
            image[num*j+k].blue = (255);
            
           image[j+num*k].red = (255);
             image[j+num*k].green = (255);
            image[j+num*k].blue = (255);
           j=j+calc;
           }k=k+1;}

   
//     for(int i=1; i < size-1; i++)
//        for(int j=1; j< size-1;j++){
//            if(board[i][j].get_node() == 'X'){
//                for(double m = i*num*calc; m< i*num*calc+calc; ){
//                    int y=0;
//                    for(double k=j*calc ; k< j*calc+calc;){
//                    image[(int)m+(int)k].red=(50);
//                     image[(int)m+(int)k].green=(150);
//                      image[(int)m+(int)k].blue=(100);
//                      image[2*(int)m+(int)k].red=(255);
//                      y++;
////                    image[num*(int)calc*i+num*(int)m+(int)calc+j*(int)calc-(int)m].green=(255);
////                    image[num*(int)calc*i+num*(int)m+(int)calc+j*(int)calc-(int)m].blue=(255);
//                    k=k+1;m=m+num;}
//                }   
//            }
//                for(int m = 15; m<calc-16; m++){
//                    image[num*(int)calc*i+num*m+j*(int)calc+m].red=(255);
//                    image[num*(int)calc*i+num*m+j*(int)calc+m].green=(255);
//                    image[num*(int)calc*i+num*m+j*(int)calc+m].blue=(255);
//                    image[num*(int)calc*i+num*m+j*(int)calc+(int)calc-m].red=(255);
//                    image[num*(int)calc*i+num*m+(int)calc+j*(int)calc-m].green=(255);
//                    image[num*(int)calc*i+num*m+(int)calc+j*(int)calc-m].blue=(255);
//            }
//            }
     for(int i=0; i < size; i++)
        for(int j=0; j< size;j++){
            if(board[i][j].get_node() == 'X'){
                for(int m = calc/calc2; m<calc; m++){
                    int a= num*calc*i+j*calc;
                    image[a+num*m+m].red=(255);
                    image[a+num*m+m].green=(255);
                    image[a+num*m+m].blue=(255);
                    image[a+num*m+(int)calc-m].red=(255);
                    image[a+num*m+(int)calc-m].green=(255);
                    image[a+num*m+(int)calc-m].blue=(255);
                }
            }
        else if (board[i][j].get_node() == 'O'){
                int a= num*calc*i+j*calc;
                int b=a+num*(calc/2)+(calc/2);
                int radius=calc/2.;
                int is = i*calc, js=j*calc;
                int im=is+calc/2, jm=js+calc/2;
                for (int k = is; k <((i+1)*calc);k++) {
                    for (int l = js; l < ((j+1)*calc); l++) {
                        if(abs((k-im)*(k-im)+(l-jm)*(l-jm)-radius*radius)<= pow((calc/radius),6)){
                            image[num*k+l].red=(255);
                            image[num*k+l].green=(255);
                            image[num*k+l].blue=(255);
                        }
                    }
                }
            }
            
    }
    imageFile.write(reinterpret_cast<char*>(&image), 3*num*num);
  imageFile.close();
  return name;
}