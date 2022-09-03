#include<iostream>
#include<vector>
#include<tuple>
#include<limits.h>
using namespace std;
class tree {

public:
	int data;
	char pre;
	char now;

	tree() {
		pre = NULL;
		now = NULL;
		data = INT_MAX;
	}
};

void min_heapify(tree* arr[], int numb, int arra_size) {
	int smallest;
	int l = (numb + 1) * 2;
	int r = (numb + 1) * 2 + 1;
	if (l <= arra_size && arr[l - 1]->data < arr[numb]->data) smallest = l;
	else smallest = numb + 1;
	if (r <= arra_size && arr[r - 1]->data < arr[smallest - 1]->data) smallest = r;
	if (smallest != numb + 1) {
		tree* temp = arr[numb];
		arr[numb] = arr[smallest - 1];
		arr[smallest - 1] = temp;
		min_heapify(arr, smallest - 1, arra_size);
	}
}


void build_min_heap(tree* arr[], int arra_size) {
	for (int i = arra_size / 2 - 1; i >= 0; i--) {
		min_heapify(arr, i, arra_size);
	}
}


class min_priority_queue {
public:
	tree** arra;
	int arra_size;

	min_priority_queue(vector<char> v,int num) {
		arra = (tree**)malloc(sizeof(tree*) * num);
		arra_size = num;
		for (int i = 0; i < num; i++) {
			arra[i] = (tree*)malloc(sizeof(tree));
			arra[i]->pre = NULL;
			if (i == 0) arra[0]->data = 0;
			else arra[i]->data = INT_MAX;
			arra[i]->now = v[i];
		}
		build_min_heap(arra, arra_size);
	}

	tree* extract_min() {
		if (arra_size < 1) cout << "heap underflow\n";
		tree* min = arra[0];
		arra[0] = arra[arra_size - 1];
		arra_size--;
		min_heapify(arra, 0, arra_size);
		return min;
	}

	tree* find(char ano) {
		for (int i = 0; i < arra_size; i++) {
			if (arra[i]->now == ano) return arra[i];
			if (i == arra_size - 1) return NULL;
		}
	}
	void decrease_key(tree* arr,int key) {
		if (key > arr->data) {
			cout << "error"; return;
		}
		int temp;
		arr->data = key;
		for (int i = 0; i < arra_size; i++) {
			if (arr->now == arra[i]->now) {
				temp = i;
				break;
			}
		}

		while (temp > 0 && arra[(temp + 1) / 2 - 1]->data > arra[temp]->data) {
			tree* temp_2 = arra[(temp + 1) / 2 - 1];
			arra[(temp + 1) / 2 - 1] = arra[temp];
			arra[temp] = temp_2;
			temp = (temp + 1) / 2 - 1;
		}
	}
};

int relax(tree* u, tree* v, int weig) {
	if (v->data > u->data + weig) {
		v->pre = u->now;
		int key = u->data + weig;
		return key;
	}
	else return -1;
}

void dijkstra(vector<char> v, vector<vector<tuple<char, int>>> vec) {
	min_priority_queue qu(v, v.size());
	vector<tree*> s;
	while (s.size() != v.size()) {
		tree* u = qu.extract_min();
		s.push_back(u);
		if (s.size() == v.size()) break;
		for (auto tup : vec[u->now - 'A']) {
			char ano = get<0>(tup);
			int weig = get<1>(tup);
			tree* anotree=qu.find(ano);
			if (anotree == NULL) continue;
			int key=relax(u, anotree, weig);
			if(key!=-1) qu.decrease_key(anotree, key);
		}
	}

	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s.size(); j++) {
			if (v[i] == s[j]->now) {
				cout << s[j]->data<<"\n";
			}
		}
	}
}

int main() {
	
	string str;
	vector<char> v;
	cin >> str;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ',') v.push_back(str[i]);
	}
	
	int num;
	cin >> num;
	vector<vector<tuple<char, int>>> vec(v.size());

	for (int i = 0; i < num; i++) {
		char a, com, b;
		int wei;
		cin >> a >> com >> b >> com >> wei;
		vec[a - 'A'].push_back(make_tuple(b, wei));
	}

	dijkstra(v,vec);

}
