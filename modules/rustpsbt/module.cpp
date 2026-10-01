#include <span>

#include "module.h"
#include "rust_psbt_lib/rust_psbt_lib.h"

namespace bitcoinfuzz {
namespace module {
RustPsbt::RustPsbt(void) : BaseModule("RustPsbt") {}

namespace {
std::optional<std::string> TakeCString(char *result_ptr) {
  if (result_ptr == nullptr)
    return std::nullopt;

  std::string result(result_ptr);
  rust_psbt_free_c_string(result_ptr);
  return result;
}
} // namespace

std::optional<std::string>
RustPsbt::psbt_v0_parse(std::span<const uint8_t> buffer) const {
  return TakeCString(rust_psbt_psbt_v0_parse(buffer.data(), buffer.size()));
}

std::optional<std::string>
RustPsbt::psbt_v2_parse(std::span<const uint8_t> buffer) const {
  return TakeCString(rust_psbt_psbt_v2_parse(buffer.data(), buffer.size()));
}
} // namespace module
} // namespace bitcoinfuzz
