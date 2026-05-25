#include <iostream>
#include <vector>

class UF {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    UF(int n){
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int p){
        if (parent[p] != p)
            parent[p] = find(parent[p]);
        return parent[p];
    }
    void unite(int p, int q){
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;
        if (size[rootP] < size[rootQ]){
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        else {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }
    bool connected(int p, int q){
        return find(p) == find(q);
    }
};
class Percolation{
private:
    int n; 
    std::vector<bool> open_el;
    UF uf;
    int count_open;
    const int TOP_VIRTUAL;
    const int BOTTOM_VIRTUAL;

    int index(int row, int col) { return row * n + col; }
public:
    Percolation(int n): n(n), open_el(n * n, false), uf(n * n + 2),
                        count_open(0), TOP_VIRTUAL(n * n), BOTTOM_VIRTUAL(n * n + 1)
                        {}
    void open(int row, int col){
        int idx = index(row, col);
        if (open_el[idx]) return;
        open_el[idx] = true;
        ++count_open;
        if (row == 0) uf.unite(idx, TOP_VIRTUAL);
        if (row == n - 1) uf.unite(idx, BOTTOM_VIRTUAL);

        if (row > 0 && open_el[index(row - 1, col)]) uf.unite(idx, index(row - 1, col));
        if (row < n - 1 && open_el[index(row + 1, col)]) uf.unite(idx, index(row + 1, col));

        if (col > 0 && open_el[index(row, col - 1)]) uf.unite(idx, index(row, col - 1));
        if (col < n - 1 && open_el[index(row, col + 1)]) uf.unite(idx, index(row, col + 1));
    }
    bool is_percolated(){
        return uf.connected(TOP_VIRTUAL, BOTTOM_VIRTUAL);
    }
    int number_of_open_cells(){
        return count_open;
    }
};

class PercolationStats
{
private:
    
public:
    /**
     * Construct a new Percolation Stats object
     * @param dimension dimension of percolation grid
     * @param trials amount of experiments
     */
    PercolationStats(std::size_t dimension, std::size_t trials);

    /**
     * Returns mean of percolation threshold (x¯ from description)
     */
    double get_mean() const;

    /**
     * Returns standard deviation of percolation threshold (s from description)
     */
    double get_standard_deviation() const;

    /**
     * Returns log edge of condidence interval
     */
    double get_confidence_low() const;

    /**
     * Returns high edge of confidence interval
     */
    double get_confidence_high() const;

    /**
     * Makes all experiments, calculates statistic values
     */
    void execute();
};
int main(){
    return 0;
}