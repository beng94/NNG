#include <vector>
#include <iostream>
#include <algorithm>

const int N = 500;

class Group
{
    public:
        std::vector<int> nums;

        int worst_num()
        {
            int array[N + 1] = {0};
            for(int i = 0; i < nums.size() -1; i++)
            {
                for(int j = i + 1; j < nums.size(); j++)
                {
                    int a = nums[i];
                    int b = nums[j];
                    if(std::find(nums.begin(), nums.end(), a+b) != nums.end())
                    {
                        array[a]++;
                        array[b]++;
                        array[a+b]++;
                    }
                }
            }

            int max = 0;
            int max_id = -1;
            for(int i = 0; i < N; i++)
            {
                if(array[i] > max)
                {
                    max = array[i];
                    max_id = i;
                }
            }

            return max_id;
        }
};


class Prison
{
    public:
       std::vector<Group> groups;

       Prison(std::vector<int> nums)
       {
            Group g;
            g.nums = nums;

            groups.push_back(g);
       }

        void sort()
        {
            int id = 0;
            while(groups[id].worst_num() != -1)
            {
                int worst_num = groups[id].worst_num();

                for(int i= 0; i< groups[id].nums.size(); i++)
                {
                    if(groups[id].nums[i] == worst_num)
                    {
                        groups[id].nums.erase(groups[id].nums.begin() + i);
                        break;
                    }
                }

                if(groups.size() == id + 1)
                {
                    Group new_g;
                    new_g.nums.push_back(worst_num);

                    groups.push_back(new_g);

                }
                else
                {
                    groups[id + 1].nums.push_back(worst_num);
                }

                if(groups[id].worst_num() == -1)
                {
                     id++;
                }
            }
        }

        void get_results()
        {
            std::cout << groups.size() << std::endl;
             for(auto g: groups)
             {
                 for(auto n: g.nums)
                 {
                     std::cout << n << " ";
                 }
                 std::cout << std::endl;
             }
        }
};

int main()
{
    std::vector<int> nums;
    for(int i = 1; i <= 500; i++)
    {
        nums.push_back(i);
        nums.push_back(i);
    }
    Prison p(nums);
    p.sort();
    p.get_results();

    return 0;
}
