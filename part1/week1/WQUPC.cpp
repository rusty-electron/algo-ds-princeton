#include <iostream>
#include <vector>

class WQUPC{
    private:
    std::vector<int> id;
    std::vector<int> weight;

    public:
    // WQUPC -> weighted quick union with path compression
    // time complexity: lg*N
    WQUPC(int size) {
        // initialize the id array
        for(int i=0; i<size; i++){
            id.push_back(i);
        }

        // initialize the weight array with zeros
        for(int i=0; i<size; i++){
            weight.push_back(0);
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
        if (weight[qid] > weight[pid]){
            // connect the larger tree to the root
            // of the smaller tree and increase its weight
            // by 1, reset the weight of the other tree
            id[pid] = qid;
            weight[qid] += weight[pid];
            weight[pid] = 0;
        } else if (weight[qid] < weight[pid]){
            // same as the last case
            id[qid] = pid;
            weight[pid] += weight[qid];
            weight[qid] = 0;
        } else {
            // when both trees are of same size
            // connect the second tree to the root
            // of the first tree and increase its weight
            // by 1, reset the weight of the other tree
            weight[pid]+=1;
            id[qid] = pid;
            weight[qid] = 0;
        }
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
    qu.union_op(8, 3);
    std::cout << qu.connected(4, 5) << std::endl;
    std::cout << qu.connected(9, 5) << std::endl;
    std::cout << qu.connected(8, 5) << std::endl;

    qu.display();
}
