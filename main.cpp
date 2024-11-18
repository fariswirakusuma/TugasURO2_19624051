#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>

using namespace cv;
using namespace std;

string _file[3] = {"Tok dalang_mengerikan.mp4","object_video.mp4","ini_telapak_kaki_atok_ni (online-video-cutter.com).mp4"};

int main()
{
    string FIle  = _file[0];
    VideoCapture Vid(FIle);
    if (!Vid.isOpened()) {
        cout << "Error: Could not open video!" << endl;
        return -1;
    }

    Ptr<Tracker> tracker = TrackerKCF::create();    

    Mat frame;
    int lebar_frame = static_cast<int>(Vid.get(CAP_PROP_FRAME_WIDTH));
    int tinggi_frame = static_cast<int>(Vid.get(CAP_PROP_FRAME_HEIGHT));

    VideoWriter output("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                       Vid.get(CAP_PROP_FPS), Size(lebar_frame, tinggi_frame));
    if (!Vid.read(frame)) {
        cout << "Error: Could not read the first frame!" << endl;
        return -1;
    }
    Rect trackbox = selectROI("Select ROI", frame, false);
    if (trackbox.width == 0 || trackbox.height == 0) {
        cout << "Error: No ROI selected!" << endl;
        return -1;
    }
    tracker->init(frame, trackbox);

    Scalar lower_hsv(35, 100, 100); 
    Scalar upper_hsv(85, 255, 255);

    while (Vid.read(frame)) {
        Mat hsv_frame;
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV); 
        Mat mask;
        inRange(hsv_frame, lower_hsv, upper_hsv, mask);
        if (tracker->update(frame, trackbox)) { 
            rectangle(frame, trackbox, Scalar(255, 0, 0), 2, 8);
        }

       
        imshow("Mask", mask);
        imshow("Video feed", frame);
        output.write(frame);

        if (waitKey(25) >= 0) break;
    }

    output.release();
    Vid.release();
    destroyAllWindows();

    return 0;
}
