
## 📌 What is Bazel?

Bazel is Google's open-source **build and test tool** designed for:

| Feature | Benefit |
|---------|---------|
| **Speed** | Only rebuilds what changed (incremental) |
| **Scalability** | Handles massive codebases |
| **Multi-language** | C++, Python, Java, Go, etc. |
| **Reproducibility** | Same inputs = same outputs |
| **Caching** | Local and remote caching |

---

## 🏗️ Core Concepts

### 1. WORKSPACE
- Marks the **root** of your Bazel project
- Defines external dependencies (classic method)
- Every project needs this file (can be empty)

### 2. MODULE.bazel
- **Modern** way to manage dependencies (Bzlmod)
- Cleaner syntax than WORKSPACE
- Works with Bazel 6.0+

### 3. BUILD File
- Defines **what to build** in a package
- Contains rules and targets
- One per package (folder)

### 4. Package
- A folder containing a BUILD file
- Unit of organization

### 5. Target
- Something that can be built
- Has a unique label (name)

### 6. Rule
- **How** to build something
- Examples: `cc_binary`, `cc_library`, `cc_test`

---

## 🏷️ Labels (How to Reference Targets)

```
//package/path:target_name
│       │          │
│       │          └── Target name (from "name" attribute)
│       └── Path from WORKSPACE root
└── Means "from project root"
```

| Label | Meaning |
|-------|---------|
| `:mylib` | Target in **same** package |
| `//math:calc` | Target `calc` in `math/` package |
| `//utils:helper` | Target `helper` in `utils/` package |
| `//:app` | Target `app` in **root** package |
| `@googletest//:gtest` | External repo target |

---

## 📝 Common Rules

### cc_binary (Executable)

```python
cc_binary(
    name = "app",              # Target name
    srcs = ["main.cpp"],       # Source files (.cpp, .c)
    deps = [                   # Dependencies
        "//lib:mylib",
        "@external//:lib",
    ],
)
```

> **Use when:** File has `main()` function

---

### cc_library (Library)

```python
cc_library(
    name = "mylib",
    srcs = ["mylib.cpp"],              # Implementation files
    hdrs = ["mylib.hpp"],              # Header files (public)
    deps = ["//other:lib"],            # Dependencies
    visibility = ["//visibility:public"],  # Who can use this
)
```

> **Use when:** Reusable code without `main()`

**Remember:**
| Attribute | File Types |
|-----------|------------|
| `srcs` | `.cpp`, `.c` (implementation) |
| `hdrs` | `.hpp`, `.h` (headers) |

---

### cc_test (Test)

```python
cc_test(
    name = "mylib_test",
    srcs = ["mylib_test.cpp"],
    deps = [
        "//lib:mylib",                 # Library to test
        "@googletest//:gtest",         # Google Test
        "@googletest//:gtest_main",    # Provides main()
    ],
)
```

---

## 🔐 Visibility

Controls who can use your target:

```python
cc_library(
    name = "mylib",
    srcs = ["mylib.cpp"],
    visibility = ["//visibility:public"],  # Everyone can use
)
```

| Visibility | Who Can Use |
|------------|-------------|
| `["//visibility:private"]` | Only same package (default) |
| `["//visibility:public"]` | Anyone |
| `["//math:__pkg__"]` | Only math package |
| `["//math:__subpackages__"]` | Math and subfolders |

---

## 📦 External Dependencies

### Method 1: WORKSPACE (Classic)

```python
# WORKSPACE

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "googletest",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"],
    strip_prefix = "googletest-1.14.0",
    sha256 = "...",  # Optional but recommended
)
```

### Method 2: Bzlmod (Modern - Recommended)

```python
# MODULE.bazel

module(
    name = "my_project",
    version = "1.0.0",
)

bazel_dep(name = "googletest", version = "1.14.0.bcr.1")
bazel_dep(name = "abseil-cpp", version = "20230802.0")
```

**Comparison:**

| Aspect | WORKSPACE | Bzlmod |
|--------|-----------|--------|
| Syntax | Verbose | Simple |
| URLs needed | Yes | No |
| Bazel version | All | 6.0+ |
| Recommended | Legacy | New projects |

---

## 🔍 Bazel Query

### List All Targets

```bash
bazel query //...
```

### Find Dependencies

```bash
# What does my target depend on?
bazel query "deps(//app:main)"

# Direct deps only (depth = 1)
bazel query "deps(//app:main, 1)"
```

### Find Reverse Dependencies

```bash
# What depends on my library?
bazel query "rdeps(//..., //lib:mylib)"
#            ─────   ─────────────
#              │           │
#              │           └── Target to find deps OF
#              └── Universe (where to search)
```

### Filter by Rule Type

```bash
# All libraries
bazel query "kind(cc_library, //...)"

# All tests
bazel query "kind(cc_test, //...)"

# All binaries
bazel query "kind(cc_binary, //...)"
```

### Find Dependency Path

```bash
# Why does A depend on B?
bazel query "somepath(//app:main, //lib:helper)"
```

### Generate Visual Graph

```bash
bazel query "deps(//app:main)" --output graph > deps.dot
dot -Tpng deps.dot -o deps.png
```

---

## 💻 Common Commands

### Build

```bash
bazel build //:app           # Build specific target
bazel build //...            # Build everything
bazel build //math:all       # Build all in math package
```

### Run

```bash
bazel run //:app             # Build and run
./bazel-bin/app              # Run directly after build
```

### Test

```bash
bazel test //test:my_test    # Run specific test
bazel test //...             # Run all tests
```

### Clean

```bash
bazel clean                  # Remove build outputs
bazel clean --expunge        # Remove everything including cache
```

### Info

```bash
bazel --version              # Check Bazel version
bazel info                   # Show project info
```

---

## 📁 Project Structure Template

```
my_project/
├── MODULE.bazel             # Dependencies (Bzlmod)
├── WORKSPACE                # Can be empty with Bzlmod
├── .bazelrc                 # Bazel settings
├── .gitignore               # Add bazel-* here
├── BUILD                    # Root package
├── main.cpp
├── lib/
│   ├── BUILD
│   ├── mylib.cpp
│   └── mylib.hpp
└── test/
    ├── BUILD
    └── mylib_test.cpp
```

---

## 📄 File Templates

### MODULE.bazel

```python
module(
    name = "my_project",
    version = "1.0.0",
)

bazel_dep(name = "googletest", version = "1.14.0.bcr.1")
```

### .bazelrc

```bash
# Enable Bzlmod (for Bazel < 7.0)
common --enable_bzlmod

# Better output
build --verbose_failures
test --test_output=errors
```

### .gitignore

```
bazel-*
MODULE.bazel.lock
```

### Root BUILD

```python
cc_binary(
    name = "app",
    srcs = ["main.cpp"],
    deps = ["//lib:mylib"],
)
```

### lib/BUILD

```python
cc_library(
    name = "mylib",
    srcs = ["mylib.cpp"],
    hdrs = ["mylib.hpp"],
    visibility = ["//visibility:public"],
)
```

### test/BUILD

```python
cc_test(
    name = "mylib_test",
    srcs = ["mylib_test.cpp"],
    deps = [
        "//lib:mylib",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
```

---

## ⚠️ Common Mistakes to Avoid

| Mistake | Fix |
|---------|-----|
| Using `cc_library` for executable | Use `cc_binary` when file has `main()` |
| `.hpp` in `srcs` | Put headers in `hdrs`, sources in `srcs` |
| `visibility:public` | Must be `//visibility:public` |
| `rdeps(target, universe)` | Order is `rdeps(universe, target)` |
| Forgetting visibility | Add `visibility = ["//visibility:public"]` |
| Wrong label path | Labels point to target NAME, not file name |

---

## 🧪 Testing with Google Test

### Test File Example

```cpp
// test/mylib_test.cpp
#include <gtest/gtest.h>
#include "lib/mylib.hpp"

TEST(MyLibTest, BasicTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(MyLibTest, AnotherTest) {
    EXPECT_TRUE(true);
}
```

### Run Tests

```bash
bazel test //test:mylib_test
bazel test //...  # Run all
```

---

## 🔗 Quick Reference Links

| Resource | URL |
|----------|-----|
| Bazel Docs | https://bazel.build/docs |
| Central Registry | https://registry.bazel.build |
| Examples | https://github.com/bazelbuild/examples |

---

## 📊 Mental Model

```
┌─────────────────────────────────────────────────────────────┐
│                     BAZEL PROJECT                           │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  MODULE.bazel ─── External Dependencies                     │
│       │                                                     │
│       ▼                                                     │
│  ┌─────────┐    ┌─────────┐    ┌─────────┐                 │
│  │ Package │    │ Package │    │ Package │                 │
│  │  BUILD  │───►│  BUILD  │◄───│  BUILD  │                 │
│  └────┬────┘    └────┬────┘    └────┬────┘                 │
│       │              │              │                       │
│    Targets        Targets        Targets                    │
│  (cc_binary)   (cc_library)    (cc_test)                   │
│       │              │              │                       │
│       └──────────────┴──────────────┘                       │
│                      │                                      │
│               bazel build //...                             │
│                      │                                      │
│                      ▼                                      │
│                 bazel-bin/                                  │
│              (compiled outputs)                             │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

> 💡 **Remember:** Bazel = Fast, Scalable, Reproducible builds!


![Bazel Mind Map](assets/bazel_mindmap.png)

---

