/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "utilities.hpp"
#include "ServerNode.hpp"
namespace free_fleet
{
namespace ros2
{

void to_ff_message(
    const rmf_fleet_msgs::msg::Location& _in_msg, messages::Location& _out_msg)
{
  _out_msg.sec = _in_msg.t.sec;
  _out_msg.nanosec = _in_msg.t.nanosec;
  _out_msg.x = _in_msg.x;
  _out_msg.y = _in_msg.y;
  _out_msg.yaw = _in_msg.yaw;
  _out_msg.level_name = _in_msg.level_name;
}

// void to_ff_message(
//     const rmf_fleet_msgs::msg::ModeRequest& _in_msg, 
//     messages::ModeRequest& _out_msg,
//     rclcpp::Client<rmf_task_msgs::srv::SubmitTask>::SharedPtr client)
// {
//     auto request = std::make_shared<rmf_task_msgs::srv::SubmitTask::Request>();
//     request->requester = _in_msg.task_id;
//     request->description.task_type.type = _in_msg.mode.mode;

//     // Servisin hazır olmasını bekleyin
//     // if (!client->wait_for_service(std::chrono::seconds(1))) {
//     //     RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Service not available. Exiting.");
//     //     return;
//     // }

//     // Servis çağrısı yapın
//     if (!client) {
//         RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Task dispatcher client is null.");
//         return;
//     }
//     else{
//         RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Task dispatcher client is not null.");
//     }
//     auto result = client->async_send_request(request, 
//         [&_out_msg, &_in_msg](rclcpp::Client<rmf_task_msgs::srv::SubmitTask>::SharedFuture future) {
//             RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Task dispatcher client ready");
//             auto response = future.get();
//             RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Hop");
//             if (response) {
//               RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Response: %s", response->task_id.c_str());
//             } else {
//               RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
//             }

//             if (response) {
//                 RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "HELLO");
//                 _out_msg.fleet_name = _in_msg.fleet_name;
//                 RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "UPS");
//                 _out_msg.robot_name = _in_msg.robot_name;
//                 _out_msg.mode.mode = _in_msg.mode.mode;
//                 _out_msg.task_id = _in_msg.task_id;
//                 RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "BYE");
//                 for (const auto& parameter : _in_msg.parameters)
//                 { 
//                     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "response->task_id: %s", response->task_id.c_str());
//                     messages::ModeParameter mode_parameter;
//                     mode_parameter.name = parameter.name;
//                     mode_parameter.value = response->task_id;
//                     _out_msg.parameters.push_back(mode_parameter);
//                 }
//             } else {
//                 RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
//             }
//         }
//     );
// }
void to_ff_message(
    const rmf_fleet_msgs::msg::ModeRequest& _in_msg, 
    messages::ModeRequest& _out_msg)
{
  _out_msg.fleet_name = _in_msg.fleet_name;
  _out_msg.robot_name = _in_msg.robot_name;
  _out_msg.mode.mode = _in_msg.mode.mode;
  _out_msg.task_id = _in_msg.task_id;

  for (const auto& parameter : _in_msg.parameters)
  {
    messages::ModeParameter mode_parameter;
    mode_parameter.name = parameter.name;
    mode_parameter.value = parameter.value;
    _out_msg.parameters.push_back(mode_parameter);
  }
}

void to_ff_message(
    const rmf_fleet_msgs::msg::PathRequest& _in_msg, 
    messages::PathRequest& _out_msg)
{
  _out_msg.fleet_name = _in_msg.fleet_name;
  _out_msg.robot_name = _in_msg.robot_name;

  _out_msg.path.clear();
  for (size_t i = 0; i < _in_msg.path.size(); ++i)
  {
    messages::Location tmp_loc_msg;
    to_ff_message(_in_msg.path[i], tmp_loc_msg);
    _out_msg.path.push_back(tmp_loc_msg);
  }

  _out_msg.task_id = _in_msg.task_id;
}

void to_ff_message(
    const rmf_fleet_msgs::msg::DestinationRequest& _in_msg, 
    messages::DestinationRequest& _out_msg)
{
  _out_msg.fleet_name = _in_msg.fleet_name;
  _out_msg.robot_name = _in_msg.robot_name;
  to_ff_message(_in_msg.destination, _out_msg.destination);
  _out_msg.task_id = _in_msg.task_id;
}

void to_ros_message(
    const messages::Location& _in_msg,
    rmf_fleet_msgs::msg::Location& _out_msg)
{
  _out_msg.t.sec = _in_msg.sec;
  _out_msg.t.nanosec = _in_msg.nanosec;
  _out_msg.x = _in_msg.x;
  _out_msg.y = _in_msg.y;
  _out_msg.yaw = _in_msg.yaw;
  _out_msg.level_name = _in_msg.level_name;
}

void to_ros_message(
    const messages::RobotState& _in_msg,
    rmf_fleet_msgs::msg::RobotState& _out_msg)
{
  _out_msg.name = _in_msg.name;
  _out_msg.model = _in_msg.model;
  _out_msg.task_id = _in_msg.task_id;
  _out_msg.mode.mode = _in_msg.mode.mode;
  _out_msg.battery_percent = _in_msg.battery_percent;

  to_ros_message(_in_msg.location, _out_msg.location);

  _out_msg.path = {};
  for (size_t i = 0; i < _in_msg.path.size(); ++i)
  {
    rmf_fleet_msgs::msg::Location tmp_loc;
    to_ros_message(_in_msg.path[i], tmp_loc);
    _out_msg.path.push_back(tmp_loc);
  }
}

} // namespace ros2
} // namespace free_fleet
