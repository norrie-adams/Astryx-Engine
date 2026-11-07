# Rendering

This page explains how the Astryx Renderer works. It also covers every file in the rendering/ directory. 

> [!NOTE]
> This section contains a lot of concepts that I explain very briefly but do not go indepth nor do I give it a proper explanation. If you would like to actually understand what these concepts are, I highly recommend checking out [LearnOpenGL](https://learnopengl.com).

### Renderer

We use a dual-pass renderer. A dual pass renderer means it preforms 2 render passes, also known as draw calls. Wait, drawing it twice? Why would we draw it twice? We draw it twice so we can produce shadows. However, the first time, we are simply not displaying it to the screen. Put simply, we are collecting data about the distance to a mesh to see if it is blocking the light. I will not go anymore indepth because I do not feel like explaining shadow mapping.

Our main draw call function is called Submit(), which takes in a variety of parameters. It configures the shader with matrices, vectors, floats, etc. that it needs to execute that draw call, and then it calls the draw() function. The parameters are passed in by the render system, which will be explained later.

Now we can look at the core parts of the Renderer, the Mesh, Shader, and Texture classes. Below is a basic summary of each:

**1. Mesh**
Mesh creates our VAO and VBO. Put simply, the VAO (Vertex Array Object) is the instruction set for how the GPU should read our VBO (Vertex Buffer Object), which contains our actual vertex data. It also assigns our Position and Texture Attribute (Position 0 and 1 respectively). Lastly, it contains our draw function which is really just a wrapper for glDrawArrays().

**2. Shader**
The shader classe is a little bit more complex. It is responsible for loading, compiling, and linking shaders. A shader is a program that runs on the GPU which tells it how to actually draw things (yes this is very different then our VAO. Its so different it has its own programming language (GLSL)!). 

**3. Texture**
Our texture class is much more similar to our Mesh class then it is to our Shader class, in that it just creates a Texture object which handles all the OpenGL texture calls. However, it does use an external library called stb_image.h. It is a single header file that can extract the pixelData out of files like .jpg, .png, etc. We load the data, determine the number of nrChannels, and set the interal/data format. 

Before we talk about our render system, I would like to talk about the Camera. I didn't include it above because I honestly forgot about it and I realized that its a niche enough thing that it deserves its own little section, so here it is: 

**Camera**
Our camera is what controls what we see in the world. It builds things like the view matrix, which says where we are in the world. The thing thats cool and weird about this is that the players position never actually changes. The rest of the world just moves closer or farther away. Anyways, the rest of the camera just handles processing the input and determining mouse-look with Euler angles. 

Yay, we finished the renderer, now we get to talk about our RenderSystem. Its actually pretty simple. 

### RenderSystem

First, I would like to explain a few concepts. If you have read the ECS section of the documentation, feel free to skip this short paragraph. Component Pools, and Entites. Entites are just the "Objects" we are drawing. Component Pools are the actual data we use. 

The big way our RenderSystem works is by just extracting component data from the component pools, and filling it in to the specific struct. We use the matchEntites() function which matches all entites with any combination of components. 

Remember 5 minutes ago when you read that Astryx uses a dual-pass renderer? That means that we must submit 2 sets of parameters, which means we need to iterate over the component pool twice. On the first pass, we populate the ShadowPassParameters struct with a pointer to the Mesh, Shader, and the model matrix. That is all we need for us to get the data needed for drawing the shadows.

On the second pass, we need a lot more data. I am not going to list it here, because its to long. If you want to see what data is needed, check [Line 19 of Renderer.hpp](../../engine/include/rendering/Renderer.hpp). And that data is also extracted from the component pools. We then Submit that data to the main renderer.