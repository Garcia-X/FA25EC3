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

---

## 2026-05-06
**Work completed**
- Built and ran the FA25EC3 project in CLion.
- Fixed the CLion run configuration so the correct CMake-built EC3 executable was being launched.
- Tested the OpenAI request flow in `main.cpp`.
- Reviewed the runtime output and generated files to determine why the story was not loading.
- Confirmed that the original inline request formatting was failing during the `curl` step on Windows.
- After testing and narrowing down the issue, made a limited `main.cpp` change to send the JSON request through `payload.json` with `--data-binary`.
- Completed the intended tree-construction integration in `main.cpp` by creating the root from `rawNodes[0]`, connecting parent-child relationships with `addNode(...)`, and printing the tree with `printAll()`.

**Issues encountered**
- The program initially failed during the OpenAI request step.
- CLion was at first trying to run the wrong executable path.
- After fixing the run configuration, the original `curl` request in `main.cpp` still failed because the inline JSON request body was not being handled correctly on Windows.
- Once the request-format issue was fixed, the API returned an `insufficient_quota` error instead of story data.
- Because the API response was an error object rather than properly formatted story nodes, `story.txt` could not be parsed into valid story nodes.

**Attempts made**
- Rebuilt the project and corrected the run configuration so the proper EC3 executable was being launched.
- Reran the starter code without changing the request logic to confirm whether the failure was caused by the run configuration, the Tree implementation, or the request step.
- Reviewed the console output carefully and confirmed that the failure was happening before the parsed story data could be used.
- After narrowing the problem down to the request formatting, updated only the request portion of `main.cpp` so the JSON body would be written to `payload.json` and passed to `curl` cleanly.
- Reran the project after that change and checked the new API response.

**Resolution**
- Confirmed that the request-format problem was fixed.
- Confirmed that the project now reaches the API correctly.
- Identified account quota as the remaining blocker to automatically generating a valid `story.txt`.
- Chose not to continue by adding billing, since the assignment instructions did not clearly state that paid API quota would be required.
- Treated this as the final commit for the project because there is no clear way to complete the OpenAI generation step further without paid API quota.

**Commit**
- Final commit: fix request formatting and document OpenAI quota blocker

**Files modified**
- `main.cpp`
- `developer_log.md`
- `payload.json`
- `story.txt`