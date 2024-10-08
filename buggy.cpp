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
            //allocate the memory for each point so we can actually put points in the array
            for(int i=0;i<=vertices;i++)
            {
                points[i] = new Point();
            }
        }

        ~Shape () {
            //add a way to delete the memory we allocated
            for(int i=0;i<=vertices;i++)
            {
                delete points[i];
            }
            delete[] points;
        }

        void addPoints (Point* pts) {
            for (int i = 0; i <= vertices; i++) {
                memcpy(points[i], &pts[i%vertices], sizeof(Point));
            }
        }

        //change the output to just be a double and not the reference to a local variable
        double area () {
            int temp = 0;
            for (int i = 0; i < vertices; i++) {
                // FIXME: there are two methods to access members of pointers
                //        use one to fix lhs and the other to fix rhs
                //can use the arrows or dereference then use the dot
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
    //create the points 3 different ways
    Point tri1(0,0);
    Point tri2;
    tri2.x = 1;
    tri2.y = 2;
    struct Point tri3 = {2,0};
    

    // adding points to tri
    //create a new Point array then add 3 points to it
    Point triPts[3];
    triPts[0] = tri1;
    triPts[1] = tri2;
    triPts[2] = tri3;
    Shape* tri = new Shape(3);
    //change to an arrow cause tri is a pointer
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)
    //creating the 4 points with the parameterized constructor
    Point quad1(0,0);
    Point quad2(0,2);
    Point quad3(2,2);
    Point quad4(2,0);

    // adding points to quad
    //create a new Point array and add 4 points to it
    Point quadPts[4];
    quadPts[0] = quad1;
    quadPts[1] = quad2;
    quadPts[2] = quad3;
    quadPts[3] = quad4;
    Shape* quad = new Shape(4);
    //change to an arrow because quad is a pointer
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    std::cout << "The area of tri is: " << tri->area() << std::endl;
    std::cout << "The area of quad is: " << quad->area() << std::endl;

    //delete the memory we allocated for the points
    delete tri;
    delete quad;
}