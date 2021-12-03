#include <iostream>
#include <vector>

class QuickUnion {
    private:
    std::vector<int> id;

    public:
    QuickUnion(int size){
        for(int i=0; i<size; i++){
            id.push_back(i);
        }
    }

    int root(int val){
        while (val != id[val]) {
            val = id[val];
        }
        return val;
    }

    bool connected(int p, int q){
        return root(p) == root(q);
    }

    void union_op(int p, int q) {
        int p_root = root(p);
        int q_root = root(q);
        id[p_root] = q_root;
    }

    void display() {
        for(int i=0; i<id.size(); i++) {
            std::cout << id[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    QuickUnion qu = QuickUnion(10);
    qu.display();

    qu.union_op(5, 1);
    qu.union_op(4, 1);
    std::cout << qu.connected(4, 5) << std::endl;
    std::cout << qu.connected(9, 5) << std::endl;
}

