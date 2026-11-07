# Entity-Component-System Implementation

Astryx Engine uses a custom Entity-Component-System implementation. The main focus on an ECS is the data-oriented design. We store Entites as simple intergers, components as raw data, and systems that iterate over that data. Astryx uses a custom sparse-set implementation of ECS, but we will start from the top.

### Entity

In a standard ECS, an Entity is just an interger (in the case of Astryx a uint32_t). This is to combat from having large inheritence trees, which can get very "tangled", and are not good for preformace. But an entity now is just an identifer of an object. 

We also use a component bitmask to give each entity a specific component combination based on the ComponentID generator, which is made at runtime. 

### Component

This is the gem of an ECS. The component, and in our case, the sparse-set component pool. A component is just a struct, that stores some relevant data to it. For example, the Transform component stores a position, rotation, and scale vector. And to store this, we use what is called a sparse set.

#### Sparse Set

A Sparse Set is a custom way to store components of one type in an ECS. It stores 3 storage containers (std::vectors in our case), the sparse array, the dense entity array, and dense component array. I am going to use a table for this because I think it helped me the most when trying to understand this:

| Structure / Array | Array Index Represents | Stored Value Represents | Primary Purpose | Memory Layout |
| :--- | :--- | :--- | :--- | :--- |
| **`sparse`**<br>`std::vector<int>` | **Entity ID** | **Dense Index** | O(1) lookup to find where component data lives. | **Sparse / Discontinuous**<br>(Contains gaps/tombstones) |
| **`entities`**<br>`std::vector<Entity>` | **Dense Index** | **Entity ID** | Validates ownership and allows safe swaps during deletions. | **Contiguous**<br>(Packed tightly) |
| **`instances`**<br>`std::vector<T>` | **Dense Index** | **Component Data (`T`)** | Stores actual game data for cache-friendly iteration. | **Contiguous**<br>(Packed tightly) |

As stated in the table, the magic of the sparse-set is that we have a Sparse Array which stores the Dense Index at the Entity ID. By having the index be the Entity ID, we can very easily look up the dense location of any piece of component data. And the dense array is amazing for CPU-cache because it can iterate it over and over again very fast. We need the Dense array of Entity IDs for "swap and pop". The steps for "swap-and-pop" are below: 

1. Look up the dense index of the entity being removed using the Sparse Array.
2. Identify the last entity currently residing at the end of the Dense Array.
3. Move the last element's data into the slot of the removed entity.
4. Update the Sparse Array for the moved entity so it points to its new, moved dense index.
5. Decrease the dense array size by 1 (the "pop"), effectively destroying the target data.
6. Flag the removed entity's sparse entry as invalid

To sum it up: We are just taking the last object in the dense array, moving it to that slot, and updating the sparse-set pointer

### System

A system is also very simple. The big thing is the matchEntites() functions. We just iterate over the smallest array using std::min_element() (or whatever that function is). We use the smallest array so its the quickest. We can return a matchEntites vector so that any system can use it. 

After they have the matchEntites function, we just iterate over the components and get the componentData at that entity index of each pool. Its not very compilcated, so see a system like RenderSystem to see the specific iteration implementation. 

### Registry

The Registry is the centeral manager of the ECS. It stores all the Entity and there bitmasks, as well as the addComponent and removeComponent function. Thats basically it. Just the centeral manager. 