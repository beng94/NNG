#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iterator>


int Partition (std::vector<std::string>& data, const int& _begin, const int& _end)
{
    int pivot_id = rand() % (_end - _begin) + _begin;
    std::string pivot_value = data[pivot_id];

    std::swap(data[pivot_id], data[_end]);

    int left_id = _begin;
    for(int i = _begin; i < _end; i++)
    {
        if(data[i] <= pivot_value)
        {
            std::swap(data[i], data[left_id]);
            left_id++;
        }
    }

    std::swap(data[_end], data[left_id]);

    return left_id;
}

void Sort(std::vector<std::string>& data, const int& _begin, const int& _end)
{
    if(_begin < _end)
    {
        int a = Partition(data, _begin, _end);
        Sort(data, _begin, a-1);
        Sort(data, a+1, _end);
    }
}

void QuickSort(std::vector<std::string>& data)
{
    Sort(data, 0, data.size()-1);
}


int main()
{
    const int num_chars = ('z' - 'a') + 1;
    const int num_chars_2 = num_chars * num_chars;
    const int num_chars_3 = num_chars_2 * num_chars;
    const unsigned int num_chars_4 = num_chars_3 * num_chars;
    std::vector<std::string> buckets [26*26*26*26];

    for(auto& vec: buckets)
    {
        vec.reserve(10);
    }

    std::ifstream file("sample.txt");

    /*
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(length);
    file.read(&buffer[0], length);

    int last = 8;
    for(int i = 8;i < buffer.size(); i++)
    {
        if(buffer[i] == '\n')
        {
            std::string str(buffer.begin() + last, buffer.begin() + i);
            last = i + 1;
            int c = str[0] - 'a';
            int d = str[1] - 'a';
            int e = str[2] - 'a';
            int f = str[3] - 'a';
            buckets[c*num_chars_3 + d * num_chars_2 + e * num_chars+ f].push_back(std::move(str));
            i += 4;
        }
    }


    for(auto& vec: buckets)
    {
        Sort(vec, 0, vec.size()-1);
    }

    return 0;
    */

/*
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(length, ' ');
    file.read(&buffer[0], length);

    std::istringstream iss(buffer);
    std::vector<std::string> strs {
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}};

    strs.erase(strs.begin()); //remove the number
    */

    int n;
    file >> n;

    //for(auto str: strs)
    for(int i = 0; i < n; i++)
    {
        std::string str;
        file >> str;
        int c = str[0] - 'a';
        int d = str[1] - 'a';
        int e = str[2] - 'a';
        int f = str[3] - 'a';
        buckets[c*num_chars_3 + d * num_chars_2 + e * num_chars+ f].push_back(std::move(str));
        //buckets[c*num_chars_2 + d * num_chars + e].push_back(std::move(str));
    }

    for(auto& vec: buckets)
    {
        //QuickSort(vec);
        Sort(vec, 0, vec.size()-1);
    }

    return 0;
    for(auto b: buckets)
    {
        for(auto s: b)
        {
            printf("%s\n", s.c_str());
            std::fflush(stdout);

        }
    }
        //std::cout << s << std::endl;

    return 0;
}
