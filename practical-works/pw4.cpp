// Create a class "Quadrilateral", which contains 5 numbers - 
// side lengths of a quadrilateral and a freely chosen angle in degrees (1..179).
// Create the following methods for class "Quadrilateral": 
// (1) constructor that gives the starting values, 
// (2) destructor that announces object liquidation, 
// (3) method "Change" with 5 parameters that alter side lengths of a triangle
//     and the freely chosen angle by a specific amount (alter not change), 
// (4) method "Print" that prints out side lengths of quadrilateral and the angle,
// (5) method "Calculation" that prints out the type of the quadrilateral: 
//     square, rectangle, rhombus, parallelogram or other.


#include <iostream>
using namespace std;

class Quadrilateral {
private:
    double a, b, c, d;
    int angle;

public:
    Quadrilateral(double a1, double b1, double c1, double d1, int angle1) {
        a = a1;
        b = b1;
        c = c1;
        d = d1;
        angle = angle1;
    }

    ~Quadrilateral() {
        cout << "Quadrilateral object has been destroyed." << endl;
    }

    // Adds the given amounts to the values
    void Change(double changeA, double changeB, double changeC, double changeD, int changeAngle) {
        // All new side lengths must be positive
        if (a + changeA <= 0 || b + changeB <= 0 ||
            c + changeC <= 0 || d + changeD <= 0 ||

            // Angle stays between 1 and 170
            angle + changeAngle < 1 || angle + changeAngle > 179) { 
                cout << "Values were not changed." << endl;
            return;
        }

        a += changeA;
        b += changeB;
        c += changeC;
        d += changeD;
        angle += changeAngle;
    }

    void Print() {
        cout << "Side a: " << a << endl;
        cout << "Side b: " << b << endl;
        cout << "Side c: " << c << endl;
        cout << "Side d: " << d << endl;
        cout << "Angle: " << angle << " degrees" << endl;
    }

    // Identifies the type
    void Calculation() {
        bool equalAB = (a == b);
        bool equalBC = (b == c);
        bool equalCD = (c == d);
        bool equalDA = (d == a);

        bool oppositeEqual = (a == c && b == d);
        bool rightAngle = (angle == 90);

        cout << "Quadrilateral type: ";

        // All four sides equal and one right angle -> square
        if (equalAB && equalBC && equalCD && equalDA
            && rightAngle) {
            cout << "Square" << endl;
        }
        // Opposite sides equal and one right angle -> rectangle
        else if (oppositeEqual && rightAngle) {
            cout << "Rectangle" << endl;
        }
        // All four sides equal, but angle is not 90deg -> rhombus
        else if (equalAB && equalBC && equalCD && equalDA) {
            cout << "Rhombus" << endl;
        }
        // Opposite sides equal, but angle is not 90deg -> parallelogram
        else if (oppositeEqual) {
            cout << "Parallelogram" << endl;
        }
        else {
            cout << "Other" << endl;
        }
    }
};

int main() {
    // Figure with four sides and an angle
    Quadrilateral q(5, 5, 5, 5, 90);

    cout << "Original quadrilateral:" << endl;
    q.Print();
    q.Calculation();

    cout << "\nAfter changing the values:" << endl;

    q.Change(1, 2, 1, 2, 15);

    q.Print();
    q.Calculation();

    return 0;
}