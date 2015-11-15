#include "tetris.hpp"
#include <iostream>
#include <set>
#include <cstdio>

int main()
{
    Shape init_shape(16);
    init_shape.set_id(0,0,1);
    init_shape.set_id(0,1,1);

    std::set<Shape> shapes;
    shapes.insert(init_shape);
    for(int i = 0; i < 7; i++)
    {
        int cnt = 0;
        std::set<Shape> new_shapes;

        for(const auto& s: shapes)
        {
            cnt++;
            if(cnt % 5000 == 0)
            {
                //std::cout << new_shapes.size();
                std::cout << cnt << " " << new_shapes.size() << " ";
                for(const auto& a: new_shapes)
                {
                    Shape tmp = a;
                    tmp.rotate();
                    if(!(tmp == a)) new_shapes.erase(tmp);
                    tmp.rotate();
                    if(!(tmp == a)) new_shapes.erase(tmp);
                    tmp.rotate();
                    if(!(tmp == a)) new_shapes.erase(tmp);
                }
                std::cout << new_shapes.size()  << std::endl;
            }

            auto extended = s.extend();
            new_shapes.insert(extended.begin(), extended.end());
        }

        for(const auto& s: new_shapes)
        {
            Shape tmp = s;
            tmp.rotate();
            if(!(tmp == s))
            {
                new_shapes.erase(tmp);
            }
            tmp.rotate();
            if(!(tmp == s))
            {
                new_shapes.erase(tmp);
            }
            tmp.rotate();
            if(!(tmp == s))
            {
                new_shapes.erase(tmp);
            }
        }

        shapes = new_shapes;

        if(i == 4)
        {
            std::cout << shapes.size() << " " << 12 << std::endl;
            for(auto a: shapes)
                a.print( 12 );

            exit(1);

        }

    }

    return 0;
}
