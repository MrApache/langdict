#include "interact.h"

interact create_interaction(bool interactable, point pos, point size, callback callback)
{
    interact interact = { interactable, pos, size, callback };
    return interact;
}
