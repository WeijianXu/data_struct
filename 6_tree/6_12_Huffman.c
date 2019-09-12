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
			// 最后一个节点
			s[1] = end -1;
		}
	}
	// 得到两个最小值，让权值小的放在左边
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
	int m = 2 * n - 1, i; // 节点数
	HuffmanTree HT = (HuffmanTree) malloc(m * sizeof(HTNode));
	
	HuffmanTree p;
	// 初始化Huffman树的叶子节点 
	for (p = HT, i = 0; i < n; ++i, ++p) {
		// 只能使用 “-> ”按值查询，不能使用点符号  “.”取值（非节点实例，节点指针） 
		p->weight = w[i];
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	// 初始化Huffman树的分支节点
	for (; i < m; ++i, ++p) {
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	
	// 建立Huffman树
	int s[2];
	for (i = n; i < m; i++) {
		// 取到当前Huffman树中权重最小的节点 
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
	// 分配n个字符编码的头指针向量 
	HuffmanCode HC = (HuffmanCode) malloc((n) * sizeof(char *));
	char *cd = (char *) malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int i, start, c, f;
	for (i = 0; i< n; i++) {
		start = n - 1;
		// 丛叶子节点逆向求编码 
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			// c 是左孩子，编码为 0 
			if (HT[f].lchild == c) {
				cd[--start] = '0'; 
			} else {
				cd[--start] = '1';
			}
		}
		// 当前叶节点的编码空间 
		HC[i] = (char *) malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	return HC;
}

int Huffman(int *w, int n) {
	HuffmanTree HT; // 指向一组 HTNode 节点 
	HuffmanCode HC; // 指向一组 char *s 编码 ，s 则对应一个编码字符串（长度不固定） 
	// int n = sizeof(w) / sizeof(int);
	if (n <= 1) {
		return 0;
	}
	HT = initHuffmanTree(w, n);
	HC = HuffmanCoding(HT, n);
	int i;
	for (i = 0; i < n; i++) {
		printf("%c: %d, %s\n", 'a' + i, HT[i].weight, HC[i]);
	}
	return 0;
}

int main() {
	int n;
	scanf("%d", &n);
	if (n <= 1) {
		return 0;
	}
	// Huffman 树至少2个叶子节点，一个无法构成Huffman树； 
	int w[n], i;
	for (i = 0; i < n; i++) {
		scanf("%d", &w[i]);
	}
	Huffman(w, n);
	return 0;
}
