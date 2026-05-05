# Developer Log

## 2026-05-04
**Work completed**
- Cloned the FA25EC3 repository and opened it in CLion.
- Reviewed `submission.md` to confirm the required repository files and the required `developer_log.md` filename.
- Added `CMakeLists.txt` so the project can build in CLion.
- Read through `main.cpp` and confirmed that it must not be modified.
- Began implementing the templated dynamic tree in `tree.h`.
- Added a templated `Node` class with dynamic child and parent pointer storage.
- Added the `Tree` constructor, `createRoot`, `findNode`, `addNode`, and destructor cleanup logic.
- Added centralized node ownership using an `unordered_map` so dynamically allocated nodes can be deleted exactly once.

**Issues encountered**
- The repository did not include a `CMakeLists.txt` file, so CLion could not configure the project automatically.
- The starter `tree.h` only contained placeholders, so the project needed real class structure before later work could continue.
- Because nodes may have multiple parents, a normal recursive tree destructor would risk double deletion.

**Attempts made**
- Opened the project in CLion and checked the starter files already included in the repository.
- Reviewed how `main.cpp` constructs and uses `Tree<string>`.
- Considered recursive deletion, then switched to storing node ownership in a map so each allocated node can be deleted once in the destructor.

**Resolution**
- Added `CMakeLists.txt` so the project can build in CLion.
- Implemented the first major portion of `tree.h` with dynamic node allocation, node lookup, root creation, and safe cleanup.
- Left `printAll()` as a placeholder message for now so the next work session can focus on readable output and fuller tree behavior.

**Commit**
- Day 1: set up FA25EC3 and implement initial tree structure

**Files modified**
- `CMakeLists.txt`
- `developer_log.md`
- `tree.h`

---

## 2026-05-05
**Work completed**
- Continued implementing the templated dynamic tree in `tree.h`.
- Finished the `Node` structure with both child and parent pointer storage.
- Improved `addNode` so the same child can be shared by multiple parents without duplicating nodes.
- Added duplicate-link checks for both parent-to-child and child-to-parent connections.
- Implemented `printAll()` to print the story structure in a readable format.
- Implemented `playGame()` so the tree can later support interactive story traversal.

**Issues encountered**
- Because a child may belong to multiple parents, simple tree assumptions did not work for linking logic.
- Duplicate parent/child links could happen if the same node relationship was added more than once.
- Recursive deletion would still be unsafe for shared nodes.

**Attempts made**
- Reviewed how repeated children should behave when multiple parents reference the same node.
- Added helper checks to prevent duplicate links instead of blindly pushing pointers into both vectors.
- Kept centralized ownership in the `nodesById` map so every allocated node is still deleted exactly once.

**Resolution**
- Completed the second major pass of `tree.h` with working lookup, linking, printing, gameplay traversal, and safe deletion.
- Left `main.cpp` unchanged, since the starter instructions say not to modify it.

**Commit**
- Day 2: implement printing and gameplay support in tree

**Files modified**
- `CMakeLists.txt`
- `developer_log.md`
- `tree.h`