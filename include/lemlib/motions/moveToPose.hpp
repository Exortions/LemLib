#pragma once

#include "lemlib/ExitCondition.hpp"
#include "pros/motor_group.hpp"
#include "units/Angle.hpp"
#include "lemlib/PID.hpp"
#include "units/Pose.hpp"

namespace lemlib {
/**
 * @brief Parameters for moveToPose
 *
 * We use a struct to simplify customization. Chassis::moveToPose has many
 * parameters and specifying them all just to set one optional param ruins
 * readability. By passing a struct to the function, we can have named
 */
struct MoveToPoseParams {
        bool forwards = true;
        double horizontalDrift = 0;
        double lead = 0.6;
        int maxSpeed = 1;
        int minSpeed = 0;
        Length earlyExitRange = 0_in;
};

/**
 * @brief Settings for moveToPose
 *
 * We use a struct to simplify customization. Chassis::moveToPose has many
 * parts of the robot that need to be passed to it. By passing a struct to the
 * function, we can have named parameters, overcoming the c/c++ limitation
 */
struct MoveToPoseSettings {
        /** the lateral PID that is used to move the robot forwards and backwards */
        PID lateralPID;
        /** the angular PID that is used to turn the robot */
        PID angularPID;
        /** the exit conditions for the lateral PID */
        ExitConditionGroup<Length> lateralExitConditions;
        /** the exit conditions for the angular PID */
        ExitConditionGroup<AngleRange> angularExitConditions;
        /** this function should return the estimated pose of the robot, typically by the tracking wheel odometry. */
        std::function<units::Pose()> poseGetter;
        /** the left motor group of the drivetrain */
        pros::MotorGroup& leftMotors;
        /** the right motor group of the drivetrain */
        pros::MotorGroup& rightMotors;
};
} // namespace lemlib