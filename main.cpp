#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    // Show help
    if (argc < 2) {
        cout <<
            " Usage: tracker <video_name>\n"
            " examples:\n"
            " object_video.mp4\n"
            << endl;
        return 0;
    }

    // Declare all required variables
    Rect2d roi; // Use Rect2d for tracking
    Mat frame;

    // Create a tracker object
    Ptr<TrackerKCF> tracker = TrackerKCF::create();

    // Set input video
    string video = argv[1];
    VideoCapture cap(video);

    if (!cap.isOpened()) {
        cerr << "Error: Could not open video file." << endl;
        return -1;
    }

    // Get the first frame from the video
    cap >> frame;

    // Select ROI
    roi = selectROI("tracker", frame);
    
    // Quit if ROI was not selected
    if (roi.width == 0 || roi.height == 0) {
        cerr << "Error: Invalid ROI selection." << endl;
        return -1;
    }

    // Initialize the tracker
    tracker->init(frame, roi);

    // Perform the tracking process
    cout << "Start the tracking process, press ESC to quit." << endl;
    while (true) {
        // Get frame from the video
        cap >> frame;

        // Stop the program if no more images
        if (frame.empty())
            break;

        // Update the tracking result
        Rect roiRect(static_cast<int>(roi.x), static_cast<int>(roi.y), static_cast<int>(roi.width), static_cast<int>(roi.height)); // Convert Rect2d to Rect
        bool ok = tracker->update(frame, roiRect); // Pass roiRect as Rect

        // Check if tracking succeeded
        if (ok) {
            // Draw the tracked object
            rectangle(frame, roiRect, Scalar(255, 0, 0), 2, 1);
        } else {
            // Tracking failure detected
            putText(frame, "Tracking failure detected", Point(100, 80), 
                    FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
        }

        // Show image with the tracked object
        imshow("tracker", frame);

        // Quit on ESC button
        if (waitKey(1) == 27) break; // ESC key
    }

    destroyAllWindows(); // Clean up windows
    return 0;
}
