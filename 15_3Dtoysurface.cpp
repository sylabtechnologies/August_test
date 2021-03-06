// 15_3Dtoysurface.cpp
// https://www.hackerrank.com/challenges/3d-surface-area/problem

int surfaceArea(vector<vector<int>> A)
{
    
    auto stack_area = [](int h)->int {int ans = 6; if (h > 1) ans += 4 * (h - 1); return ans;};

    int answer = 0;

    // compute all stacks
    const size_t H = A.size();
    const size_t W = A[0].size();

    for (size_t i = 0; i < H; i++)
    {
        for (size_t j = 0; j < W; j++)
        {
            answer += stack_area(A[i][j]);
        }
    }

    // subract intersections for zero row
    for (size_t j = 1; j < W; j++)
    {
        answer -= 2 * std::min(A[0][j - 1], A[0][j]);
    }

    // & rest for the grid
    for (size_t i = 1; i < H; i++)
    {
        for (size_t j = 1; j < W; j++)
        {
            answer -= 2 * std::min(A[i][j - 1], A[i][j]);
        }

        for (size_t j = 0; j < W; j++)
        {
            answer -= 2 * std::min(A[i - 1][j], A[i][j]);
        }
    }

    return answer;
}
