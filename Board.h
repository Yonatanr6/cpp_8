/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: Yoni
 *
 * Created on May 8, 2018, 6:33 PM
 */

#include <iostream>
#include <vector>
#include <exception>
#include <list>
#pragma once
using namespace std;



class IllegalCoordinateException : public exception{
    int a,b;
    public: 
        IllegalCoordinateException(int num, int num2){
            a=num;
            b=num2;
        }
        string theCoordinate ()const{
            return to_string(a)+","+to_string(b);
        }
};

class IllegalCharException : public exception{
    char ch;
public:
     IllegalCharException(char c){
        ch = c;
    }
    const char theChar() const throw (){
        return ch;
   }
};

struct RGB {
  uint8_t red, green, blue;
public:
  RGB() {}
  RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};

class Node{
    char cell;
public:
    Node(){};
    
    Node(const char ch){
          if(ch=='X' || ch== 'O' || ch=='.')
        this->cell = ch;
    else{
        IllegalCharException ex(ch);
        throw ex;
    }
};



Node(const Node& n){
    this->cell = n.get_node();
};

char get_node() const {
    return this->cell;
}

Node& operator=(char val);

friend ostream& operator<<(ostream& out,const Node& node);
operator char()const;

};


class Coordinate
{
    int row,col;
public:
    
    void setCoordinate(Coordinate c){row = c.row,col = c.col;};
    int getRow()const{return row;};
    int getCol()const{return col;};
    void setRow(int x){row=x;};
    void setCol(int y){col=y;};
    

    Coordinate(int x,int y){
        row=x,col=y;
    }
};



class Board{
public:    
    int size;
   Node **board;
    
    friend ostream& operator<<(ostream& out,const Board& board);
    friend istream& operator>>(istream& is,const Board& board);
    string draw(int n);
  
    Board& operator=(char c);
    Node& operator[](const list<int> list);
    Node& operator[](const Coordinate& c) const;
    Board& operator=(const Board& b);
    
    Board(){};
    
     Board(const Board& b){
      size=b.size; 
      board = new Node*[size];
      for (int i = 0; i < size; i++) {
	board[i] = new Node[size];
	}
    for(int i = 0; i < size; i++) {
	for(int j = 0; j < size; j++) {
	board[i][j]= b.board[i][j];
		}
	}
    };
    
    Board(int num){
      size=num; 
      board = new Node*[size];
      for (int i = 0; i < size; i++) {
	board[i] = new Node[size];
	}
    for(int i = 0; i < size; i++) {
	for(int j = 0; j < size; j++) {
	board[i][j]= Node{'.'};
		}
	}
    };
    
    ~Board(){
        for(int i = 0; i < size; i++)
            delete[] board[i];
        delete[] board;
    };
    
};

inline ostream& operator<<(ostream& out,const Node& node){
    out<<"";
    out<<node.get_node();
     out << "" <<endl;
     return out;
}


 inline istream& operator>> (istream& is, Board& board){  
    string str;
    is>>str;
    int n = str.length();
    Board temp(n);
    board=temp;
    for (int i=0; i<n; i++){
        board[{0,i}] = str[i];   
    }
    int curr = 1;
    while(is>>str){
        for (int i=0; i<n; i++){
            board[{curr, i}] = str[i];
        }
        curr++;
    }
    return is;
}







