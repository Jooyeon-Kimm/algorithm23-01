#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

typedef struct node* node_ptr;
typedef struct node {
    char symbol; // the value of a character.
    int frequency; // the number of times the character is in the file.
    node_ptr left;
    node_ptr right;
} node_t;

node_ptr create_node(char symbol, int frequency, node_ptr left, node_ptr right) {
    node_ptr node = new node_t();
    node->symbol = symbol;
    node->frequency = frequency;
    node->left = left;
    node->right = right;
    return node;
}

struct compare {
    bool operator()(node_ptr p, node_ptr q) {
        return p->frequency > q->frequency;
    }
};
typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;

void preorder(node_ptr root) {
    if (root == NULL) return;
    cout << root->symbol << ":" << root->frequency << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node_ptr root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->symbol << ":" << root->frequency << " ";
    inorder(root->right);
}


node_ptr huffman(int n, vector<char> codes, vector<int> freqs, PriorityQueue& PQ)
{
    for (int i = 0; i < n; i++)
        PQ.push(create_node(codes[i], freqs[i], nullptr, nullptr));

    for (int i = 0; i < n - 1; i++) {
        node_ptr p = PQ.top(); PQ.pop();
        node_ptr q = PQ.top(); PQ.pop();
        node_ptr r = create_node('+', p->frequency + q->frequency, nullptr, nullptr);
        r->left = p;
        r->right = q;
        PQ.push(r);
    }
    return PQ.top();
}


void encode(node_ptr node, string code, map<char, string>& encoder) {
    if (node->symbol != '+') { // leaf node
        encoder[node->symbol] = code;
    }
    else { // internal node
        encode(node->left, code + "0", encoder);
        encode(node->right, code + "1", encoder);
    }
}

void decode(node_ptr root, node_ptr node, string s, int i) {
    if (i <= s.length()) {
        if (node->symbol != '+') { // leaf node
            cout << node->symbol;
            decode(root, root, s, i);
        }
        else { // internal node
            if (s[i] == '0')
                decode(root, node->left, s, i + 1);
            else
                decode(root, node->right, s, i + 1);
        }
    }
}

int main() {
    // 문자의 개수 n
    int n;
    cin >> n;


    vector<char> codes(n);  // 알
    vector<int> freqs(n);
    PriorityQueue PQ;

    // 입력받기
    for (int i = 0; i < n; i++) {
        cin >> codes[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> freqs[i];
    }


    // t1: 알파벳(대문자,소문자) 문자열 개수
    // t2: 바이너리 숫자 문자열 개수
    int t1, t2;

    // s1: 알파벳 문자열 (대문자, 소문자)
    // s2: 바이너리 문자열 (0/1)

    cin >> t1;
    vector<string> s1(t1);
    for (int i = 0; i < t1; i++) {
        cin >> s1[i];
    }

    cin >> t2;
    vector<string> s2(t2);
    for (int i = 0; i < t2; i++) {
        cin >> s2[i];
    }

    // 출력부
    // 순회
    node_ptr root = huffman(n, codes, freqs, PQ);
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    
    // 인코딩
    map<char, string> encoder;
    encode(root, "", encoder);

    for (int i = 0; i < s1.size(); i++) {
        string encoded = "";
        for (int k = 0; k < s1[i].length(); k++) {
            encoded += encoder[s1[i][k]];
        }
        cout << encoded << endl;
    }
    
    // 디코딩
    string decoded = "";
    for (int i = 0; i < s2.size(); i++) {
        decoded = s2[i];
        decode(root, root, decoded, 0);
        if (i < s2.size() - 1) {
            cout << endl;
        }
    }

    return 0;
}

/*
Sample Input 1 
6
b e c a d f
5 10 12 16 17 25
5
cab
dec
fad
becadf
fdaceb
5
110001110
011111110
100001
11101111110000110
10010011011111110

Sample Output 1
+:85 +:33 a:16 d:17 +:52 f:25 +:27 c:12 +:15 b:5 e:10
a:16 +:33 d:17 +:85 f:25 +:52 c:12 +:27 b:5 +:15 e:10
110001110
011111110
100001
11101111110000110
10010011011111110
cab
dec
fad
becadf
fdaceb


Description
허프만 트리의 리프 노드가 아닌 internal 노드들에는 
심볼값으로 '+' 문자를 입력해 두도록 한다.
허프만 트리를 만들었다면, 
문자열을 허프만 코드로 인코딩, 디코딩하는 알고리즘을 구현하시오.


Input
첫째 줄에 문자의 개수 n이 주어진다.
둘째 줄에 n개의 문자가 주어진다.
문자는 알파벳 대문자, 또는 소문자로만 입력된다고 가정한다.
셋째 줄에 n개의 빈도값이 주어진다.
빈도값은 모두 양의 정수라고 가정한다.
다음 줄에 문자열의 개수 T1이 주어진다.
이후 T1개의 줄에 한 줄에 하나씩 텍스트 문자열이 주어진다.
다음 줄에 문자열의 개수 T2가 주어진다.
이후 T2개의 줄에 한 줄에 하나씩 허프만 코드 문자열이 주어진다.


Output
첫째 줄에 허프만 트리의 preorder traversal 결과를 쓴다. 
(출력 포맷은 아래 출력 사례를 참조한다. 
예외적으로 줄끝 공백이 있음에 주의한다.)

둘째 줄에 허프만 트리의 inorder traversal 결과를 쓴다.
(출력 포맷은 아래 출력 사례를 참조한다.
예외적으로 줄끝 공백이 있음에 주의한다.)

셋째 줄 이후로 T1개의 문자열을 인코딩한 허프만 코드를 
한 줄에 하나씩 출력한다. (줄끝 공백이 없다.)

이후로 T2개의 허프만 코드를 디코딩한 텍스트 문자열을 
한 줄에 하나씩 출력한다. (줄끝 공백이 없다.)
*/