#pragma once
#include <stratosphere.hpp>

namespace ams::ldr {
    void ApplyPcvPatch(u8 *mapped_module, const ro::ModuleId* module_id);

}
