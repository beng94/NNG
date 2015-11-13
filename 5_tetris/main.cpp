#include "tetris.hpp"
#include <iostream>

int main()
{
    Shape s(2, true);
    s.set_rotations();

    std::vector<Shape> shapes;
    shapes.push_back(s);

    for(int i = 0; i < 7; i++)
    {
        std::vector<Shape> new_shapes;
        int cnt = 0;
        for(auto s: shapes)
        {
            std::cout << (++cnt) << " " << new_shapes.size() << std::endl;
            auto vec = s.extend();
            for(auto v: vec)
            {
                if(!v.exists(new_shapes))
                {
                     new_shapes.push_back(v);
                }
            }
        }

        //shapes = new_shapes;
        shapes.clear();
        for(auto n: new_shapes)
            shapes.push_back(n);

        std::cout << shapes.size() << std::endl;
    }

    return 0;
}
