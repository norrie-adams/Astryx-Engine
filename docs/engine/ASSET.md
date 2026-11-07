# AssetManager / AssetLoader

This page is going to explain how our AssetManager works, and how our AssetLoader works. It is the orchestrator of our asset loaders.

### Asset ID

One of the biggest problems that engines face is loading models. If 100 cubes have the exact same cube.obj file, then we only want to load it once. To do this, we use an AssetID system. We use the FNV-1a hashing formula to allow us to preform O(1) lookups for assets in a hash table, and store either the Mesh or Texture object as the value. We also store the filePaths next to the hash so we know what filePath corresponds to what model/texture.

That is the basis of our AssetManager, and really all it is. We call the specifc AssetLoader if neccessary (not always the case, for example: Texture calls the loadTexture() function when creating the model).

### Model Loader

The model loader is significantly more complex then the texture loader. I am not going to go to indepth into using Assimp, but I will give the overall concept. To actually understand Assimp, read the [Assimp Documentation](https://the-asset-importer-lib-documentation.readthedocs.io/en/latest/)

The way Assimp loads models is basically by traversing the hierarchal tree of the model using their node hierarchy. The specifics of that can be viewed in the Assimp Documentation linked above. 

However, the specific implmentation of the model data is built into one flat std::vector<float> using the following formula (3 vertices, 2 UV, 3 normals). It is built into a flat array that way we can just pass it in directly to our VBO. 

### Texture Loader

Texture loader is very simple. Because stb_image.h does almost all the work for us, we can just call stbi_load(). We can then return the pixelData so that our Texture object can use that data to upload to to the glTex2D(). 