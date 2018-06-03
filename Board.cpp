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

    string temp=to_string(num*size);
    string name= "board_"+temp+".ppm";
    ofstream imageFile(name, ios::out | ios::binary);
    
    imageFile << "P6" << endl << num <<" " << num << endl << 255 << endl;
    
    RGB image[num*num];
    double calc=num/size;
    double calc2= calc/size;
    int radius=calc/2;

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

     for(int i=0; i < size; i++)
        for(int j=0; j< size;j++){
            if(board[i][j].get_node()=='X'){
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
        else if (board[i][j].get_node()=='O'){
                for (int k = i*calc; k <((i+1)*calc);k++) {
                    for (int l = j*calc; l < ((j+1)*calc); l++) {
                        if(abs((k-(i*calc+radius))*(k-(i*calc+radius))+(l-(j*calc+radius))*(l-(j*calc+radius))-radius*radius)<= pow((calc/radius),8)){
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