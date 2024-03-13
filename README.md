# Inter-process-communication-IPC

This project demonstrates interprocess communication, managed by the main file (driver program) named `a3ece650.cpp`, which oversees the overall control flow. Three programs run concurrently, each with specific tasks:

1. **Rgen**: 
   - Randomly generates streets and their coordinates in the format:
     ```
     a “Weber street” (2,2) (5,5) (5,6) (3,8)
     a "King Street S" (4,2) (4,8)
     ```
   - Uses the letter "a" to add a street, specified as: `"a "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)"`. Each `(xi , yi)` represents a GPS coordinate, interpreted as a polyline segment from `(xi , yi)` to `(xi+1, yi+1)`.

2. **a1ece650.py**: 
   - Processes the output of Rgen to generate undirected graphs, including vertices and edges. 
   - Each intersection and endpoint of a line segment that intersects with another street corresponds to a vertex in the graph. 
   - An edge between two vertices is defined as follows:
     1. At least one of them is an intersection.
     2. Both lie on the same street.
     3. One is reachable from the other without traversing another vertex.

3. **a2ece650.cpp**: 
   - Receives the undirected graph as input from `a1ece650.py` and facilitates finding the shortest path between two vertices specified by the user.

This cycle repeats indefinitely until the user explicitly quits. 

4. **a3ece650.cpp**:
   - The driver program (`a3ece650.cpp`) utilizes file descriptors, `dup2()`, `fork()`, `wait()`, `exec()`, `pipe()`, etc. functions for interprocess communication. The code is extensively commented to explain each step of the communication process.
