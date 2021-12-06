#include <iostream>
#include <vector>

class WQUPC{
    private:
    std::vector<int> id;
    std::vector<int> weight;
    std::vector<int> max_val;

    public:
    // WQUPC -> weighted quick union with path compression
    // time complexity: lg*N
    WQUPC(int size) {
        // initialize the arrays
        for(int i=0; i<size; i++){
            id.push_back(i);
            weight.push_back(0);
            max_val.push_back(i);
        }
    }

    int root(int val) {
        while(id[val] != val){
            id[val] = id[id[val]]; // path compression
            val = id[val];
        }
        return val;
    }

    bool connected(int p, int q){
        return root(p) == root(q);
    }

    void union_op(int p, int q){
        int qid = root(q);
        int pid = root(p);
        int small_tree, big_tree, weight_val;

        if (qid == pid) return;

        if (weight[pid] >= weight[qid]){
            small_tree = qid;
            big_tree = pid;
        } else {
            small_tree = pid;
            big_tree = qid;
        }

        id[small_tree] = big_tree;

        if (weight[small_tree] == weight[big_tree]){
            weight_val = 1;
        } else { weight_val = weight[small_tree]; }

        weight[big_tree] += weight_val;
        weight[small_tree] = 0; 

        // for updating the max values array
        int max_in_small = max_val[small_tree];
        int max_in_big = max_val[big_tree];

        if (max_in_small > max_in_big) {
            max_val[big_tree] = max_in_small;
        }
    }

    int find(int val) {
        return max_val[root(val)];
    }

    void display() {
        std::cout << "I: ";
        for(int i=0; i<id.size(); i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << "C: ";
        for(int i=0; i<id.size(); i++) {
            std::cout << id[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "W: ";
        for(int i=0; i<weight.size(); i++) {
            std::cout << weight[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "M: ";
        for(int i=0; i<max_val.size(); i++) {
            std::cout << max_val[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    WQUPC qu = WQUPC(10);
    qu.display();

    // first tree (big)
    qu.union_op(5, 3);
    qu.union_op(4, 5);
    qu.union_op(3, 2);

    // second tree (small)
    qu.union_op(1, 7);
    qu.union_op(8, 7);

    // connect both trees
    // qu.union_op(8, 3);
    // qu.union_op(9, 3);

    std::cout << qu.connected(4, 5) << std::endl;
    std::cout << qu.connected(9, 5) << std::endl;
    std::cout << qu.connected(8, 5) << std::endl;

    std::cout << qu.find(1) << std::endl;

    qu.display();
}
