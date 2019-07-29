//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;

extern mcu_data mcuData;

//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(cv::Point target_point_) {
    float target_polar_angle_ = static_cast<float>(180 / PI * atan2(-1 * (target_point_.y - circle_center_point.y),
                                                                    (target_point_.x - circle_center_point.x)));
    if (target_polar_angle_ > 40 && target_polar_angle_ < 140){
        extra_delta_x = 0;
        extra_delta_y = -14;
    }
    else if (target_polar_angle_ > 30 && target_polar_angle_ <= 40){
        extra_delta_x = 8;
        extra_delta_y = -8;
    }
    else if (target_polar_angle_ >= 140 && target_polar_angle_ < 150){
        extra_delta_x = -8;
        extra_delta_y = -8;
    }
    else {
        extra_delta_x = 0;
        extra_delta_y = 0;
    }

//    if (target_polar_angle_ > 20 && target_polar_angle_ <= 90) {
//        extra_delta_y = -17 * (target_polar_angle_ - 20) / 70;
//    } else if (target_polar_angle_ > 90 && target_polar_angle_ < 160) {
//        extra_delta_y = -17 * (160 - target_polar_angle_) / 70;
//    } else {
//        extra_delta_y = 0;
//    }

    double dx = -(target_point_.x - 320 - COMPENSATE_YAW - mcuData.delta_x - manual_delta_x - extra_delta_x);
    double dy = -(target_point_.y - 240 - COMPENSATE_PITCH - mcuData.delta_y - manual_delta_y - extra_delta_y);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
//    cout << "yaw: " << yaw_rotation << '\t' << "pitch: " << pitch_rotation << endl;
//    cout << "mcuData.delta_x: " << mcuData.delta_x << '\t' << "mcuData.delta_y: " << mcuData.delta_y << endl;
//    cout << "manual delta: " << manual_delta_x << '\t' << manual_delta_y << endl;

}
