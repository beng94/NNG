#include "tetris.hpp"
#include <iostream>

int main()
{
    Shape s(2, true);
    s.extend();

    std::vector<Shape> shapes;
    shapes.push_back(s);

    std::vector<int> sol_num;

    for(int i = 0; i < 7; i++)
    {
        std::vector<Shape> new_shapes;
        for(auto s: shapes)
        {
            auto vec = s.extend();
            for(auto v: vec)
            {
                if(!v.exists(new_shapes))
                    new_shapes.push_back(v);
            }
        }

        //shapes = new_shapes;
        shapes.clear();
        for(auto n: new_shapes)
            shapes.push_back(n);

        sol_num.push_back(shapes.size());
        std::cout << shapes.size() << std::endl;
    }

    for(auto i: sol_num)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
