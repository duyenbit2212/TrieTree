#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;
const int Alphabet_size = 26;

struct Voca {
	string Key;
	string Mean;
};

struct Node {
	Node* Children[Alphabet_size];
	bool isEndOfWord;
	string sMean;
};

Node* getNode(void) {
	Node* pNode = new Node;
	pNode->isEndOfWord = false;
	for (int i = 0; i<Alphabet_size; i++) {
		pNode->Children[i] = NULL;
	}
	return pNode;
}

void insert(Node* root, Voca key) {
	Node* pTmp = root;
	for (int i = 0; i<key.Key.length(); i++) {
		int index = key.Key[i] - 'a';
		if (!pTmp->Children[index]) {
			pTmp->Children[index] = getNode();
		}
		pTmp = pTmp->Children[index];
	}
	pTmp->sMean = key.Mean;
	pTmp->isEndOfWord = true;
}

bool search(Node* root, string key) {
	Node* pTmp = root;
	for (int i = 0; i<key.length(); i++) {
		int index = key[i] - 'a';
		if (!pTmp->Children[index])
			return false;
		pTmp = pTmp->Children[index];
	}
	if (pTmp != NULL && pTmp->isEndOfWord == true)
		cout << pTmp->sMean << " ";
	return (pTmp != NULL && pTmp->isEndOfWord == true);
}

bool Delete(Node* root, string key) {
	Node* pTmp = root;
	for (int i = 0; i<key.length(); i++) {
		int index = key[i] - 'a';
		if (!pTmp->Children[index])
			return false;
		pTmp = pTmp->Children[index];
	}
	pTmp->isEndOfWord = false;
	return true;
}

void TachTu(Voca &Word, string key) {
	int k=0;
	int l = 0;
	for (int i = 0; i<key.length(); i++) {
		if (key[i] == ':') {
			k = i;
			break;
		}
		Word.Key.push_back(key[i]);

	}
	for (int i = k + 2; i<key.length(); i++) {
		Word.Mean.push_back(key[i]);
	}
}

int main() {
	ifstream file_input("Dictionary.txt");
	Node* root = getNode();
	int c = 0;
	while (!file_input.eof())
	{
		char temp[255];
		file_input.getline(temp, 255);
		string line = temp;
		Voca k;
		TachTu(k, line);
		insert(root, k);
	}
	while (1) {
		cout << "\n\t\t DICTIONARY\n";
		cout << "1. Tra tu\n";
		cout << "2. Them tu\n";
		cout << "3. Xoa tu\n";
		cout << "4. Thoat\n";
		cout << "Nhap lua chon: ";
		int choose;
		cin >> choose;
		if (choose == 4) break;
		if (choose == 1) {
			string c;
			cin.ignore();
			getline(cin, c);
			search(root, c) ? cout << " Yes\n" : cout << " No\n";
		}
		if (choose == 2) {
			Voca b;
			cin.ignore();
			getline(cin, b.Key);
			if (!search(root, b.Key)) {
				getline(cin, b.Mean);
				insert(root, b);
			}
			else cout << "Tu da co";
		}
		if (choose == 3) {
			string a;
			cin.ignore();
			getline(cin, a);
			Delete(root, a) ? cout << "da xoa\n" : cout << "khong tim thay\n";
		}
	}

}
