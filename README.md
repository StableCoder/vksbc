# Vulkan Binary Converter

[![pipeline status](http://git.stabletec.com/utilities/vksbc/badges/master/pipeline.svg)](http://git.stabletec.com/utilities/vksbc/commits/master)
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://git.stabletec.com/utilities/vksbc/blob/master/LICENSE)

This program is used to convert a SPIR-V binary code file into a set of hexadecimal 4-byte values that can be pasted as an array on unsigned integers in code and used.

This is meant mostly for embedding non-changing shaders directly into code, mostly for testing purposes.

### Usage

Generate a Vulkan bytecode file (typically .spv) from a shader using the glslangvalidator program provided with the Vulkan SDK:

```bash
glslangvalidator -V -o inputFile.frag.spv inputFile.frag
```

Then, run this program on the output file of the above.

```bash
vkshaderbinaryconverter inputFile.frag.spv
```

A file should have been created, with content similar to this:

```
0x07230203, 0x00010000, 0x00080001, 0x0000000D, 0x00000000, 0x00020011, 0x00000001, 0x0006000B, 
0x00000001, 0x4C534C47, 0x6474732E, 0x3035342E, 0x00000000, 0x0003000E, 0x00000000, 0x00000001, 
0x0006000F, ...
```

## C/C++ style headers

New options allow for genenrating ready-to-use C and C++ style headers, by adding the `--ch` or `--cpph` options to running the program, generated standalone headers with the arrays and required header incudes for use.

```bash
vkshaderbinaryconverter inputFile.frag.spv
```

```c
// C header
#include <stdint.h>

static uint32_t fragShader[] = {
    ...
};
```

```c++
// C++ header
#include <array>
#include <cstdint>

constexpr std::array<uint32_t, 143> fragShader = {
    ...
};
```

Usage of such a header can be as simple as
```cpp
#include "vk_shader.h"

...

VkShaderModuleCreateInfo moduleCI = {};
moduleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
moduleCI.pCode = fragShader.data();
moduleCI.codeSize = fragShader.size() * sizeof(uint32_t);

VkShaderModule shaderModule;
vkCreateShaderModule(device, &moduleCI, nullptr, &shaderModule);
```

And it should be ready to be used in the creation of Vulkan shaders in the program.