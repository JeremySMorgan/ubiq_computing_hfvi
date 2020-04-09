// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2019 Intel Corporation. All Rights Reserved.

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <iostream>             // for cout
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include "include/example.hpp"          // Include a short list of convenience functions for rendering

// Hello RealSense example demonstrates the basics of connecting to a RealSense device
// and taking advantage of depth data
int main(int argc, char * argv[]) try{


    window app(1280, 720, "RealSense Capture Example");

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Declare rates printer for showing streaming rates of the enabled streams.
    rs2::rates_printer printer;

    // Create a Pipeline - this serves as a top-level API for streaming and processing frames
    rs2::pipeline pipe;

    // Configure and start the pipeline
    pipe.start();

    while (app){

        rs2::frameset data = pipe.wait_for_frames().
                                apply_filter(printer).
                                apply_filter(color_map);    // colorize the depth data

        app.show(data);

        auto mat = frame_to_mat();

        // Block program until frames arrive
//        rs2::frameset frames = p.wait_for_frames();
//
//        // Try to get a frame of a depth image
//        rs2::depth_frame depth = frames.get_depth_frame();
//
//        // Get the depth frame's dimensions
//        float width = depth.get_width();
//        float height = depth.get_height();
//
//        // Query the distance from the camera to the object in the center of the image
//        float dist_to_center = depth.get_distance(width / 2, height / 2);
//
//        // Print the distance
//        std::cout << "The camera is facing an object " << dist_to_center << " meters away \r";
    }

    return EXIT_SUCCESS;
}
catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
