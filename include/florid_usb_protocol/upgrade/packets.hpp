#ifndef FLORID_USB_PROTOCOL_UPGRADE_PACKETS_HPP
#define FLORID_USB_PROTOCOL_UPGRADE_PACKETS_HPP

#include "florid_usb_protocol/upgrade/constants.hpp"
#include "RPL/Meta/PacketTraits.hpp"
#include "RPL/Packets/USBAck.hpp"
#include <cstddef>
#include <cstdint>

#pragma pack(push, 1)

namespace florid::usb::upgrade {

struct Version {
    std::uint8_t major;
    std::uint8_t minor;
    std::uint8_t revision;
    std::uint8_t build;
};

struct GetBootStatusRequest {
    std::uint8_t req_id;
};

struct BootStatusResponse {
    std::uint8_t req_id;
    std::uint8_t protocol_version;
    std::uint8_t boot_state;
    std::uint8_t recovery_reason;
    std::uint8_t active_slot;
    std::uint8_t confirmed_slot;
    std::uint8_t pending_slot;
    std::uint8_t reserved0;
    std::uint16_t write_align;
    std::uint16_t max_chunk_size;
    std::uint32_t slot0_address;
    std::uint32_t slot0_size;
    std::uint32_t slot1_address;
    std::uint32_t slot1_size;
    std::uint32_t bytes_written;
};

struct StartUpgradeRequest {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t flags;
    Version version;
    std::uint32_t image_size;
    std::uint32_t image_crc32;
};

struct StartUpgradeResponse {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t accepted_flags;
    std::uint32_t session_id;
    std::uint32_t next_offset;
    std::uint16_t write_align;
    std::uint16_t max_chunk_size;
};

struct WriteChunkRequest {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t reserved0;
    std::uint32_t session_id;
    std::uint32_t offset;
    // Actual bytes to program into flash. Must satisfy the target write
    // alignment requirements.
    std::uint16_t data_size;
    // Logical image bytes carried in `data`. Must be <= data_size. The trailing
    // bytes are padding when valid_size < data_size.
    std::uint16_t valid_size;
    std::uint32_t chunk_crc32;
    std::uint8_t data[kWriteChunkPayloadBytes];
};

struct ChunkWrittenResponse {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t reserved0;
    std::uint32_t session_id;
    std::uint32_t accepted_offset;
    std::uint32_t total_written;
    std::uint16_t accepted_data_size;
    std::uint16_t accepted_valid_size;
    std::uint32_t chunk_crc32;
};

struct FinishUpgradeRequest {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t reserved0;
    std::uint32_t session_id;
    std::uint32_t image_size;
    std::uint32_t image_crc32;
};

struct FinishUpgradeResponse {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t result_flags;
    std::uint32_t session_id;
    std::uint32_t total_written;
};

struct AbortUpgradeRequest {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t flags;
    std::uint32_t session_id;
};

struct UpgradeAbortedResponse {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t result_flags;
    std::uint32_t session_id;
};

struct SetPendingRequest {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t flags;
};

struct PendingSetResponse {
    std::uint8_t req_id;
    std::uint8_t image_id;
    std::uint8_t target_slot;
    std::uint8_t applied_flags;
};

struct RebootRequest {
    std::uint8_t req_id;
    std::uint8_t mode;
    std::uint8_t reserved0;
    std::uint8_t reserved1;
};

struct RebootingResponse {
    std::uint8_t req_id;
    std::uint8_t mode;
    std::uint8_t reserved0;
    std::uint8_t reserved1;
};

static_assert(sizeof(Version) == 4);
static_assert(sizeof(GetBootStatusRequest) <= 0xFF);
static_assert(sizeof(BootStatusResponse) <= 0xFF);
static_assert(sizeof(StartUpgradeRequest) <= 0xFF);
static_assert(sizeof(StartUpgradeResponse) <= 0xFF);
static_assert(sizeof(WriteChunkRequest) <= 0xFFFF);
static_assert(sizeof(ChunkWrittenResponse) <= 0xFF);
static_assert(sizeof(FinishUpgradeRequest) <= 0xFF);
static_assert(sizeof(FinishUpgradeResponse) <= 0xFF);
static_assert(sizeof(AbortUpgradeRequest) <= 0xFF);
static_assert(sizeof(UpgradeAbortedResponse) <= 0xFF);
static_assert(sizeof(SetPendingRequest) <= 0xFF);
static_assert(sizeof(PendingSetResponse) <= 0xFF);
static_assert(sizeof(RebootRequest) <= 0xFF);
static_assert(sizeof(RebootingResponse) <= 0xFF);

} // namespace florid::usb::upgrade

#pragma pack(pop)

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::GetBootStatusRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::GetBootStatusRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::GetBootStatusRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::GetBootStatusRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::BootStatusResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::BootStatusResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::BootStatusResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::BootStatusResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::StartUpgradeRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::StartUpgradeRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::StartUpgradeRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::StartUpgradeRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::StartUpgradeResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::StartUpgradeResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::StartUpgradeResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::StartUpgradeResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::WriteChunkRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::WriteChunkRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::WriteChunkRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::WriteChunkRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::ChunkWrittenResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::ChunkWrittenResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::ChunkWrittenResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::ChunkWrittenResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::FinishUpgradeRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::FinishUpgradeRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::FinishUpgradeRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::FinishUpgradeRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::FinishUpgradeResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::FinishUpgradeResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::FinishUpgradeResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::FinishUpgradeResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::AbortUpgradeRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::AbortUpgradeRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::AbortUpgradeRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::AbortUpgradeRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::UpgradeAbortedResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::UpgradeAbortedResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::UpgradeAbortedResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::UpgradeAbortedResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::SetPendingRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::SetPendingRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::SetPendingRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::SetPendingRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::PendingSetResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::PendingSetResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::PendingSetResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::PendingSetResponse);
    using Protocol = USBBaseProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::RebootRequest>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::RebootRequest>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::RebootRequest);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::RebootRequest);
    static constexpr PacketCategory category = PacketCategory::Request;
    using Protocol = USBRequestProto;
};

template <>
struct RPL::Meta::PacketTraits<florid::usb::upgrade::RebootingResponse>
    : PacketTraitsBase<PacketTraits<florid::usb::upgrade::RebootingResponse>> {
    static constexpr std::uint16_t cmd = florid::usb::upgrade::to_u8(
        florid::usb::upgrade::Command::RebootingResponse);
    static constexpr std::size_t size = sizeof(florid::usb::upgrade::RebootingResponse);
    using Protocol = USBBaseProto;
};

#endif // FLORID_USB_PROTOCOL_UPGRADE_PACKETS_HPP
