#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <cstdint>

using Matrix = std::vector<std::vector<int>>;

auto matrixChainOrder(const std::vector<int>& p) 
{
    int n = p.size();

    Matrix m{};
    m.resize(n);
    for(int i = 0; i < n; i++) 
    {
        m[i].resize(n);
    }

    Matrix s{};
    s.resize(n - 1);
    for(int i = 0; i < n - 1; i++) 
    {
        s[i].resize(n);
    }

    for (int i = 0; i < n; i++) 
    {
        m[i][i] = 0;
    }

    for(int l = 2; l < n; l++) 
    {
        for(int i = 1; i < n - l + 1; i++)
        {
            int j = i + l - 1;
            // m[i][j] = std::numeric_limits<int>::max();
            m[i][j] = 0;
            m[i][j] = ~m[i][j];
            m[i][j] = (unsigned int)m[i][j] >> 1;
            for(int k = i; k <= j - 1; k++)
            {
                int q = 
                    m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) 
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    return std::make_pair(m, s);
}

void printOptimalParens(Matrix s, int i, int j)
{
    if(i == j)
    {
        std::cout << "A" << i;
    }
    else
    {
        std::cout << "(";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        std::cout << ")";
    }
}

int main() 
{
    std::vector<int> shapes {5, 10, 3, 12, 5, 50, 6};

    auto [m, s] = matrixChainOrder(shapes);

    for(std::size_t i = 0; i < m.size(); i++)
    {
        for(std::size_t j = 0; j < m[i].size(); j++)
        {
            std::cout << std::setw(10) << m[i][j] << ' ';
        }
        std::cout << '\n';
    }

    for(std::size_t i = 0; i < s.size(); i++)
    {
        for(std::size_t j = 0; j < s[i].size(); j++)
        {
            std::cout << s[i][j] << ' ';
        }
        std::cout << '\n';
    }

    printOptimalParens(s, 1, 6);

    return 0;
}
