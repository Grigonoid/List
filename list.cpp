#include "list.h"

int main() 
{
	Node* elem = Create_Node(200);
	Insert_After(elem, 300);
	Insert_After(elem->next, 400);
	Insert_Before(elem, 100);
	Insert_Before(elem, 150);
	Insert_After(elem, 250);
	Print_Full_List(elem);
	printf("Element:%d.\nIndex:%d.\n", elem->next->data, Calculate_Index(elem->next));
	printf("%p\n", elem);
	Delete_List(&elem);
	Print_Full_List(elem);
	printf("%p\n", elem);
}
