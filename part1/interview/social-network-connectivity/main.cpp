#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>

class WQUPC{
    private:
    std::vector<int> id;
    std::vector<int> weight;
    std::vector<int> length;

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

        // initialize the length array to keep track of sizes
        for(int i=0; i<size; i++){
            length.push_back(1);
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

        if (pid == qid) {
            return;
        }
        if (weight[qid] > weight[pid]){
            // connect the larger tree to the root
            // of the smaller tree and increase its weight
            // by 1, reset the weight of the other tree
            id[pid] = qid;
            weight[qid] += weight[pid];
            weight[pid] = 0;
            length[qid] += length[pid];
        } else if (weight[qid] < weight[pid]){
            // same as the last case
            id[qid] = pid;
            weight[pid] += weight[qid];
            weight[qid] = 0;
            length[pid] += length[qid];
        } else {
            // when both trees are of same size
            // connect the second tree to the root
            // of the first tree and increase its weight
            // by 1, reset the weight of the other tree
            weight[pid]+=1;
            id[qid] = pid;
            weight[qid] = 0;
            length[pid] += length[qid];
        }
    }

    int get_length(int val) {
        return length[val];
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

        std::cout << "L: ";
        for(int i=0; i<length.size(); i++) {
            std::cout << length[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::ifstream inFile("lines.txt");
    int size = 10;
    WQUPC qu = WQUPC(10);
    // qu.display();

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)){
            std::stringstream ss(line);

            std::string a, b, date_str, time_str;
            std::getline(ss, a, ' ');
            std::getline(ss, b, ' ');
            std::getline(ss, date_str, ' ');
            std::getline(ss, time_str, ' ');

            int a_val = atoi(a.c_str());
            int b_val = atoi(b.c_str());

            // connect
            qu.union_op(a_val, b_val);

            if (qu.get_length(qu.root(a_val)) == size) {
                std::cout << "all nodes connected at " << date_str << " " << time_str << std::endl;
                break;
            }
        }
    }
    // qu.display();
}
