#include <cstdint>
#include <map>
#include <string>

namespace radar {
struct Configs {
    bool debug;
    int friend_side;
    std::string log_path;
    std::string serial_port;
    float delay_duration;
};

struct enemy_robot_position {
    float x;
    float y;
};

/*
 * 串口数据格式 - 定位数据
 * 帧头(5字节) + cmd id(2字节) + 数据(10字节) + CRC16(2字节)
 * 帧头: SOF(1字节) + 数据长度(2字节) + 包序号(1字节) + CRC8(1字节)
 * 数据: 目标机器人ID(2字节) + 目标机器人x坐标(4字节) + 目标机器人y坐标(4字节)
 * 帧尾: CRC16(2字节)
 */
struct __attribute__((packed)) map_robot_data_t {
    uint16_t target_robot_id;
    float target_position_x;
    float target_position_y;
};

/*
 * 串口数据格式 - 雷达决策数据
 * 帧头(5字节) + cmd id(2字节) + 数据(1字节) + CRC16(2字节)
 * 帧头: SOF(1字节) + 数据长度(2字节) + 包序号(1字节) + CRC8(1字节)
 * 数据: cmd命令(1字节)
 * 帧尾: CRC16(2字节)
 */
struct __attribute__((packed)) radar_cmd_t {
    uint8_t cmd;
};

// 比赛状态
enum class GameState {
    NOT_START,
    PREPARATION,
    REFREE_CHECK,
    COUNTDOWN,
    STARTED,
    SETTLING
};
/* - 比赛信息 - ;
   己方颜色  friend_Side;
   比赛状态  gamestate;
   剩余时间  time_remain;
   敌方哨兵血量  enemy_sentry_hp;

   是否激活大能量机关  is_active_big_buff;
   是否已开启双倍易伤  is_double_debuff_enabled;
   可用双倍易伤次数 double_debuff_chances;
   飞镖目标 dart_target;

   开启双倍易伤  enable_double_debuff;
   雷达决策命令  double_debuff_cmd;
 */
class RadarInformation {
public:
    int friend_Side_;
    GameState gamestate_;
    int time_remain_;
    float enemy_sentry_hp_;

    bool is_active_big_buff_;
    bool is_double_debuff_enabled_;

    int double_debuff_chances_;
    int double_debuff_cmd_;

    int dart_target_;
    bool dart_change_;

    struct is_enable_double_debuff_by_ {
        bool enemy_sentry;
        bool big_buff;
    };

    std::map<int, enemy_robot_position> enemy_robot_positions;
};

}