#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include<map>
#include <array>

#define cons 97
#define alphabet 26
#define one 1
const char a = 'a';


std::unordered_map<int, std::vector<int>> answer;
struct Node {
    bool term = false;
    std::map<char, Node*> next;
    std::vector<int> word;
    int word_size = 0;
    Node *suf = nullptr;
    std::array<Node*, alphabet> go;
};
Node root;
class Carp {
public:
    Node *insert(Node *v, const std::string &s, int i, int ID) {
        if (v == nullptr) {
            v = new Node();
        }
        if (i == s.size()) {
            v->word.push_back(ID);
            v->word_size = static_cast<int>(s.size());
            v->term = true;
            return v;
        }
        char cnt = s[i];
        v->next[cnt] = insert(v->next[cnt], s, i + one, ID);
        return v;
    }
    static void build() {
        root.suf = &root;
        std::queue<Node*> vec;
        vec.push(&root);
        while (!vec.empty()) {
            auto now = vec.front();
            vec.pop();
            for (auto &elem: now->next) {
                vec.push(elem.second);
                elem.second->suf = ((now == &root) ? &root : now->suf->go[elem.first - cons]);
            }
            for (char c = a; c < a + alphabet; ++c) {
                if (now->next.find(c) != now->next.end()) {
                    now->go[c - cons] = now->next[c];
                } else {
                    now->go[c - cons] = (now == &root ? &root : now->suf->go[c - cons]);
                }
            }
            if (!now->word_size) {
                now->word_size = now->suf->word_size;
            }
            if (!now->suf->word_size) {
                now->suf->word_size = now->word_size;
            }
        }
    }
    static void count(const std::string& str) {
        auto now = &root;
        for (int i = one - 1; i < str.size(); ++i) {
            now = now->go[str[i] - cons];
            Node* temp = now;
            while (temp != &root) {
                if (temp->term) {
                    for (auto e : temp->word) {
                        answer[e].push_back(i + one + one - temp->word_size);
                    }
                }
                temp = temp->suf;
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string str;
    std::cin >> str;
    int cnt;
    Carp Trie;
    std::cin >> cnt;
    for (int i = one; i <= cnt; ++i) {
        std::string word;
        std::cin >> word;
        Trie.insert(&root, word, one - 1, i);
    }
    Carp::build();
    Carp::count(str);
    for (int i = one; i <= cnt; ++i) {
        std::cout << answer[i].size()<< " ";
        for (const auto &el :answer[i]) {
            std::cout << el << " ";
        }
        std::cout << "\n";
    }
    return one - 1;
}
