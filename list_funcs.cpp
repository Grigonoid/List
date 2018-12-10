Node* Create_Node (int data)
{
	Node* new_node = new Node;
	if (new_node == NULL) {
		printf("Узел не может быть создан.\n");
		return NULL;
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->can1 = CAN1;
	new_node->can2 = CAN2;
	Calculate_Checksum(new_node);
	return new_node;
}

int Insert_After (Node* cur, int data)
{
	if (Ok(cur) == ERROR) return ERROR;
	Node* node_after = Create_Node(data);
	if (Ok(node_after) == ERROR) return ERROR;
	node_after->next = cur->next;
	node_after->prev = cur;
	cur->next = node_after;
	Calculate_Checksum(node_after);
	Calculate_Checksum(cur);
	if (node_after->next) {
		node_after->next->prev = node_after;
		Calculate_Checksum(node_after->next);
	}
	if (Ok(node_after) == ERROR) return ERROR;
	return OK;
}

int Insert_Before (Node* cur, int data)
{
	if (Ok(cur) == ERROR) return ERROR;
	Node* node_before = Create_Node (data);
	if (Ok(node_before) == ERROR) return ERROR;
	node_before->next = cur;
	node_before->prev = cur->prev;
	cur->prev = node_before;
	Calculate_Checksum(node_before);
	Calculate_Checksum(cur);
	if (node_before->prev) {
		node_before->prev->next = node_before;
		Calculate_Checksum(node_before->prev);
	}
	if (Ok(node_before) == ERROR) return ERROR;
	return OK;
}

int Delete_Node (Node* cur)
{
	if (Ok(cur) == ERROR) return ERROR;
	if (cur->next) {
		cur->next->prev = cur->prev;
		Calculate_Checksum(cur->next);
	}
	if (cur->prev) {
		cur->prev->next = cur->next;
		Calculate_Checksum(cur->prev);
	}
	delete cur;
	cur->next = NULL;
	return OK;
}

int Delete_List (Node** cur)
{
	if (Ok(*cur) == ERROR) return ERROR;
	while ((*cur)->prev != NULL)
		*cur = (*cur)->prev;
	while ((*cur)->next != NULL) {
		*cur = (*cur)->next;
		delete (*cur)->prev;
	}
	delete *cur;
	*cur = NULL;
	return OK;
}

int Print_Full_List (Node* cur)
{
	if (Ok(cur) == ERROR) return ERROR;
	while (cur->prev != NULL)
		cur = cur->prev;
	while (cur->next != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("%d\n", cur->data);
	return OK;
}

int Print_List_From_Cur (Node* cur)
{
	if (Ok(cur) == ERROR) return ERROR;
	while (cur->next != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("%d\n", cur->data);
	return OK;
}

int Calculate_Index (Node* cur)
{
	if (Ok(cur) == ERROR) return ERROR;
	int index = 1;
	while (cur->prev != NULL) {
		cur = cur->prev;
		index++;
	}
	return index;
}

Node* Search (Node* cur, int data_to_find)
{
	if (Ok(cur) == ERROR) return NULL;
	Node* temp = cur;
	if (cur->data == data_to_find) 
		return cur;
	while (cur->prev != NULL) {
		if (cur->prev->data == data_to_find)
			return cur->prev;
		cur = cur->prev;
	}
	while (cur->next != NULL) {
		if (cur->next->data == data_to_find)
			return cur->next;
		cur = cur->next;
	}
	return NULL;
}

int Ok (Node* cur)
{
	if (cur == NULL) {
		printf("Обращение по нулевому указателю.\n");
		return ERROR;
	}
	if (cur->can1 != CAN1 || cur->can2 != CAN2) {
		printf("Нарушена структура узла.\n");
		return ERROR;
	}
	if (cur->checksum != Return_Checksum(cur)) {
		printf("Несанкционированное изменение указателей.\n");
		return ERROR;
	}
	return OK;
}

void Calculate_Checksum (Node* cur)
{
	cur->checksum = ((unsigned long long)(cur->prev)*322 + (unsigned long long)(cur->next)*228) % 13337;
}

unsigned Return_Checksum (Node* cur)
{
	return ((unsigned long long)(cur->prev)*322 + (unsigned long long)(cur->next)*228) % 13337;
}



