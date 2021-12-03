class eff_union:
    def __init__(self, size):
        self.size = size
        self.id = list(range(size))
        self.weights = [0] * size

    def root(self, val):
        while self.id[val] != val:
            self.id[val] = self.id[self.id[val]]
            val = self.id[val]
        return val

    def connected(self, p, q):
        return self.root(p) == self.root(q)

    def union_op(self, p, q):
        qid = self.root(q)
        pid = self.root(p)
        if self.weights[qid] > self.weights[pid]:
            self.id[pid] = qid
            self.weights[qid] += self.weights[pid]
            # self.weights[pid] = 0
        elif self.weights[qid] < self.weights[pid]:
            self.id[qid] = pid
            self.weights[pid] += self.weights[qid]
            # self.weights[qid] = 0
        else:
            self.weights[pid]+=1
            self.id[qid] = pid
            self.weights[qid] = 0

    def __str__(self):
        return f"I:{list(range(self.size))}\nC:{self.id}\nW:{self.weights}"

if __name__ == "__main__":
    qu = eff_union(10)
    qu.union_op(1,5)
    qu.union_op(2,5)
    qu.union_op(3,5)

    qu.union_op(7,8)
    assert qu.connected(1, 8) == False

    qu.union_op(7,2)
    assert qu.connected(8, 1) == True

    print(qu)
