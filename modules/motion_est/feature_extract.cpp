#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "feature_extract.hpp"
#include <algorithm>
#include <opencv2/imgcodecs.hpp>
namespace vsl
{
    static int callcnt = 0;
    void find_feature_matches(cv::Mat const &img_1,
                              cv::Mat const &img_2,
                              std::vector<cv::KeyPoint> &keypoints_1,
                              std::vector<cv::KeyPoint> &keypoints_2,
                              std::vector<cv::DMatch> &goodmatches)
    {
        using namespace cv;
        using namespace std;

        //-- 第一步:检测 Oriented FAST 角点位置
        Ptr<FeatureDetector> detector = ORB::create();
        detector->detect(img_1, keypoints_1);
        detector->detect(img_2, keypoints_2);

        //-- 第二步:根据角点位置计算 BRIEF 描述子
        Ptr<DescriptorExtractor> descriptor = ORB::create(100,1.2,8,13); 
        Mat descriptors_1, descriptors_2;
        descriptor->compute(img_1, keypoints_1, descriptors_1);
        descriptor->compute(img_2, keypoints_2, descriptors_2);

        //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
        Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
        vector<DMatch> allmatches;
        matcher->match(descriptors_1, descriptors_2, allmatches);

        //-- 第四步:匹配点对筛选
        double min_dist = 10000, max_dist = 0;

        //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
        for (int i = 0; i < descriptors_1.rows; i++)
        {
            double dist = allmatches[i].distance;
            if (dist < min_dist)
                min_dist = dist;
            if (dist > max_dist)
                max_dist = dist;
        }

        size_t n = allmatches.size() / 3;
        std::nth_element(allmatches.begin(),
                         allmatches.begin() + n,
                         allmatches.end(),
                         []( auto &&m1, auto &&m2)
                         { return m1.distance < m2.distance; });

        //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.但有时候最小距离会非常小,设置一个经验值30作为下限.
        for (int i = 0; i < descriptors_1.rows; i++)
        {
            if (allmatches[i].distance <= allmatches[n].distance)
            {
                goodmatches.push_back(allmatches[i]);
            }
        }

        Mat img_goodmatch;
        drawMatches(img_1, keypoints_1, img_2, keypoints_2, goodmatches, img_goodmatch);
        cv::imwrite("D:\\Projects\\vslam_lab\\data\\mc\\output\\match" + std::to_string(callcnt++) + ".png", img_goodmatch);
    }
}