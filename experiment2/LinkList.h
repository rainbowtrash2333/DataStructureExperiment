//���ݽṹ
typedef struct LNode {
	double coef; //����ʽ��ϵ�� 
	double expn; //����ʽ��ָ�� 
	struct LNode *next; //ָ����һ������ʽ����ָ�� 
} Link;

//����
typedef struct {
	Link* head;
	Link* tail;
	int len;
}LinkList;

//��ӽڵ�
void AddNode(LinkList* L, double coef, double expn) {
	Link *p = NULL;
	p = new Link;
	p->next = NULL;
	L->tail->coef = coef;
	L->tail->expn = expn;
	L->tail = L->tail->next = p;
	L->len++;
}

//��������
//��ʼ������
void InitList(LinkList& L) {
	L.head = L.tail = new Link;
	L.len = 0;
};
//ɾ������
void DestroyList(LinkList& L) {
	delete &L;
};
//�����ڵ�
void swapLink(Link* L1, Link* L2) {
	double tempCoef = L1->coef;
	double tenpExpnv = L1->expn;

	L1->coef = L2->coef;
	L1->expn = L2->expn;

	L2->coef = tempCoef;
	L2->expn = tenpExpnv;
}
//ɾ���ڵ�
void deleteLink(Link* L, LinkList& linklist) {
	L->next = L->next->next;
	linklist.len--;
};

//ð������(�ɴ�С��
void LinkListBubbleSort(LinkList& L) {
	Link* index;
	for (int i = 0; i < L.len - 1; ++i) {
		index = L.head;
		for (int j = 0; j < L.len - i - 1; ++j) {
			if (index->next->coef == 0) {
				deleteLink(index, L);
			}
			if (index->expn == index->next->expn) {
				index->coef += index->next->coef;
				deleteLink(index, L);
			}
			if (index->expn < index->next->expn) {
				swapLink(index, index->next);
			}
			index = index->next;
		}
	}
}

//�ӷ�
LinkList AddPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	LinkList result;
	InitList(result);

	while (L1.head->next != NULL || L2.head->next != NULL) {
		if (L1.head->expn > L2.head->expn) {
			AddNode(&result, L1.head->coef, L1.head->expn);
			L1.head = L1.head->next;
		}
		else if (L1.head->expn < L2.head->expn) {
			AddNode(&result, L2.head->coef, L2.head->expn);
			L2.head = L2.head->next;
		}
		else {
			AddNode(&result, L1.head->coef + L2.head->coef, L2.head->expn);
			L1.head = L1.head->next;
			L2.head = L2.head->next;
		}
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L1.head->coef, L1.head->expn);
		L1.head = L1.head->next;
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L2.head->coef, L2.head->expn);
		L2.head = L2.head->next;
	}
	return result;
}

//���� L1-L2
LinkList SubPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	LinkList result;
	InitList(result);
	while (L1.head->next != NULL || L2.head->next != NULL) {
		if (L1.head->expn > L2.head->expn) {
			AddNode(&result, L1.head->coef, L1.head->expn);
			L1.head = L1.head->next;
		}
		else if (L1.head->expn < L2.head->expn) {
			AddNode(&result, L2.head->coef*-1, L2.head->expn);
			L2.head = L2.head->next;
		}
		else {
			if (L1.head->coef - L2.head->coef != 0) {
				AddNode(&result, L1.head->coef - L2.head->coef, L2.head->expn);
			}
			L1.head = L1.head->next;
			L2.head = L2.head->next;
		}
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L1.head->coef, L1.head->expn);
		L1.head = L1.head->next;
	}
	while (L1.head->next != NULL) {
		AddNode(&result, L2.head->coef*-1, L2.head->expn);
		L2.head = L2.head->next;
	}
	return result;
}

//�˷�
LinkList MultiplyPolyn(LinkList L1, LinkList L2) {
	LinkListBubbleSort(L1);
	LinkListBubbleSort(L2);
	Link* index;
	LinkList result;
	InitList(result);
	while (L1.head->next != NULL)
	{
		index = L2.head;
		while (index->next != NULL) {
			if (L1.head->coef != 0 && index->coef != 0)
				AddNode(&result, L1.head->coef* index->coef, L1.head->expn + index->expn);
			index = index->next;
		}
		L1.head = L1.head->next;
	}
	return result;
}

//��
LinkList Derivation(LinkList L) {
	LinkList result;
	InitList(result);
	while (L.head->next != NULL)
	{
		if (L.head->expn != 0)
			AddNode(&result, L.head->coef*L.head->expn, L.head->expn - 1);
		L.head = L.head->next;
	}
	return result;
}

