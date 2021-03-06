// Greedy_goodland: https://www.hackerrank.com/challenges/pylons/problem
// 1-2-3 just make the procedure like this:

struct MyCity { size_t index; bool canBuild; bool covered; };
struct MyInterval { size_t index; size_t start; size_t finish;  bool isChosen; };

typedef vector<MyCity> Citivec;
typedef vector<MyInterval> Iv_vec;
typedef vector<int> I_vec;

int findMaxUncovered(const Iv_vec& local_access, const Citivec& mycities)
{
    int answer = INT_MIN;       // return this if we're undefined
    int max_uncovered = INT_MIN;

    for (size_t j = 0; j < local_access.size(); j++)
    {
        MyInterval ivl = local_access[j];

        if (ivl.isChosen) continue;

        // count all uncovered cities
        int num_uncovered = 0;
        for (size_t i = ivl.start; i <= ivl.finish; i++)
        {
            if (!mycities[i].covered) num_uncovered++;
        }

        if (num_uncovered > max_uncovered)
        {
            max_uncovered = num_uncovered;
            answer = ivl.index;
        }
    }

    return answer;
}


Iv_vec findUnChosen(const size_t city, const Iv_vec& myintervals)
{
    Iv_vec answer;

    for (auto ivl : myintervals)
    {
        if (city >= ivl.start && city <= ivl.finish) answer.push_back(ivl);
    }

    return answer;
}

Iv_vec createIntervals(const size_t distance, const Citivec& arr)
{
    Iv_vec answer;
    const size_t my_size = arr.size();

    size_t i_count = 0;
    for (size_t i = 0; i < my_size; i++)
    {
        if (arr[i].canBuild)
        {
            MyInterval temp;

            temp.start = (i > distance) ? (i - distance) : 0;
            temp.finish = (i + distance > my_size - 1) ? (my_size - 1) : (i + distance);
            temp.isChosen = false;
            temp.index = i_count;
            answer.push_back(temp);
            i_count++;
        }
    }

    return answer;
}

Citivec populateCities(const I_vec& arr)
{
    Citivec answer;

    for (size_t i = 0; i < arr.size(); i++)
    {
        MyCity temp;
        temp.index = i;
        temp.covered = false;
        temp.canBuild = (arr[i] == 1) ? true : false;
        answer.push_back(temp);
    }

    return answer;
}


int pylons(const int k, const I_vec& arr)
{
    const size_t distance = k - 1;

    Citivec myCities = populateCities(arr);
    Iv_vec myintervals = createIntervals(distance, myCities);

    // for each cities
    for(auto city : myCities)
    {
        if (city.covered) continue;

        Iv_vec local_access = findUnChosen(city.index, myintervals);

        if (local_access.size() == 0) return -1;

        // find the largest number of not covered cities
        int largest = findMaxUncovered(local_access, myCities);
        if (largest < 0) return -1;

        size_t largestIndex = static_cast<size_t>(largest);

        // mark all as covered
        myintervals[largestIndex].isChosen = true;

        for (size_t j = myintervals[largestIndex].start; j <= myintervals[largestIndex].finish; j++)
        {
            myCities[j].covered = true;
        }
    }

    int answer = 0;

    for (auto ivl : myintervals)
    {
        if (ivl.isChosen) answer += 1;
    }

    return answer;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = pylons(k, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
