# OpenGL System Explanation

OpenGL is a graphics API that can talk to your GPU directly, and draw things on the screen, with the help of a few external libraries. In this document, I am going to explain the OpenGL Pipeline, which is the process that OpenGL goes through to draw the triangle. This is not going to go in depth to each part, as that will covered by other pages (which will be guided through as you read these documents). 

### OpenGL Pipeline

Think of the OpenGL Pipeline as the steps to drawing a colored triangle. When drawing a triangle, you usually follow a specific set of steps. For example, you first need to decide on your 3 points you want to draw. Then you plot those points. Then you connect the lines, and color it in. OpenGL follows a similar process, but has some specific terminology for them.

#### 1. Pass in vertices 
The first step is to pass in an array of vertices. This is like drawing the points on the paper. 