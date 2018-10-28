# Vulkan Binary Converter

[![pipeline status](https://git.stabletec.com/utilities/vksbc/badges/master/pipeline.svg)](https://git.stabletec.com/utilities/vksbc/commits/master)
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://git.stabletec.com/utilities/vksbc/blob/master/LICENSE)
[![GitHub tag](https://img.shields.io/github/tag/stablecoder/vksbc.svg)](https://git.stabletec.com/utilities/vksbc/commits/master)

This program is used to convert a SPIR-V binary code file into a set of hexadecimal 4-byte values that can be pasted as an array on unsigned integers in code and used.

This is meant mostly for embedding non-changing shaders directly into code, mostly for testing purposes.

### Usage

Generate a Vulkan bytecode file (typically .spv) from a shader using the glslangvalidator program provided with the Vulkan SDK:

```bash
glslangvalidator -V -o fragShader.frag.spv fragShader.frag
```

Then, run this program on the output file of the above.

```bash
vksbc fragShader.frag.spv
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
./vksbc --ch --cpph fragShader.frag.spv
```

```c
// C header
#include <stdint.h>

static const uint32_t vk_fragShader_size = 572;
static const uint32_t vk_fragShader[] = {
    ...
};
```

```c++
// C++ header
#include <array>
#include <cstdint>

constexpr uint32_t vk_fragShader_size = 572;
constexpr std::array<uint32_t, 143> vk_fragShader = {
    ...
};
```

Usage of such a header can be as simple as
```c
#include "vk_shader.h"

...

VkShaderModuleCreateInfo moduleCI = {};
moduleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
moduleCI.pCode = vk_fragShader;
moduleCI.codeSize = vk_fragShader_size;

VkShaderModule shaderModule;
vkCreateShaderModule(device, &moduleCI, nullptr, &shaderModule);
```

And it should be ready to be used in the creation of Vulkan shaders in the program.