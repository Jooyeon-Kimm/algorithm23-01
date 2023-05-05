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
    // ������ ���� n
    int n;
    cin >> n;


    vector<char> codes(n);  // ��
    vector<int> freqs(n);
    PriorityQueue PQ;

    // �Է¹ޱ�
    for (int i = 0; i < n; i++) {
        cin >> codes[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> freqs[i];
    }


    // t1: ���ĺ�(�빮��,�ҹ���) ���ڿ� ����
    // t2: ���̳ʸ� ���� ���ڿ� ����
    int t1, t2;

    // s1: ���ĺ� ���ڿ� (�빮��, �ҹ���)
    // s2: ���̳ʸ� ���ڿ� (0/1)

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

    // ��º�
    // ��ȸ
    node_ptr root = huffman(n, codes, freqs, PQ);
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
    
    // ���ڵ�
    map<char, string> encoder;
    encode(root, "", encoder);

    for (int i = 0; i < s1.size(); i++) {
        string encoded = "";
        for (int k = 0; k < s1[i].length(); k++) {
            encoded += encoder[s1[i][k]];
        }
        cout << encoded << endl;
    }
    
    // ���ڵ�
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
������ Ʈ���� ���� ��尡 �ƴ� internal ���鿡�� 
�ɺ������� '+' ���ڸ� �Է��� �ε��� �Ѵ�.
������ Ʈ���� ������ٸ�, 
���ڿ��� ������ �ڵ�� ���ڵ�, ���ڵ��ϴ� �˰����� �����Ͻÿ�.


Input
ù° �ٿ� ������ ���� n�� �־�����.
��° �ٿ� n���� ���ڰ� �־�����.
���ڴ� ���ĺ� �빮��, �Ǵ� �ҹ��ڷθ� �Էµȴٰ� �����Ѵ�.
��° �ٿ� n���� �󵵰��� �־�����.
�󵵰��� ��� ���� ������� �����Ѵ�.
���� �ٿ� ���ڿ��� ���� T1�� �־�����.
���� T1���� �ٿ� �� �ٿ� �ϳ��� �ؽ�Ʈ ���ڿ��� �־�����.
���� �ٿ� ���ڿ��� ���� T2�� �־�����.
���� T2���� �ٿ� �� �ٿ� �ϳ��� ������ �ڵ� ���ڿ��� �־�����.


Output
ù° �ٿ� ������ Ʈ���� preorder traversal ����� ����. 
(��� ������ �Ʒ� ��� ��ʸ� �����Ѵ�. 
���������� �ٳ� ������ ������ �����Ѵ�.)

��° �ٿ� ������ Ʈ���� inorder traversal ����� ����.
(��� ������ �Ʒ� ��� ��ʸ� �����Ѵ�.
���������� �ٳ� ������ ������ �����Ѵ�.)

��° �� ���ķ� T1���� ���ڿ��� ���ڵ��� ������ �ڵ带 
�� �ٿ� �ϳ��� ����Ѵ�. (�ٳ� ������ ����.)

���ķ� T2���� ������ �ڵ带 ���ڵ��� �ؽ�Ʈ ���ڿ��� 
�� �ٿ� �ϳ��� ����Ѵ�. (�ٳ� ������ ����.)
*/