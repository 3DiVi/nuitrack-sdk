#include <iostream>

#include <nuitrack/Nuitrack.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace tdv::nuitrack;
using namespace tdv::nuitrack::device;

bool isColorViewMode = false;
cv::Scalar colors[8] = {cv::Scalar(212,255,127), cv::Scalar(0,128,0),
                        cv::Scalar(0,255,255), cv::Scalar(0,0,255),
                        cv::Scalar(0,165,255), cv::Scalar(122,160,255),
                        cv::Scalar(255,0,255), cv::Scalar(180,105,255)};

void depthCallback(const DepthFrame::Ptr &frame, cv::Mat &window)
{
    if (!frame || isColorViewMode) return;

    cv::Mat depth(frame->getRows(), frame->getCols(), CV_16UC1, const_cast<uint16_t *>(frame->getData()));
    depth /= 25;
    depth.convertTo(depth, CV_8UC1);
    cv::cvtColor(depth, window, cv::COLOR_GRAY2BGR);
}

void colorCallback(const RGBFrame::Ptr &frame, cv::Mat &window)
{
    if (!frame || !isColorViewMode) return;

    cv::Mat image(frame->getRows(), frame->getCols(), CV_8UC3, (void*)frame->getData());

    cv::resize(image, image, cv::Size2i(window.cols, window.rows));
    image.copyTo(window);
}

void skeletonCallback(const SkeletonData::Ptr& userSkeletons, cv::Mat &window)
{
    if (!userSkeletons)
        return;

    const std::vector<Skeleton>& skeletons = userSkeletons->getSkeletons();
    for (const auto & skeleton : skeletons)
    {
        for (size_t j = 0; j < skeleton.joints.size(); ++j)
        {
            cv::circle(window, cv::Point(skeleton.joints[j].proj.x * window.cols, skeleton.joints[j].proj.y * window.rows), 7, cv::Scalar(255, 255, 255), -1);
        }
    }
}

void userCallback(const UserFrame::Ptr& users, cv::Mat &window)
{
    if (!users || isColorViewMode) return;

    cv::Mat mask(users->getRows(), users->getCols(), CV_16UC1, const_cast<uint16_t *>(users->getData()));
    mask.convertTo(mask, CV_8UC1);

    for (const auto& user : users->getUsers())
        window.setTo(colors[user.id % 8], mask == user.id);
}

class Tracker
{
public:
    explicit Tracker(const NuitrackDevice::Ptr& dev)
    {
        device = dev;

        Nuitrack::setDevice(device);

        colorSensor = ColorSensor::create();
        depthSensor = DepthSensor::create();

        OutputMode mode = depthSensor->getOutputMode();
        window = cv::Mat(mode.yres, mode.xres, CV_8UC3, cv::Scalar());
        // Bind to event new depth frame
        depthSensor->connectOnNewFrame(std::bind(depthCallback, std::placeholders::_1, window));
        // Bind to event new rgb frame
        colorSensor->connectOnNewFrame(std::bind(colorCallback, std::placeholders::_1, window));

        skeletonTracker = SkeletonTracker::create();
        // Bind to event new Skeleton Tracker
        skeletonTracker->connectOnUpdate(std::bind(skeletonCallback, std::placeholders::_1, window));

        userTracker = UserTracker::create();
        // Bind to event new User Tracker
        userTracker->connectOnUpdate(std::bind(userCallback, std::placeholders::_1, window));
    }

    NuitrackDevice::Ptr device;
    DepthSensor::Ptr depthSensor;
    ColorSensor::Ptr colorSensor;
    SkeletonTracker::Ptr skeletonTracker;
    UserTracker::Ptr userTracker;
    cv::Mat window;
};

void showImage(std::vector<Tracker> &trackers)
{
    int cols = trackers[0].window.cols;
    int rows = trackers[0].window.rows;

    cv::Mat image;

    int n = (int)ceil(sqrt((int)trackers.size()));

    for (int i = 0; i < n; ++i)
    {
        bool flag = false;
        std::vector<cv::Mat> windowRow;
        for (int j = 0; j < n; ++j)
        {
            int k = i * n + j;
            if (k < trackers.size())
            {
                if (trackers[k].window.rows != rows || trackers[k].window.cols != cols)
                {
                    cv::Mat resized;
                    cv::resize(trackers[k].window, resized, cv::Size2i(cols, rows));
                    windowRow.push_back(resized);
                }
                else
                    windowRow.push_back(trackers[k].window);

                flag = true;
            }
            else
            {
                windowRow.push_back(cv::Mat(rows, cols, CV_8UC3, cv::Scalar()));
            }
        }

        if (flag)
        {
            cv::Mat windowRowImage;
            cv::hconcat(windowRow, windowRowImage);
            if (i == 0) image = windowRowImage;
            else cv::vconcat(windowRowImage, image, image);
        }
    }

    cv::imshow("Nuitrack Multi-Sensor", image);
}

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN)
        isColorViewMode = !isColorViewMode;
}

int main()
{
    cv::namedWindow("Nuitrack Multi-Sensor");
    cv::setMouseCallback("Nuitrack Multi-Sensor", mouseCallback);
//  Initialize Nuitrack 
    Nuitrack::init();
//  Get all connected sensors
    auto devices = Nuitrack::getDeviceList();

    if (devices.empty())
    {
        std::clog << "No devices available!" << std::endl;
        Nuitrack::release();
        return 0;
    }
//  Create Nuitrack Modules for each sensor
    std::vector<Tracker> trackers;
    for (const auto& device : devices)
    {
        trackers.emplace_back(device);
    }
//  When Nuitrack modules are created, we need to call Nuitrack::run() to start processing all modules
    Nuitrack::run();

    while (true)
    {
        try
        {
            // Wait and update Nuitrack data for all Nuitrack instance
            for (const auto& tracker : trackers)
            {
                Nuitrack::waitUpdate(tracker.skeletonTracker);
            }

        } catch (const LicenseNotAcquiredException& e)
        {
            std::cerr << "NUITRACK: LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << std::endl;
            break;
        }
//  Show images from all sensors
        showImage(trackers);

        char c = cv::waitKey(1);
        if (c == 27) break;
    }
//  Release Nuitrack and remove all modules
    Nuitrack::release();

    return 0;
}
