

#include "utils.h"
#include "absl/strings/string_view.h"
#include <string.h>

namespace nlptools
{


//     std::string utf8chr(int cp)
// {
//     char c[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
//     if (cp <= 0x7F) { c[0] = cp; }
//     else if (cp <= 0x7FF)
//     {
//         c[0] = (cp >> 6) + 192;
//         c[1] = (cp & 63) + 128;
//     }
//     else if (0xd800 <= cp && cp <= 0xdfff) {} //invalid block of utf8
//     else if (cp <= 0xFFFF)
//     {
//         c[0] = (cp >> 12) + 224;
//         c[1] = ((cp >> 6) & 63) + 128;
//         c[2] = (cp & 63) + 128;
//     }
//     else if (cp <= 0x10FFFF)
//     {
//         c[0] = (cp >> 18) + 240;
//         c[1] = ((cp >> 12) & 63) + 128;
//         c[2] = ((cp >> 6) & 63) + 128;
//         c[3] = (cp & 63) + 128;
//     }
//     return std::string(c);
// }


} // namespace nlptool
