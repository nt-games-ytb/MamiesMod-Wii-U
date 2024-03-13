#pragma once

#include "block/Block.hpp"

#include "blockentity/BlockEntity.hpp"
#include "blockentity/SignBlockEntity.hpp"
#include "blockentity/TheEndGatewayEntity.hpp"

#include "client/app/CInput.hpp"
#include "client/app/CMinecraftApp.hpp"
#include "client/app/ConsoleUIController.hpp"
#include "client/app/CProfile.hpp"
#include "client/app/Options.hpp"
#include "client/app/System.hpp"

#include "client/file/File.hpp"
#include "client/file/FileInputStream.hpp"
#include "client/file/FileOutputStream.hpp"

#include "client/resource/texture/Textures.hpp"

#include "client/resource/NonNullList.hpp"
#include "client/resource/ResourceLocation.hpp"
#include "client/resource/shared_ptr.hpp"
#include "client/resource/vector.hpp"
#include "client/resource/wstring.hpp"

#include "client/C4JThreadImpl.hpp"
#include "client/Minecraft.hpp"

#include "container/AbstractContainerMenu.hpp"
#include "container/Container.hpp"
#include "container/Inventory.hpp"
#include "container/SimpleContainer.hpp"

#include "entity/effect/MobEffect.hpp"
#include "entity/effect/MobEffectInstance.hpp"

#include "entity/player/LocalPlayer.hpp"
#include "entity/player/Player.hpp"
#include "entity/player/PlayerUID.hpp"
#include "entity/player/RemotePlayer.hpp"
#include "entity/player/ServerPlayer.hpp"

#include "entity/AgableMob.hpp"
#include "entity/Animal.hpp"
#include "entity/AreaEffectCloud.hpp"
#include "entity/ArmorStand.hpp"
#include "entity/Entity.hpp"
#include "entity/EvocationFangs.hpp"
#include "entity/ItemEntity.hpp"
#include "entity/ItemFrame.hpp"
#include "entity/LivingEntity.hpp"
#include "entity/Minecart.hpp"
#include "entity/Mob.hpp"
#include "entity/Monster.hpp"
#include "entity/Painting.hpp"
#include "entity/PathfinderMob.hpp"
#include "entity/PrimedTnt.hpp"
#include "entity/Sheep.hpp"
#include "entity/Slime.hpp"
#include "entity/SpectralArrow.hpp"
#include "entity/TippableArrow.hpp"
#include "entity/Zombie.hpp"

#include "item/BlockItem.hpp"
#include "item/BowItem.hpp"
#include "item/Item.hpp"
#include "item/ItemInstance.hpp"

#include "nbt/CompundTag.hpp"
#include "nbt/ListTag.hpp"
#include "nbt/Tag.hpp"

#include "network/listener/ClientPacketListener.hpp"
#include "network/listener/ServerGamePacketListenerImpl.hpp"

#include "network/packet/clientbound/ClientbooundSetEntityMotionPacket.hpp"
#include "network/packet/clientbound/ClientboundBlockUpdatePacket.hpp"
//#include "network/packet/clientbound/ClientboundChatPacket.hpp"
#include "network/packet/clientbound/ClientboundSoundPacket.hpp"

#include "network/packet/serverbound/ServerboundContainerClickPacket.hpp"
#include "network/packet/serverbound/ServerboundInteractPacket.hpp"
#include "network/packet/serverbound/ServerboundMovePlayerPacket.hpp"
#include "network/packet/serverbound/ServerboundPlayerActionPacket.hpp"
#include "network/packet/serverbound/ServerboundPreLoginPacket.hpp"
#include "network/packet/serverbound/ServerboundSetCreativeModeSlotPacket.hpp"
#include "network/packet/serverbound/ServerboundUseItemOnPacket.hpp"

#include "network/packet/CraftItemPacket.hpp"
#include "network/packet/DisconnectPacket.hpp"
#include "network/packet/Packet.hpp"

#include "network/server/MinecraftServer.hpp"
#include "network/server/PlayerList.hpp"

#include "rendering/buffer/BufferBuilder.hpp"
#include "rendering/buffer/BufferedImage.hpp"

#include "rendering/CameraController.hpp"
#include "rendering/Font.hpp"
#include "rendering/GlStateManager.hpp"
#include "rendering/Tesselator.hpp"

#include "ui/Gui.hpp"

#include "util/AABB.hpp"
#include "util/Abilities.hpp"
#include "util/BlockPos.hpp"
#include "util/ClickType.hpp"
#include "util/DamageSource.hpp"
#include "util/Direction.hpp"
#include "util/EntityTickCache.hpp"
#include "util/ePARTICLE_TYPE.hpp"
#include "util/EquipmentSlot.hpp"
#include "util/FloatConverter.hpp"
#include "util/FoodData.hpp"
#include "util/GameType.hpp"
#include "util/HitResult.hpp"
#include "util/InteractionHand.hpp"
#include "util/MallocOperator.hpp"
#include "util/Matrix4.hpp"
#include "util/Other.hpp"
#include "util/pair.hpp"
#include "util/ParticleType.hpp"
#include "util/ParticleType.hpp"
#include "util/SoundEvent.hpp"
#include "util/SoundSource.hpp"
#include "util/unordered_map.hpp"
#include "util/Vec3.hpp"
#include "util/VTable_Entity.hpp"
#include "util/VTable_Item.hpp"
#include "util/VTable.hpp"

#include "world/gamemode/ServerPlayerGameMode.hpp"

#include "world/Level.hpp"
#include "world/ServerLevel.hpp"

// Prints a message into Chat.
template<typename... Args>
void mc_printf(const wchar_t* x, Args... args) {
    if (!mc::Minecraft::getInstance()->thePlayer) return;
    wchar_t temp[0xA0];
    mc_swprintf(temp, 0xA0, x, args...);
    mc::Minecraft::getInstance()->gui->addMessage(temp, 0, 0, 0, 0, 0);
}

template<typename... Args>
void locale_chat_message(const wchar_t* message, Args... args) {
    if (!mc::Minecraft::getInstance()->thePlayer)
        return;
    wchar_t temp[0x1000];
    mc_swprintf(temp, 0x1000, message, args...);
    mc::Minecraft::getInstance()->gui->addMessage(temp, 0, 0, 0, 0, 0);
}
