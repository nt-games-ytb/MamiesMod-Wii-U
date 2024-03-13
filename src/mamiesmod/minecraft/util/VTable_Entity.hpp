#pragma once

#include "VTable.hpp"

#include "../client/resource/shared_ptr.hpp"
#include "InteractionHand.hpp"

namespace mc {
    struct VTable_Entity : public VTable {
    public:
        MC_VFUNC(void, struct Entity, __pure_virtual_called);
        MC_VFUNC(void, struct Entity, __dt__6EntityFv);
        MC_VFUNC(void, struct Entity, fjDerivedCtorCalls__6EntityFv);
        MC_VFUNC(void, struct Entity, kill__6EntityFv);
        MC_VFUNC(void, struct Entity, __pure_virtual_called_2);
        MC_VFUNC(void, struct Entity, resetPos__6EntityFv);
        MC_VFUNC(void, struct Entity, remove__6EntityFv);
        MC_VFUNC(void, struct Entity, setDropContainerContent__6EntityFb);
        MC_VFUNC(void, struct Entity, setSize__6EntityFfT1);
        MC_VFUNC(void, struct Entity, setPos__6EntityFdN21);
        MC_VFUNC(void, struct Entity, tick__6EntityFv);
        MC_VFUNC(void, struct Entity, baseTick__6EntityFv);
    };
}