# Virtual-Painter - OpenCV

--- This project was done by following the course provided on YouTube by Murtaza's Robotics & AI. ---

*There is currently a bug of "vector subscript out of range", which shows up as soon as the specified color comes
into the camera view.

This virtual painter uses the OpenCV library to detect prespecified colors, which can then be used to 'write on the screen'.

Logic behind the program:
1. Read frames from camera.
2. Convert image to HSV, find a mask for the image with thresholds for prespecified colors.
3. Find the contours of the image (filtering for noise) and create a rectangle around color pen.
4. Return the top point (x, y) and use this point to draw circles onto the screen, which will seem continuous and not discrete
   as we are using a video feed and not a single image.



