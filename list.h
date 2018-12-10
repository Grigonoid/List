#include <stdio.h>

const int ERROR = -1;
const int OK = 1;
const int CAN1 = 666;
const int CAN2 = 999;

struct Node 
{
	int can1;
	int data;
	Node* next;
	Node* prev;
	unsigned checksum;
	int can2;
};

Node* Create_Node (int data);
int Insert_After (Node* cur, int data);
int Insert_Before (Node* cur, int data);
int Delete_Node (Node* cur);
int Delete_List (Node** cur);
int Ok (Node* cur);
int Print_Full_List (Node* cur);
int Print_List_From_Cur (Node* cur);
int Calculate_Index (Node* cur);
Node* Search (Node* cur, int data);
void Calculate_Checksum (Node* cur);
unsigned Return_Checksum (Node* cur);

#include "list_funcs.cpp"

