# include "stdio.h"
# include "malloc.h"
# include "string.h"

typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;

typedef char * * HuffmanCode;

// typedef int * Weight;

void Select(HuffmanTree	HT, int end, int *s) {
	s[0] = -1;
	s[1] = -1;
	if (end < 0) {
		return;
	}
	if (end == 0) {
		s[0] = 1;
		s[1] = 1;
		return;
	}
	int k;
	for (k = 0; k < end; k++) {
		if (HT[k].parent != 0) {
			continue;
		}
		if (s[0] < 0) {
			s[0] = k;
		}
		if (s[1] < 0) {
			s[1] = k;
		}
		if (HT[k].weight < HT[s[1]].weight) {
			s[1] = k;
		} else if (HT[k].weight < HT[s[0]].weight) {
			s[0] = k;
		} else if (s[0] == s[1] && s[1] != (end -1) && k == (end - 1)) {
			// ���һ���ڵ�
			s[1] = end -1;
		}
	}
	// �õ�������Сֵ����ȨֵС�ķ������
	if (HT[s[0]].weight > HT[s[1]].weight) {
		int a = s[0];
		s[0] = s[1];
		s[1]= a;
	}
}

HuffmanTree initHuffmanTree(int *w, int n) {
	if (n <= 1) {
		return 0;
	}
	int m = 2 * n - 1, i; // �ڵ���
	HuffmanTree HT = (HuffmanTree) malloc(m * sizeof(HTNode));
	
	HuffmanTree p;
	// ��ʼ��Huffman����Ҷ�ӽڵ� 
	for (p = HT, i = 0; i < n; ++i, ++p) {
		// ֻ��ʹ�� ��-> ����ֵ��ѯ������ʹ�õ����  ��.��ȡֵ���ǽڵ�ʵ�����ڵ�ָ�룩 
		p->weight = w[i];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	// ��ʼ��Huffman���ķ�֧�ڵ�
	for (; i < m; ++i, ++p) {
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	
	// ����Huffman��
	int s[2];
	for (i = n; i < m; i++) {
		// ȡ����ǰHuffman����Ȩ����С�Ľڵ� 
		Select(HT, i, s);
		HT[s[0]].parent = i;
		HT[s[1]].parent = i;
		HT[i].lchild =  s[0];
		HT[i].rchild = s[1];
		HT[i].weight = HT[s[0]].weight + HT[s[1]].weight;
	}
	return HT;
}

HuffmanCode HuffmanCoding(HuffmanTree HT, int n) {
	if (n <= 1) {
		return 0;
	}
	// ����n���ַ������ͷָ������ 
	HuffmanCode HC = (HuffmanCode) malloc((n) * sizeof(char *));
	char *cd = (char *) malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int i, start, c, f;
	for (i = 0; i< n; i++) {
		start = n - 1;
		// ��Ҷ�ӽڵ���������� 
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			// c �����ӣ�����Ϊ 0 
			if (HT[f].lchild == c) {
				cd[--start] = '0'; 
			} else {
				cd[--start] = '1';
			}
		}
		// ��ǰҶ�ڵ�ı���ռ� 
		HC[i] = (char *) malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	return HC;
}

int main() {
	HuffmanTree HT; // ָ��һ�� HTNode �ڵ� 
	HuffmanCode HC; // ָ��һ�� char *s ���� ��s ���Ӧһ�������ַ��������Ȳ��̶��� 
	int w[4] = {
		7, 5, 2, 4
	};
	int n = sizeof(w) / sizeof(int);
	if (n <= 1) {
		return 0;
	}
	HT = initHuffmanTree(w, n);
	HC = HuffmanCoding(HT, n);
	int i;
	for (i = 0; i < n; i++) {
		printf("%c: %d, %s\n", 'a' + i, HT[i].weight, HC[i]);
	}
}
