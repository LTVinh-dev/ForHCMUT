#include <iostream>
#include <math.h>
using namespace std;
double getDiameter(double radius)

{
    return (radius *2);
   //TODO

}

double getCircumference(double radius)

{
    return (2*3.14*radius);
   //TODO

}

double getArea(double radius)

{

   return (3.14*radius*radius);
   //TODO

}
int main()
{
    double radius, diameter, circle, area;
    cin>>radius;
    diameter = getDiameter(radius); // Calling getDiameter function
    circle = getCircumference(radius); // Calling getCircumference function
    area = getArea(radius); // Calling getArea function
    cout<<"Diameter of the circle: "<<diameter <<" units"<<endl;
    cout<<"Circumference of the circle: "<< circle<<" units"<<endl;
    cout<<"Area of the circle:"<< area<<" sq. units"<<endl;
    return 0;
}