#ifndef LOW_PASS_FILTER_HPP
#define LOW_PASS_FILTER_HPP
class LowPassFilter {
private:
    float alpha;             // 滤波系数
    float yaw_filtered;
    float pitch_filtered;
    bool interrupted = false; // 中断状态标志

public:
    // 构造函数
    LowPassFilter(float alpha, float initial_yaw = 0.0f, float initial_pitch = 0.0f)
        : alpha(alpha), yaw_filtered(initial_yaw), pitch_filtered(initial_pitch) {}

    // 更新滤波器
    void update(float new_yaw, float new_pitch) {
        if (interrupted) {
            // 如果中断，直接同步当前值
            yaw_filtered = new_yaw;
            pitch_filtered = new_pitch;
            interrupted = false; // 自动退出中断状态
            std::cout << "[INFO] 中断恢复：已自动同步当前值。\n";
        } else {
            // 正常滤波
            yaw_filtered = alpha * new_yaw + (1.0f - alpha) * yaw_filtered;
            pitch_filtered = alpha * new_pitch + (1.0f - alpha) * pitch_filtered;
        }
    }

    // 手动初始化滤波器（可选）
    void initialize(float init_yaw, float init_pitch) {
        yaw_filtered = init_yaw;
        pitch_filtered = init_pitch;
    }

    // 设置是否中断
    void setInterrupted(bool state) {
        interrupted = state;
    }

    // 获取当前滤波后的值
    float getFilteredYaw() const {
        return yaw_filtered;
    }

    float getFilteredPitch() const {
        return pitch_filtered;
    }
};

#endif  // LOW_PASS_FILTER_HPP