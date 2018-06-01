/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
//     char temp=(char)num;
//    string name= "board_.ppm";
//    name.insert(6,1,temp);
//    char* temp=(char*)num;
    string temp=to_string(num);
    string name= "board_"+temp+".ppm";
   // name.insert(6,1,temp);
    ofstream imageFile(name, ios::out | ios::binary);
    imageFile << "P6" << endl << num <<" " << num << endl << 255 << endl;
    BnW image[num*num];
    for(int i=0;i<num; i++){
        for(int j=0 ; j<num ; j++){
          image[num*j+i].black = (i % 256);  
        }
    }
    for(int i=0; i < num; i++)
        for(int j=0; j< num;j++){
            for (int m = i*size+num; m < i*size+size-num; ++m){
                for (int p = j * size + num; p < j * size + size - num; ++p){
                    image[num * m + p].white = (255);
                }
            }
        }
     for(int i=0; i < size; i++)
        for(int j=0; j< size;j++){
            if(this->board[i][j].get_node() == 'X'){
                for(int m = 15; m<size-16; m++){
                    image[num*size*i+num*m+j*size+m].white=(255);
                }   
                }
        else if (board[i][j].get_node() == 'O'){
                int a= num*size*i+j*size;
                int b=a+num*(size/2)+(size/2);
                int radius=size/2.5;
                int is = i*size, js=j*size;
                int im=is+size/2, jm=js+size/2;
                for (int k = is; k <((i+1)*size);k++) {
                    for (int l = js; l < ((j+1)*size); l++) {
                        if(abs((k-im)*(k-im)+(l-jm)*(l-jm)-radius*radius)<= pow((size/radius),6)){
                            image[num*k+l].white=(255);
                             }
                    }
                }
        }
            
    }
    imageFile.write(reinterpret_cast<char*>(&image), num*num);
  imageFile.close();
  return name;
}