//
// Created by sjturm on 19-5-17.
//

#ifndef _ADDITIONS_H_
#define _ADDITIONS_H_

#include <stdint.h>
#include <systime.h>
#include <serial.h>
#include <opencv2/core.hpp>
// 单片机端回传数据结构体
struct McuData {
    float curr_yaw;
    float curr_pitch;
    uint8_t state;
    uint8_t mark;
    uint8_t anti_top;
    uint8_t enemy_color;
    int delta_x;
    int delta_y;
};

extern McuData mcu_data;
// 串口接收函数
void uartReceive(Serial *pSerial);
// 相机断线重连函数
bool checkReconnect(bool is_camera_connect);
// 视频保存函数
void saveVideos(const cv::Mat &src);
//　原始图像显示函数
void showOrigin(const cv::Mat &src);
// 图像裁剪函数
void extract(cv::Mat &src);

double getPointLength(const cv::Point2f &p);

// 循环队列
template<class type, int length>
class RoundQueue {
private:
    type data[length];
    int head;
    int tail;
public:
    RoundQueue<type, length>() : head(0), tail(0) {};

    constexpr int size() const {
        return length;
    };

    bool empty() const {
        return head == tail;
    };

    void push(const type &obj) {
        data[head] = obj;
        head = (head + 1) % length;
        if (head == tail) {
            tail = (tail + 1) % length;
        }
    };

    bool pop(type &obj) {
        if (empty()) return false;
        obj = data[tail];
        tail = (tail + 1) % length;
        return true;
    };

    type &operator[](int idx) {
        while (tail + idx < 0) idx += length;
        return data[(tail + idx) % length];
    };
};

#endif /* _ADDITIONS_H_ */
