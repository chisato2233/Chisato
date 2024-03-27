#include "input_from_Windows.h"

namespace cst {
	input_base* input_base::create() { return new input_information<platforms::Windows>{}; }
}