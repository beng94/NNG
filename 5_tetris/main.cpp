#include "tetris.hpp"
#include <iostream>
#include <set>
#include <cstdio>

int main()
{
    Shape s(2, true);

    std::set<Shape> shapes;
    shapes.insert(s);

    for(int i = 0; i < 7; i++)
    {
        int cnt= 0;
        std::set<Shape> new_shapes;
        for(auto s: shapes)
        {
            cnt++;
            if(cnt % 10000 == 0)
            {
                std::cout << cnt << new_shapes.size();

                for(const auto& a: new_shapes)
                {
                    Shape tmp = a;
                    Shape s1 = tmp.rotate();
                    Shape s2 = tmp.rotate();
                    Shape s3 = tmp.rotate();

                    if (!(s1 == a)) new_shapes.erase(s1);
                    if(!(s2 == a)) new_shapes.erase(s2);
                    if(!(s3 == a)) new_shapes.erase(s3);
                }

                std::cout << " " << new_shapes.size() << std::endl;
            }

            auto vec = std::move(s.extend());

            for(const auto& v: vec)
            {
                Shape d = v;

                Shape s1 = d.rotate();
                Shape s2 = d.rotate();
                Shape s3 = d.rotate();

                if(!s1.has_hole()) new_shapes.insert(s1);
                if(!s2.has_hole()) new_shapes.insert(s2);
                if(!s3.has_hole()) new_shapes.insert(s3);
           }
        }

        for(const auto& a: new_shapes)
        {
            Shape tmp = a;
            Shape s1 = tmp.rotate();
            Shape s2 = tmp.rotate();
            Shape s3 = tmp.rotate();

            if (!(s1 == a)) new_shapes.erase(s1);
            if(!(s2 == a)) new_shapes.erase(s2);
            if(!(s3 == a)) new_shapes.erase(s3);
        }

        shapes.clear();
        shapes = new_shapes;

        std::cout << shapes.size() << std::endl;
    }

    return 0;
}
