#include <iostream>
#include <vector>

class QuickFindUF {
    private:
    std::vector<int> id;

    public:
    QuickFindUF(int N){
        for(int i=0; i<N; i++){
            id.push_back(i);
        }
    }

    bool connected(int p, int q){
        return id[p] == id[q];
    }

    void union_op(int p, int q){
        int pid = id[p];
        int qid = id[q];

        for(int i=0; i<id.size(); i++){
            if (id[i] == pid) {
                id[i] = qid;
            }
        }
    }

    void display(){
        for(int i=0; i<id.size(); i++){
            std::cout << id[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    QuickFindUF union_ds = QuickFindUF(5);
    union_ds.display();
    union_ds.union_op(1, 4);
    std::cout << union_ds.connected(1, 4) << std::endl;
    union_ds.display();
}