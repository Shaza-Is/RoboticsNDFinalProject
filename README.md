# RoboticsNDFinalProject
A repository containing the fifth [final] project in Udacity's Robotics Software Engineer Nanodegree: a home service robot picking up a marker from a fixed position and droping it off to another position. Using the [turtle_bot](http://wiki.ros.org/action/show/Robots/TurtleBot?action=show&redirect=TurtleBot) library.


* #### SLAM
Using the package [gmapping](http://wiki.ros.org/gmapping) that contains a ROS wrapper for OpenSlam's Gmapping. The gmapping package provides laser-based SLAM (Simultaneous Localization and Mapping) that is able to generate a floor plan.
* #### Positioning
Using the package [amcl](http://wiki.ros.org/amcl) that implements adaptive Monte Carlo localization approach, which uses a particle filter to track the pose of a robot against a known map.
* #### Navigation
The ROS Navigation Stack serves to drive a mobile base from one location to another while safely avoiding obstacles.
* #### Path Planning
The ROS navigation stack creates a path for your robot based on Dijkstra's algorithm, a variant of the Uniform Cost Search algorithm, while avoiding obstacles on its path.
