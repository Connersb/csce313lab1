#include <iostream>
#include <cstring>

struct Point {
    int x, y;

    Point () : x(), y() {}
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
    public:
        int vertices;
        Point** points;

        Shape (int _vertices) {
            vertices = _vertices;
            points = new Point*[vertices+1];
            for(int i=0;i<=vertices;i++)
            {
                points[i] = new Point();
            }
        }

        ~Shape () {
            for(int i=0;i<=vertices;i++)
            {
                delete points[i];
            }
            delete[] points;
        }

        //should just be a single pointer not two because it's just a list not a 2D array
        void addPoints (Point* pts) {
            for (int i = 0; i <= vertices; i++) {
                memcpy(points[i], &pts[i%vertices], sizeof(Point));
            }
        }

        double area () {
            int temp = 0;
            //should jsut be less than not less than or equal b/c you are checking i+1
            for (int i = 0; i < vertices; i++) {
                // FIXME: there are two methods to access members of pointers
                //        use one to fix lhs and the other to fix rhs
                int lhs = points[i]->x * points[i+1]->y;
                int rhs = (*points[i+1]).x * (*points[i]).y;
                temp += (lhs - rhs);
            }
            double area = abs(temp)/2.0;
            return area;
        }
};

int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
    //          tri1 = (0, 0)
    //          tri2 = (1, 2)
    //          tri3 = (2, 0)
    Point tri1(0, 0);
    Point tri2;
    tri2.x = 1;
    tri2.y = 2;
    struct Point tri3 = {2,0};

    // adding points to tri
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    //use -> and not . beacuse tri is a pointer
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)
    Point quad1(0,0);
    Point quad2(0,2);
    Point quad3(2,2);
    Point quad4(2,0);

    // adding points to quad
    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    //use -> and not . beacuse quad is a pointer
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    std::cout << "The area of tri is: " << tri->area() << std::endl;
    std::cout << "The area of quad is: " << quad->area() << std::endl;

    //delete the shapes to avoid memory leaks
    delete tri;
    delete quad;
}
