#include "Engine/Modules/Input/RawKey.h"

RawKey::RawKey(RawKeyCode keyCode, InputDivice inputDivice) : code(keyCode), divice(inputDivice)
{
}

bool RawKey::operator==(const RawKey rhs) const
{
	return code == rhs.code && divice == rhs.divice;
}

bool RawKey::operator!=(const RawKey rhs) const
{
	return !(*this == rhs);
}
