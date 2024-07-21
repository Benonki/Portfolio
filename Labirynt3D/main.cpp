/**
 * @file main.cpp
 * @brief Main entry point of the application.
 */

#include "Engine3D.h"

 /**
  * @brief Main function to initialize and run the 3D engine.
  * @param argc Argument count.
  * @param argv Argument vector.
  * @return Exit status.
  */
int main(int argc, char** argv) {
    Engine3D engine;
    engine.run(argc, argv);
    return 0;
}
