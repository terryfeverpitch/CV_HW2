#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

// Choose 4 points
vector<Point2f> points;
// Input Quadilateral or Image plane coordinates
Point2f inputQuad[4];
// Output Quadilateral or World plane coordinates
Point2f outputQuad[4];

// Lambda Matrix
Mat lambda(2, 4, CV_32FC1);
//Input and Output Image;
Mat input, output, tmp[5];

int distance(Point2f& a, Point2f& b) {
    return (int)sqrt((float)((a.x - b.x) * (a.x - b.x)+(a.y - b.y) * (a.y - b.y)));
//    return (a.x - b.x) * (a.x - b.x)+(a.y - b.y) * (a.y - b.y);
}

void doTransform() {
    // The 4 points that select quadilateral on the input , from top-left in clockwise order
    // These four pts are the sides of the rect box used as input
    inputQuad[0] = Point2f(points[0]);
    inputQuad[1] = Point2f(points[1]);
    inputQuad[2] = Point2f(points[2]);
    inputQuad[3] = Point2f(points[3]);

    int length = input.rows-1;
    int width = input.cols-1;
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f(0,0);
    outputQuad[1] = Point2f(width,0);
    outputQuad[2] = Point2f(width, length);
    outputQuad[3] = Point2f(0,length);

    // Get the Perspective Transform Matrix i.e. lambda
    lambda = getPerspectiveTransform(inputQuad, outputQuad);
    // Apply the Perspective Transform just found to the src image
    warpPerspective(input,output,lambda,output.size());


    imshow("Output",output);
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if(event == EVENT_LBUTTONDOWN && points.size() < 4) {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

        points.push_back(Point(x,y));
        tmp[points.size()] = tmp[points.size() - 1].clone();
        circle(tmp[points.size()], points.back(), 8, CV_RGB(255,0,0), -1, 4, 3);
        if(points.size() > 1)
            line(tmp[points.size()], points.back(), points.at(points.size() - 2), CV_RGB(255,0,0), 3, 8, 0);
    }
    else if(event == EVENT_RBUTTONDOWN && points.size() > 0) {
        cout << "Right button of the mouse is clicked - remove (" << points.back().x << ", " << points.back().y << ")" << endl;
        points.pop_back();
    }

    if(event == EVENT_LBUTTONDOWN && points.size() == 4) {
        line(tmp[points.size()], points.at(0), points.at(3), CV_RGB(255,0,0), 3, 8, 0);
        doTransform();
    }

    if(tmp[points.size()].data) {
        imshow("Input", tmp[points.size()]);
    }
}

int main(int argc, char* argv[]) {
    cout << "\nComputer Vision HW2" << endl;
    cout << "\nLeft button click - choose a point." << endl;
    cout << "Right button click - undo." << endl;
    cout << "\n============================================" << endl;
    cout << "Please choose the points in clockwise order." << endl;
    cout << "like : 0----1" << endl;
    cout << "       |    |" << endl;
    cout << "       |    |" << endl;
    cout << "       |    |" << endl;
    cout << "       3----2" << endl;
    cout << "Press 'ESC' to leave." << endl;
    cout << "============================================\n" << endl;
    //Load the image
    input = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    // Check for invalid input
    if(!input.data) {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    tmp[0] = input.clone();
    // Set the lambda matrix the same type and size as input
    lambda = Mat::zeros(input.rows, input.cols, input.type());

    //Display input and output
    //Create a window
    namedWindow("Input", 1);

    //set the callback function for any mouse event
    setMouseCallback("Input", CallBackFunc, NULL);

    imshow("Input",input);

    while(1) {
        char k = waitKey(0);
        if(k == 27)
            break;
    }

    return 0;
}
