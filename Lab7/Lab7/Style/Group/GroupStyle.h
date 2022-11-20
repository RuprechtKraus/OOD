#pragma once
#include "GroupStyleImpl.h"
#include "Style/IStyle.h"
#include <functional>

using StyleCallback = std::function<void(IStyle&)>;
using StyleEnumerator = std::function<void(const StyleCallback&)>;

using GroupStyle = GroupStyleImpl<IStyle, StyleEnumerator>;