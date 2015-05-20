/* 
 * File:   main.cpp
 * Author: johannes
 *
 * Created on 27. April 2015, 12:26
 */

#include <time.h>

#include "Firefly.h"
#include "SensorCommand.h"
#include "NavigationCommand.h"

/*
 * 
 */
void sensors(bool read_gps) {
    GPSDataCommand gps;
    IMUDataCommand imu;
    LLStatusCommand lls;
    timespec reqt, remt;

    reqt.tv_sec = 1;
    reqt.tv_nsec = 0;

    while (true) {
        try {
            if (read_gps) {
                gps.execute();
                std::cout << "Latitude: " << gps.getData()->latitude << std::endl;
                std::cout << "Longtiude: " << gps.getData()->longitude << std::endl;
            }
            imu.execute();
            std::cout << "Nick: " << imu.getData()->angle_nick << std::endl;
            std::cout << "Roll: " << imu.getData()->angle_roll << std::endl;
            std::cout << "Yaw : " << imu.getData()->angle_yaw << std::endl;
            lls.execute();
            std::cout << "Battery: " << lls.getData()->battery_voltage_1 << std:.endl;
            std::cout << "--------------------------------------------------------" << std::cout;
        } catch (std::runtime_error &e) {
            std::cout << "Runtime error: " << e.what() << std::endl;
        }
        nanosleep(&reqt, &remt);
    }
}

void waypoints(){
        LaunchCommand ln;
        WaypointCommand wp;
        EndCommand ed;
}  

int main(int argc, char** argv) {
    try {
        sensors(false);
        //waypoints();
    } catch (std::runtime_error &e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cout << "Esception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Uncaught Exception" << std::endl;
    }

    return 0;
}
